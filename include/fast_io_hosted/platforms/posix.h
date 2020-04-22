#pragma once

#if defined(__WINNT__) || defined(_MSC_VER)
#include<io.h>
#else
#include<unistd.h>
#endif
#include<fcntl.h>
#ifdef __linux__
#include<sys/sendfile.h>
#endif

namespace fast_io
{
	
namespace details
{
#if defined(__WINNT__) || defined(_MSC_VER)
template<bool wide_char=false>
inline constexpr int calculate_posix_open_mode_for_win32_handle(open_mode value)
{
	int mode{};
	if((value&open_mode::binary)!=open_mode::none)
		mode = _O_BINARY;
	else
	{
		if constexpr(wide_char)
			mode |= _O_WTEXT;
		else
			mode |= _O_TEXT;
	}
	constexpr auto supported_values{open_mode::out|open_mode::app|open_mode::in};
	switch(supported_values&value)
	{
//Action if file already exists;	Action if file does not exist;	c-style mode;	Explanation
//Read from start;	Failure to open;	"r";	Open a file for reading
	case open_mode::in:
		return mode | O_RDONLY;
//Destroy contents;	Create new;	"w";	Create a file for writing
	case open_mode::out:
//Read from start;	Error;	"r+";		Open a file for read/write
	case open_mode::out|open_mode::in:
		return mode;
//Append to file;	Create new;	"a";	Append to a file
	case open_mode::app:
	case open_mode::out|open_mode::app:
		return mode | O_APPEND;
//Write to end;	Create new;	"a+";	Open a file for read/write
	case open_mode::out|open_mode::in|open_mode::app:
	case open_mode::in|open_mode::app:
		return mode | O_APPEND;
//Destroy contents;	Error;	"wx";	Create a file for writing
	default:
#ifdef __cpp_exceptions
		throw std::system_error(make_error_code(std::errc::invalid_argument));
#else
		fast_terminate();
#endif
	}
}
template<open_mode om>
struct posix_file_openmode_for_win32_handle
{
	static int constexpr mode = calculate_posix_open_mode_for_win32_handle(om);
};
#endif


inline constexpr int calculate_posix_open_mode(open_mode value)
{
	int mode
	{
#ifdef O_NOFOLLOW
		O_NOFOLLOW
#endif
	};
	if((value&open_mode::follow)!=open_mode::none)
		mode = {};
	if((value&open_mode::inherit)==open_mode::none)
#ifdef O_CLOEXEC
		mode |= O_CLOEXEC;
#elif _O_NOINHERIT
		mode |= _O_NOINHERIT;
#endif
#ifdef O_BINARY
	if((value&open_mode::binary)!=open_mode::none)
		mode |= O_BINARY;
#endif
	if((value&open_mode::excl)!=open_mode::none)
		mode |= O_CREAT | O_EXCL;
	if((value&open_mode::trunc)!=open_mode::none)
		mode |= O_TRUNC;
#ifdef O_DIRECT
	if((value&open_mode::direct)!=open_mode::none)
		mode |= O_DIRECT;
#endif

#ifdef O_SYNC
	if((value&open_mode::sync)!=open_mode::none)
		mode |= O_SYNC;
#endif
/*
	if((value&open_mode::directory)!=open_mode::none)
#ifdef O_DIRECTORY
		mode |= O_DIRECTORY;
#elif __cpp_exceptions
		throw std::system_error(make_error_code(std::errc::operation_not_supported));
#else
		fast_terminate();
#endif
*/
#ifdef O_NOCTTY
	if((value&open_mode::no_ctty)!=open_mode::none)
		mode |= O_NOCTTY;
#endif
#ifdef O_NOATIME
	if((value&open_mode::no_atime)!=open_mode::none)
		mode |= O_NOATIME;
#endif
	if((value&open_mode::no_block)!=open_mode::none)
#ifdef O_NONBLOCK
		mode |= O_NONBLOCK;
#elif __cpp_exceptions
		throw std::system_error(make_error_code(std::errc::operation_not_supported));
#else
		fast_terminate();
#endif

#ifdef _O_TEMPORARY
	if((value&open_mode::temprorary)!=open_mode::none)
		mode |= _O_TEMPORARY;
#endif
#ifdef _O_SEQUENTIAL
	if((value&open_mode::sequential_scan)!=open_mode::none)
		mode |= _O_SEQUENTIAL;
	else
		mode |= _O_RANDOM;
#endif
	constexpr auto supported_values{open_mode::out|open_mode::app|open_mode::in};
	switch(value&supported_values)
	{
//Action if file already exists;	Action if file does not exist;	c-style mode;	Explanation
//Read from start;	Failure to open;	"r";	Open a file for reading
	case open_mode::in:
		return mode | O_RDONLY;
//Destroy contents;	Create new;	"w";	Create a file for writing
	case open_mode::out:
		return mode | O_WRONLY | O_CREAT | O_TRUNC;
//Append to file;	Create new;	"a";	Append to a file
	case open_mode::app:
	case open_mode::out|open_mode::app:
		return mode | O_WRONLY | O_CREAT | O_APPEND;
//Read from start;	Error;	"r+";		Open a file for read/write
	case open_mode::out|open_mode::in:
		return mode | O_RDWR;
//Write to end;	Create new;	"a+";	Open a file for read/write
	case open_mode::out|open_mode::in|open_mode::app:
	case open_mode::in|open_mode::app:
		return mode | O_RDWR | O_CREAT | O_APPEND;
//Destroy contents;	Error;	"wx";	Create a file for writing
	default:
#ifdef __cpp_exceptions
		throw std::system_error(make_error_code(std::errc::invalid_argument));
#else
		fast_terminate();
#endif
	}
}
template<open_mode om>
struct posix_file_openmode
{
	static int constexpr mode = calculate_posix_open_mode(om);
};
}
template<std::integral ch_type>
class basic_posix_io_observer
{
public:
	using char_type = ch_type;
	using native_handle_type = int;
	native_handle_type fd=-1;
	constexpr auto& native_handle() noexcept
	{
		return fd;
	}
	constexpr auto& native_handle() const noexcept
	{
		return fd;
	}
	explicit constexpr operator bool() const noexcept
	{
		return fd!=-1;
	}
#if defined(__WINNT__) || defined(_MSC_VER)
	explicit operator basic_win32_io_observer<char_type>() const
	{
		auto os_handle(_get_osfhandle(fd));
		if(os_handle==-1)
#ifdef __cpp_exceptions
			throw std::system_error(errno,std::system_category());
#else
			fast_terminate();
#endif
		return {bit_cast<void*>(os_handle)};
	}
	explicit operator basic_nt_io_observer<char_type>() const
	{
		return static_cast<basic_nt_io_observer<char_type>>(static_cast<basic_win32_io_observer<char_type>>(*this));
	}
#endif
};

template<std::integral ch_type>
class basic_posix_io_handle:public basic_posix_io_observer<ch_type>
{
protected:
	void close_impl() noexcept
	{
		if(this->native_handle()!=-1)
#if defined(__linux__)&&defined(__x86_64__)
			system_call<3,int>(this->native_handle());
#else
			close(this->native_handle());
#endif
	}
public:
	using char_type = ch_type;
	using native_handle_type = int;

	constexpr explicit basic_posix_io_handle()=default;
	constexpr explicit basic_posix_io_handle(int fdd):basic_posix_io_observer<ch_type>{fdd}{}
	basic_posix_io_handle(basic_posix_io_handle const& dp):basic_posix_io_observer<ch_type>{
#if defined(__linux__)&&defined(__x86_64__)
		system_call<32,int>
#else
		dup
#endif
(dp.native_handle())}
	{
		system_call_throw_error(this->native_handle());
	}
	basic_posix_io_handle& operator=(basic_posix_io_handle const& dp)
	{
		auto newfd(
#if defined(__linux__)&&defined(__x86_64__)
		system_call<33,int>
#else
		dup2
#endif
(dp.native_handle(),this->native_handle()));
		system_call_throw_error(newfd);
		this->native_handle()=newfd;
		return *this;
	}
	constexpr basic_posix_io_handle(basic_posix_io_handle&& b) noexcept : basic_posix_io_handle(b.native_handle())
	{
		b.native_handle() = -1;
	}
	basic_posix_io_handle& operator=(basic_posix_io_handle&& b) noexcept
	{
		if(b.native_handle()!=this->native_handle())
		{
			close_impl();
			this->native_handle()=b.native_handle();
			b.native_handle() = -1;
		}
		return *this;
	}
	void detach()
	{
		this->native_handle()=-1;
	}
};

template<std::integral ch_type>
inline bool valid(basic_posix_io_observer<ch_type>& h)
{
	return h.native_handle()!=-1;
}

template<std::integral ch_type,std::contiguous_iterator Iter>
inline Iter read(basic_posix_io_observer<ch_type>& h,Iter begin,Iter end)
{
	auto read_bytes(
#if defined(__linux__)&&defined(__x86_64__)
		system_call<0,std::ptrdiff_t>
#else
		::read
#endif
	(h.native_handle(),std::to_address(begin),(end-begin)*sizeof(*begin)));
	system_call_throw_error(read_bytes);
	return begin+(read_bytes/sizeof(*begin));
}
template<std::integral ch_type,std::contiguous_iterator Iter>
inline Iter write(basic_posix_io_observer<ch_type>& h,Iter begin,Iter end)
{
	auto write_bytes(
#if defined(__linux__)&&defined(__x86_64__)
		system_call<1,std::ptrdiff_t>
#else
		::write
#endif
(h.native_handle(),std::to_address(begin),(end-begin)*sizeof(*begin)));
	system_call_throw_error(write_bytes);
	return begin+(write_bytes/sizeof(*begin));
}

template<std::integral ch_type,typename T,std::integral R>
inline std::common_type_t<std::int64_t, std::size_t> seek(basic_posix_io_observer<ch_type>& h,seek_type_t<T>,R i=0,seekdir s=seekdir::cur)
{
	auto ret(
#if defined(__linux__)&&defined(__x86_64__)
		system_call<8,std::ptrdiff_t>
#else
		::lseek64
#endif
		(h.native_handle(),seek_precondition<std::int64_t,T,ch_type>(i),static_cast<int>(s)));
	system_call_throw_error(ret);
	return ret;
}
template<std::integral ch_type,std::integral R>
inline auto seek(basic_posix_io_observer<ch_type>& h,R i=0,seekdir s=seekdir::cur)
{
	return seek(h,seek_type<ch_type>,i,s);
}
template<std::integral ch_type>
inline void flush(basic_posix_io_observer<ch_type>&)
{
	// no need fsync. OS can deal with it
//		if(::fsync(fd)==-1)
//			throw std::system_error(errno,std::generic_category());
}

#ifdef __linux__
template<std::integral ch_type>
inline auto zero_copy_in_handle(basic_posix_io_observer<ch_type>& h)
{
	return h.native_handle();
}
template<std::integral ch_type>
inline auto zero_copy_out_handle(basic_posix_io_observer<ch_type>& h)
{
	return h.native_handle();
}
#endif
template<std::integral ch_type>
inline auto redirect_handle(basic_posix_io_observer<ch_type>& h)
{
#if defined(__WINNT__) || defined(_MSC_VER)
	return bit_cast<void*>(_get_osfhandle(h.native_handle()));
#else
	return h.native_handle();
#endif
}

template<std::integral ch_type>
inline void swap(basic_posix_io_observer<ch_type>& a,basic_posix_io_observer<ch_type>& b) noexcept
{
	a.swap(b);
}

template<std::integral ch_type>
class basic_posix_file:public basic_posix_io_handle<ch_type>
{
	void seek_end_local()
	{
		basic_posix_file<ch_type> local{this->native_handle()};
		seek(*this,0,seekdir::end);
		local.detach();
	};
#if defined(__WINNT__) || defined(_MSC_VER)
	using mode_t = int;
#endif
public:
	using char_type = ch_type;
	using native_handle_type = basic_posix_io_handle<char_type>::native_handle_type;
	using basic_posix_io_handle<ch_type>::native_handle;
	constexpr basic_posix_file() noexcept = default;
	constexpr basic_posix_file(int fd) noexcept: basic_posix_io_handle<ch_type>(fd){}
	template<typename ...Args>
	requires requires(Args&& ...args)
	{
		{
#if defined(__WINNT__) || defined(_MSC_VER)
			::_open(
#else
			::openat(AT_FDCWD,
#endif
		std::forward<Args>(args)...)}->std::same_as<int>;
	}
	basic_posix_file(native_interface_t,Args&& ...args):basic_posix_io_handle<ch_type>(
#if defined(__WINNT__) || defined(_MSC_VER)
			::_open(
#else
#if defined(__linux__)&&defined(__x86_64__)
		system_call<257,int>(AT_FDCWD,
#else
		::openat(AT_FDCWD,
#endif
#endif
	std::forward<Args>(args)...))
	{
/*	if(native_handle()<0)
#ifdef __cpp_exceptions
		throw std::system_error(errno,std::generic_category());
#else
		fast_terminate();
#endif*/
		system_call_throw_error(native_handle());
	}
#if defined(__WINNT__) || defined(_MSC_VER)
//windows specific. open posix file from win32 io handle
	template<open_mode om>
	basic_posix_file(basic_win32_io_handle<char_type>&& hd,open_interface_t<om>):
		basic_posix_io_handle<char_type>(::_open_osfhandle(bit_cast<std::intptr_t>(hd.native_handle()),details::posix_file_openmode_for_win32_handle<om>::mode))
	{
		if(native_handle()==-1)
#ifdef __cpp_exceptions
			throw std::system_error(errno,std::generic_category());
#else
			fast_terminate();
#endif
		hd.detach();
	}
	basic_posix_file(basic_win32_io_handle<char_type>&& hd,open_mode m):
		basic_posix_io_handle<char_type>(::_open_osfhandle(bit_cast<std::intptr_t>(hd.native_handle()),details::calculate_posix_open_mode_for_win32_handle(m)))
	{
		if(native_handle()==-1)
#ifdef __cpp_exceptions
			throw std::system_error(errno,std::generic_category());
#else
			fast_terminate();
#endif
		hd.detach();
	}
	basic_posix_file(basic_win32_io_handle<char_type>&& hd,std::string_view mode):basic_posix_file(std::move(hd),from_c_mode(mode)){}
	template<open_mode om,typename... Args>
	basic_posix_file(std::string_view file,open_interface_t<om>,Args&& ...args):
		basic_posix_file(basic_win32_file<char_type>(file,open_interface<om>,std::forward<Args>(args)...),open_interface<om>)
	{}
	template<typename... Args>
	basic_posix_file(std::string_view file,open_mode om,Args&& ...args):
		basic_posix_file(basic_win32_file<char_type>(file,om,std::forward<Args>(args)...),om)
	{}
	template<typename... Args>
	basic_posix_file(std::string_view file,std::string_view mode,Args&& ...args):
		basic_posix_file(basic_win32_file<char_type>(file,mode,std::forward<Args>(args)...),mode)
	{}
#else
	template<open_mode om,perms pm>
	basic_posix_file(std::string_view file,open_interface_t<om>,perms_interface_t<pm>):basic_posix_file(native_interface,file.data(),details::posix_file_openmode<om>::mode,static_cast<mode_t>(pm))
	{
		if constexpr ((om&open_mode::ate)!=open_mode::none)
			seek_end_local();
	}
	template<open_mode om>
	basic_posix_file(std::string_view file,open_interface_t<om>):basic_posix_file(native_interface,file.data(),details::posix_file_openmode<om>::mode,static_cast<mode_t>(436))
	{
		if constexpr ((om&open_mode::ate)!=open_mode::none)
			seek_end_local();
	}
	template<open_mode om>
	basic_posix_file(std::string_view file,open_interface_t<om>,perms pm):basic_posix_file(native_interface,file.data(),details::posix_file_openmode<om>::mode,static_cast<mode_t>(pm))
	{
		if constexpr ((om&open_mode::ate)!=open_mode::none)
			seek_end_local();
	}
	//potential support modification prv in the future
	basic_posix_file(std::string_view file,open_mode om,perms pm=static_cast<perms>(436)):basic_posix_file(native_interface,file.data(),details::calculate_posix_open_mode(om),static_cast<mode_t>(pm))
	{
		if((om&open_mode::ate)!=open_mode::none)
			seek_end_local();
	}
	basic_posix_file(std::string_view file,std::string_view mode,perms pm=static_cast<perms>(436)):basic_posix_file(file,from_c_mode(mode),pm){}
#endif
	~basic_posix_file()
	{
		this->close_impl();
	}
};

template<std::integral ch_type>
inline void truncate(basic_posix_io_observer<ch_type>& h,std::size_t size)
{
#if defined(__WINNT__) || defined(_MSC_VER)
	auto err(_chsize_s(h.native_handle(),size));
	if(err)
#ifdef __cpp_exceptions
		throw std::system_error(err,std::generic_category());
#else
		fast_terminate();
#endif
#else
	if(::ftruncate(h.native_handle(),size)<0)
#ifdef __cpp_exceptions
		throw std::system_error(errno,std::generic_category());
#else
		fast_terminate();
#endif
#endif
}

template<std::integral ch_type>
class basic_posix_pipe
{
public:
	using char_type = ch_type;
	using native_handle_type = std::array<basic_posix_file<ch_type>,2>;
private:
	native_handle_type pipes;
public:
	basic_posix_pipe()
	{
		std::array<int,2> a2{pipes.front().native_handle(),pipes.back().native_handle()};
#if defined(__WINNT__) || defined(_MSC_VER)
		if(_pipe(a2.data(),1048576,_O_BINARY)==-1)
#else
		if(::pipe(a2.data())==-1)
#endif
#ifdef __cpp_exceptions
			throw std::system_error(errno,std::generic_category());
#else
			fast_terminate();
#endif
		pipes.front().native_handle()=a2.front();
		pipes.back().native_handle()=a2.back();
	}
	auto& native_handle()
	{
		return pipes;
	}
	auto& in()
	{
		return pipes.front();
	}
	auto& out()
	{
		return pipes.back();
	}
	void swap(basic_posix_pipe& o) noexcept
	{
		using std::swap;
		swap(pipes,o.pipes);
	}
};
template<std::integral ch_type>
inline void swap(basic_posix_pipe<ch_type>& a,basic_posix_pipe<ch_type>& b) noexcept
{
	a.swap(b);
}

template<std::integral ch_type,std::contiguous_iterator Iter>
inline Iter read(basic_posix_pipe<ch_type>& h,Iter begin,Iter end)
{
	return read(h.in(),begin,end);
}
template<std::integral ch_type,std::contiguous_iterator Iter>
inline Iter write(basic_posix_pipe<ch_type>& h,Iter begin,Iter end)
{
	return write(h.out(),begin,end);
}

template<std::integral ch_type>
inline void flush(basic_posix_pipe<ch_type>&)
{
	// no need fsync. OS can deal with it
//		if(::fsync(fd)==-1)
//			throw std::system_error(errno,std::generic_category());
}

template<std::integral ch_type>
inline std::array<int*,2> redirect_handle(basic_posix_pipe<ch_type>& h)
{
	return {std::addressof(h.in().native_handle()),
		std::addressof(h.out().native_handle())};
}

#ifdef __linux__
template<std::integral ch_type>
inline auto zero_copy_in_handle(basic_posix_pipe<ch_type>& h)
{
	return h.in().native_handle();
}
template<std::integral ch_type>
inline auto zero_copy_out_handle(basic_posix_pipe<ch_type>& h)
{
	return h.out().native_handle();
}
#endif

using posix_io_observer=basic_posix_io_observer<char>;
using posix_io_handle=basic_posix_io_handle<char>;
using posix_file=basic_posix_file<char>;
using posix_pipe=basic_posix_pipe<char>;

using u8posix_io_observer=basic_posix_io_observer<char8_t>;
using u8posix_io_handle=basic_posix_io_handle<char8_t>;
using u8posix_file=basic_posix_file<char8_t>;
using u8posix_pipe=basic_posix_pipe<char8_t>;

using wposix_io_observer=basic_posix_io_observer<wchar_t>;
using wposix_io_handle=basic_posix_io_handle<wchar_t>;
using wposix_file=basic_posix_file<wchar_t>;
using wposix_pipe=basic_posix_pipe<wchar_t>;

inline int constexpr posix_stdin_number = 0;
inline int constexpr posix_stdout_number = 1;
inline int constexpr posix_stderr_number = 2;
#ifdef __linux__

//zero copy IO for linux
namespace details
{


template<bool random_access=false,bool report_einval=false,zero_copy_output_stream output,zero_copy_input_stream input>
inline std::conditional_t<report_einval,std::pair<std::size_t,bool>,std::size_t>
	zero_copy_transmit_once(output& outp,input& inp,std::size_t bytes,std::intmax_t offset)
{
	std::intmax_t *np{};
	if constexpr(random_access)
		np=std::addressof(offset);
	auto transmitted_bytes(::sendfile(zero_copy_out_handle(outp),zero_copy_in_handle(inp),np,bytes));
	if(transmitted_bytes==-1)
	{
		if constexpr(report_einval)
		{
			auto const eno(errno);
			if(eno==EINVAL)
				return {0,true};
			else
			{
			#ifdef __cpp_exceptions
				throw std::system_error(eno,std::generic_category());
			#else
				fast_terminate();
			#endif
			}
		}
		else
		{
			#ifdef __cpp_exceptions
				throw std::system_error(errno,std::generic_category());
			#else
				fast_terminate();
			#endif
		}
	}
	if constexpr(report_einval)
		return {transmitted_bytes,false};
	else
		return transmitted_bytes;
}


template<bool random_access=false,bool report_einval=false,zero_copy_output_stream output,zero_copy_input_stream input>
inline std::conditional_t<report_einval,std::pair<std::uintmax_t,bool>,std::uintmax_t> zero_copy_transmit
(output& outp,input& inp,std::uintmax_t bytes,std::intmax_t offset)
{
	constexpr std::size_t maximum_transmit_bytes(2147479552);
	std::uintmax_t transmitted{};
	for(;bytes;)
	{
		std::size_t should_transfer(maximum_transmit_bytes);
		if(bytes<should_transfer)
			should_transfer=bytes;
		std::size_t transferred_this_round{};
		auto ret(details::zero_copy_transmit_once<random_access,report_einval>(outp,inp,should_transfer,offset));
		if constexpr(report_einval)
		{
			if(ret.second)
				return {transmitted,true};
			transferred_this_round=ret.first;
		}
		else
			transferred_this_round=ret;
		transmitted+=transferred_this_round;
		if(transferred_this_round!=should_transfer)
		{
			if constexpr(report_einval)
				return {transmitted,false};
			else
				return transmitted;
		}
		bytes-=transferred_this_round;
	}
	if constexpr(report_einval)
		return {transmitted,false};
	else
		return transmitted;
}
template<bool random_access=false,bool report_einval=false,zero_copy_output_stream output,zero_copy_input_stream input>
inline std::conditional_t<report_einval,std::pair<std::uintmax_t,bool>,std::uintmax_t> zero_copy_transmit(output& outp,input& inp,std::intmax_t offset)
{
	constexpr std::size_t maximum_transmit_bytes(2147479552);
	for(std::uintmax_t transmitted{};;)
	{
		std::size_t transferred_this_round{};
		auto ret(details::zero_copy_transmit_once<random_access,report_einval>(outp,inp,maximum_transmit_bytes,offset));
		if constexpr(report_einval)
		{
			if(ret.second)
				return {transmitted,true};
			transferred_this_round=ret.first;
		}
		else
			transferred_this_round=ret;
		transmitted+=transferred_this_round;
		if(transferred_this_round!=maximum_transmit_bytes)
		{
			if constexpr(report_einval)
				return {transmitted,false};
			else
				return transmitted;
		}
	}
}
}

#endif

inline constexpr posix_io_handle posix_stdin()
{
	return posix_io_handle(posix_stdin_number);
}
inline constexpr posix_io_handle posix_stdout()
{
	return posix_io_handle(posix_stdout_number);
} 
inline constexpr posix_io_handle posix_stderr()
{
	return posix_io_handle(posix_stderr_number);
}

template<output_stream output,std::integral intg>
inline constexpr void print_define(output& out,basic_posix_io_observer<intg> iob)
{
	print(out,iob.native_handle());
}

}
