#pragma once
#include<cstdio>
#include<cwchar>

namespace fast_io
{

struct c_file_cookie_t
{
explicit constexpr c_file_cookie_t()=default;
};
inline constexpr c_file_cookie_t c_file_cookie{};

namespace details
{
template<open_mode om>
struct c_open_mode
{
inline static constexpr std::string_view value=to_c_mode(om);
};

}
template<std::integral ch_type>
class basic_c_io_observer_unlocked
{
public:
	std::FILE *fp=nullptr;
	using char_type = ch_type;
	using native_handle_type = std::FILE*;
	constexpr auto& native_handle() noexcept
	{
		return fp;
	}
	constexpr auto& native_handle() const noexcept
	{
		return fp;
	}
	explicit operator bool() const noexcept
	{
		return fp;
	}
	explicit operator basic_posix_io_observer<char_type>() const
	{

		auto fd(
#if defined(__WINNT__) || defined(_MSC_VER)
	_fileno(fp)
#else
	::fileno_unlocked(fp)
#endif
);
		if(fd<0)
#ifdef __cpp_exceptions
			throw std::system_error(errno,std::system_category());
#else
			fast_terminate();
#endif
		return basic_posix_io_observer<char_type>{fd};
	}
#if defined(__WINNT__) || defined(_MSC_VER)
	explicit operator basic_win32_io_observer<char_type>() const
	{
		return static_cast<basic_win32_io_observer<char_type>>(static_cast<basic_posix_io_observer<char_type>>(*this));
	}
#endif
};

template<std::integral ch_type>
inline auto redirect_handle(basic_c_io_observer_unlocked<ch_type>& h)
{
#if defined(__WINNT__) || defined(_MSC_VER)
	return static_cast<basic_win32_io_observer<ch_type>>(h).native_handle();
#else
	return static_cast<basic_posix_io_observer<ch_type>>(h).native_handle();
#endif
}

using c_io_observer_unlocked = basic_c_io_observer_unlocked<char>;

template<std::integral T,std::contiguous_iterator Iter>
inline Iter read(basic_c_io_observer_unlocked<T> cfhd,Iter begin,Iter end)
{
	std::size_t const count(end-begin);
	std::size_t const r(
//mingw
#ifdef _MSC_VER
	_fread_nolock
#elif _POSIX_SOURCE
	fread_unlocked
#else
	fread
#endif
	(std::to_address(begin),sizeof(*begin),count,cfhd.native_handle()));
	if(r==count||std::feof(cfhd.native_handle()))
		return begin+r;
#ifdef __cpp_exceptions
	throw std::system_error(errno,std::generic_category());
#else
	fast_terminate();
#endif
}

template<std::integral T,std::contiguous_iterator Iter>
inline void write(basic_c_io_observer_unlocked<T> cfhd,Iter begin,Iter end)
{
	std::size_t const count(end-begin);
	if(
#ifdef _MSC_VER
	_fwrite_nolock
#elif defined(_POSIX_SOURCE)
	fwrite_unlocked
#else
	fwrite
#endif
	(std::to_address(begin),sizeof(*begin),count,cfhd.native_handle())<count)
#ifdef __cpp_exceptions
		throw std::system_error(errno,std::system_category());
#else
		fast_terminate();
#endif
}

template<std::integral T>
inline void flush(basic_c_io_observer_unlocked<T>& cfhd)
{
	if(
#if defined(_MSC_VER)
		_fflush_nolock
#elif defined(_POSIX_SOURCE)
		fflush_unlocked
#else
		fflush
#endif
	(cfhd.native_handle()))
#ifdef __cpp_exceptions
		throw std::system_error(errno,std::system_category());
#else
		fast_terminate();
#endif
}

template<std::integral ch_type,typename T,std::integral U>
inline auto seek(basic_c_io_observer_unlocked<ch_type> cfhd,seek_type_t<T>,U i,seekdir s=seekdir::beg)
{
	if(
#if defined(__WINNT__) || defined(_MSC_VER)
		_fseek_nolock
#elif defined(_POSIX_SOURCE)
		fseek_unlocked
#else
		fseek
#endif
	(cfhd.native_handle(),seek_precondition<long,T,char>(i),static_cast<int>(s)))
		throw std::system_error(errno,std::system_category()); 
	auto val(std::ftell(cfhd.native_handle()));
	if(val<0)
#ifdef __cpp_exceptions
		throw std::system_error(errno,std::system_category());
#else
		fast_terminate();
#endif
	return val;
}

template<std::integral ch_type,std::integral U>
inline auto seek(basic_c_io_observer_unlocked<ch_type> cfhd,U i,seekdir s=seekdir::beg)
{
	return seek(cfhd,seek_type<char>,i,s);
}

class c_io_lock_guard;

template<std::integral ch_type>
class basic_c_io_observer
{
public:
	std::FILE *fp=nullptr;
	using lock_guard_type = c_io_lock_guard;
	using char_type = ch_type;
	using native_handle_type = std::FILE*;
	constexpr auto& native_handle() const noexcept
	{
		return fp;
	}
	constexpr auto& native_handle() noexcept
	{
		return fp;
	}
	explicit operator bool() const noexcept
	{
		return fp;
	}
	explicit operator basic_posix_io_observer<char_type>() const
	{
		auto fd(
#if defined(__WINNT__) || defined(_MSC_VER)
	_fileno(fp)
#else
	::fileno(fp)
#endif
);
		if(fd<0)
#ifdef __cpp_exceptions
			throw std::system_error(errno,std::system_category());
#else
			fast_terminate();
#endif
		return basic_posix_io_observer<char_type>{fd};
	}
#if defined(__WINNT__) || defined(_MSC_VER)
	explicit operator basic_win32_io_observer<char_type>() const
	{
		return static_cast<basic_win32_io_observer<char_type>>(static_cast<basic_posix_io_observer<char_type>>(*this));
	}
	explicit operator basic_nt_io_observer<char_type>() const
	{
		return static_cast<basic_nt_io_observer<char_type>>(static_cast<basic_posix_io_observer<char_type>>(*this));
	}
#endif
};

template<std::integral T>
inline auto mutex(basic_c_io_observer<T>& h)
{
	return h.native_handle();
}
template<std::integral T>
inline basic_c_io_observer_unlocked<T> unlocked_handle(basic_c_io_observer<T>& h)
{
	return {h.native_handle()};
}

class c_io_lock_guard
{
	std::FILE* const fp;
public:
	c_io_lock_guard(std::FILE* f):fp(f)
	{
#if defined(__WINNT__) || defined(_MSC_VER)
		_lock_file(fp);
#else
		flockfile(fp);
#endif
	}
	c_io_lock_guard(c_io_lock_guard const&) = delete;
	c_io_lock_guard& operator=(c_io_lock_guard const&) = delete;
	~c_io_lock_guard()
	{
#if defined(__WINNT__) || defined(_MSC_VER)
		_unlock_file(fp);
#else
		funlockfile(fp);
#endif
	}
};


template<std::integral T,std::contiguous_iterator Iter>
inline Iter read(basic_c_io_observer<T> cfhd,Iter begin,Iter end)
{
	std::size_t const count(end-begin);
	std::size_t const r(std::fread(std::to_address(begin),sizeof(*begin),count,cfhd.native_handle()));
	if(r==count||std::feof(cfhd.native_handle()))
		return begin+r;
#ifdef __cpp_exceptions
	throw std::system_error(errno,std::system_category());
#else
	fast_terminate();
#endif
}

template<std::integral T,std::contiguous_iterator Iter>
inline void write(basic_c_io_observer<T> cfhd,Iter begin,Iter end)
{
	std::size_t const count(end-begin);
	if(std::fwrite(std::to_address(begin),sizeof(*begin),count,cfhd.native_handle())<count)
#ifdef __cpp_exceptions
		throw std::system_error(errno,std::system_category());
#else
		fast_terminate();
#endif
}

template<std::integral T>
inline void flush(basic_c_io_observer<T> cfhd)
{
	if(std::fflush(cfhd.native_handle()))
#ifdef __cpp_exceptions
		throw std::system_error(errno,std::system_category());
#else
		fast_terminate();
#endif
}

template<typename P,typename T,std::integral U>
inline auto seek(basic_c_io_observer<P>& cfhd,seek_type_t<T>,U i,seekdir s=seekdir::beg)
{
	if(std::fseek(cfhd.native_handle(),seek_precondition<long,T,typename basic_c_io_observer<P>::char_type>(i),static_cast<int>(s)))
#ifdef __cpp_exceptions
		throw std::system_error(errno,std::system_category());
#else
		fast_terminate();
#endif
	auto val(std::ftell(cfhd.native_handle()));
	if(val<0)
#ifdef __cpp_exceptions
		throw std::system_error(errno,std::system_category());
#else
		fast_terminate();
#endif
	return val;
}

template<typename P,std::integral U>
inline auto seek(basic_c_io_observer<P>& cfhd,U i,seekdir s=seekdir::beg)
{
	return seek(cfhd,seek_type<typename basic_c_io_observer<P>::char_type>,i,s);
}
namespace details
{
template<typename T>
class basic_c_io_handle_impl:public T
{
protected:
	void close_impl() noexcept
	{
		if(this->native_handle())
			std::fclose(this->native_handle());
	}
public:
	using char_type = typename T::char_type;
	using native_handle_type = std::FILE*;
	constexpr basic_c_io_handle_impl()=default;
	constexpr basic_c_io_handle_impl(native_handle_type fp2) noexcept:T{fp2}{}
	basic_c_io_handle_impl(basic_c_io_handle_impl const&)=delete;
	basic_c_io_handle_impl& operator=(basic_c_io_handle_impl const&)=delete;
	constexpr basic_c_io_handle_impl(basic_c_io_handle_impl&& b) noexcept : T{b.native_handle()}
	{
		b.native_handle() = nullptr;
	}
	basic_c_io_handle_impl& operator=(basic_c_io_handle_impl&& b) noexcept
	{
		if(b.native_handle()!=this->native_handle())
		{
			close_impl();
			this->native_handle()=b.native_handle();
			b.native_handle() = nullptr;
		}
		return *this;
	}
	constexpr void detach() noexcept
	{
		this->native_handle() = nullptr;
	}
};


template<typename T>
class basic_c_file_impl:public T
{
public:
	using T::native_handle;
	using char_type=typename T::char_type;
	using native_handle_type=typename T::native_handle_type;
	basic_c_file_impl()=default;
	basic_c_file_impl(native_handle_type hd):T(hd){}
/*
	basic_c_file_impl(std::string_view name,std::string_view mode):T(std::fopen(name.data(),mode.data()))
	{
		if(native_handle()==nullptr)
#ifdef __cpp_exceptions
			throw std::system_error(errno,std::system_category());
#else
			fast_terminate();
#endif
	}
	basic_c_file_impl(std::string_view file,open_mode const& m):basic_c_file_impl(file,c_style(m))
	{
		if(with_ate(m))
			seek(*this,0,seekdir::end);
	}*/
//fdopen interface

	basic_c_file_impl(basic_posix_io_handle<typename T::char_type>&& posix_handle,std::string_view mode):T(
#if defined(__WINNT__) || defined(_MSC_VER)
			::_fdopen
#else
			::fdopen
#endif
(posix_handle.native_handle(),mode.data()))
	{
		if(native_handle()==nullptr)
#ifdef __cpp_exceptions
			throw std::system_error(errno,std::system_category());
#else
			fast_terminate();
#endif
		posix_handle.detach();
		if constexpr(std::same_as<wchar_t,typename T::char_type>)
		{
			fwide(this->native_handle(),1);
		}
		else if constexpr(!std::same_as<char,typename T::char_type>)
		{
		//close buffer for non char and wchar_t types like libstdc++ does. All these hacks just violate strict-aliasing rule
			if(setvbuf(this->native_handle(),nullptr,_IONBF,0))
			{
#ifdef __cpp_exceptions
				std::fclose(this->native_handle());
				throw std::system_error(errno,std::generic_category());
#else
				fast_terminate();
#endif
			}
		}
	}

	basic_c_file_impl(basic_posix_io_handle<char_type>&& posix_handle,open_mode om):
		basic_c_file_impl(std::move(posix_handle),to_c_mode(om)){}
	template<open_mode om>
	basic_c_file_impl(basic_posix_io_handle<char_type>&& posix_handle,open_interface_t<om>):
		basic_c_file_impl(std::move(posix_handle),details::c_open_mode<om>::value){}

#if defined(__WINNT__) || defined(_MSC_VER)
//windows specific. open posix file from win32 io handle
	basic_c_file_impl(basic_win32_io_handle<char_type>&& win32_handle,std::string_view mode):
		basic_c_file_impl(basic_posix_file<char_type>(std::move(win32_handle),mode),mode)
	{
	}
	basic_c_file_impl(basic_win32_io_handle<char_type>&& win32_handle,open_mode om):
		basic_c_file_impl(basic_posix_file<char_type>(std::move(win32_handle),om),to_c_mode(om))
	{
	}
	template<open_mode om>
	basic_c_file_impl(basic_win32_io_handle<char_type>&& win32_handle,open_interface_t<om>):
		basic_c_file_impl(basic_posix_file<char_type>(std::move(win32_handle),open_interface<om>),
			details::c_open_mode<om>::value)//open::c_style_interface_t<om>::mode)
	{
	}
#endif

	template<open_mode om,typename... Args>
	basic_c_file_impl(std::string_view file,open_interface_t<om>,Args&& ...args):
		basic_c_file_impl(basic_posix_file<typename T::char_type>(file,open_interface<om>,std::forward<Args>(args)...),
			open_interface<om>)
	{}
	template<typename... Args>
	basic_c_file_impl(std::string_view file,open_mode om,Args&& ...args):
		basic_c_file_impl(basic_posix_file<typename T::char_type>(file,om,std::forward<Args>(args)...),om)
	{}
	template<typename... Args>
	basic_c_file_impl(std::string_view file,std::string_view mode,Args&& ...args):
		basic_c_file_impl(basic_posix_file<typename T::char_type>(file,mode,std::forward<Args>(args)...),mode)
	{}
	template<stream stm,typename... Args>
	requires (std::same_as<typename T::char_type,char>&&std::same_as<typename stm::char_type,char>)
	basic_c_file_impl(c_file_cookie_t,std::string_view mode,std::in_place_type_t<stm>,Args&& ...args)
#if defined(_GNU_SOURCE)
//musl libc also supports this I think
//https://gitlab.com/bminor/musl/-/blob/061843340fbf2493bb615e20e66f60c5d1ef0455/src/stdio/fopencookie.c
	{
		cookie_io_functions_t io_funcs{.close=[](void* cookie) noexcept->int
		{
			delete bit_cast<stm*>(cookie);
			return 0;
		}};
		if constexpr(input_stream<stm>)
			io_funcs.read=[](void* cookie,char* buf,std::size_t size) noexcept->std::ptrdiff_t
			{
				try
				{
					return read(*bit_cast<stm*>(cookie),buf,buf+size)-buf;
				}
				catch(std::system_error const& err)
				{
					if(err.code().category()==std::generic_category())
						errno=err.code().value();
					else
						errno=EIO;
					return -1;
				}
				catch(...)
				{
					errno=EIO;
					return -1;
				}
			};
		if constexpr(output_stream<stm>)
		{
			io_funcs.write=[](void* cookie,char const* buf,std::size_t size) noexcept->std::ptrdiff_t
			{
				try
				{
					if constexpr(std::same_as<decltype(write(*bit_cast<stm*>(cookie),buf,buf+size)),void>)
					{
						write(*bit_cast<stm*>(cookie),buf,buf+size);
						return static_cast<std::ptrdiff_t>(size);
					}
					else
						return write(*bit_cast<stm*>(cookie),buf,buf+size)-buf;
				}
				catch(std::system_error const& err)
				{
					if(err.code().category()==std::generic_category())
						errno=err.code().value();
					else
						errno=EIO;
					return -1;
				}
				catch(...)
				{
					errno=EIO;
					return -1;
				}
			};
		}
		if constexpr(random_access_stream<stm>)
		{
			io_funcs.seek=[](void *cookie, off64_t *offset, int whence) noexcept->int
			{
				try
				{
					*offset=seek(*bit_cast<stm*>(cookie),*offset,static_cast<fast_io::seekdir>(whence));
					return 0;
				}
				catch(std::system_error const& err)
				{
					if(err.code().category()==std::generic_category())
						errno=err.code().value();
					else
						errno=EIO;
					return -1;
				}
				catch(...)
				{
					errno=EIO;
					return -1;
				}
			};
		}
		std::unique_ptr<stm> up{std::make_unique<stm>(std::forward<Args>(args)...)};
		if(!(this->native_handle()=fopencookie(up.get(),mode.data(),io_funcs)))[[unlikely]]
			throw std::system_error(errno,std::generic_category());
		up.release();
	}
/*
#elif defined(__unix__) || (defined(__APPLE__) && defined(__MACH__)) || defined (__BIONIC__)
Todo
	{

	}
*/
#else
//not supported platform like windows MSVCRT. We throw std::errc::operation_not_supported

	{
#ifdef __cpp_exceptions
		throw std::system_error(std::make_error_code(std::errc::operation_not_supported));
#else
		fast_terminate();
#endif
	}
#endif


	template<stream stm>
	requires (std::same_as<typename T::char_type,char>&&std::same_as<typename stm::char_type,char>)
	basic_c_file_impl(c_file_cookie_t,std::string_view mode,std::reference_wrapper<stm> reff)
#if defined(_GNU_SOURCE)
//musl libc also supports this I think
//https://gitlab.com/bminor/musl/-/blob/061843340fbf2493bb615e20e66f60c5d1ef0455/src/stdio/fopencookie.c
	{
		cookie_io_functions_t io_funcs{};
		if constexpr(input_stream<stm>)
			io_funcs.read=[](void* cookie,char* buf,std::size_t size) noexcept->std::ptrdiff_t
			{
				try
				{
					return read(*bit_cast<stm*>(cookie),buf,buf+size)-buf;
				}
				catch(std::system_error const& err)
				{
					if(err.code().category()==std::generic_category())
						errno=err.code().value();
					else
						errno=EIO;
					return -1;
				}
				catch(...)
				{
					errno=EIO;
					return -1;
				}
			};
		if constexpr(output_stream<stm>)
		{
			io_funcs.write=[](void* cookie,char const* buf,std::size_t size) noexcept->std::ptrdiff_t
			{
				try
				{
					if constexpr(std::same_as<decltype(write(*bit_cast<stm*>(cookie),buf,buf+size)),void>)
					{
						write(*bit_cast<stm*>(cookie),buf,buf+size);
						return static_cast<std::ptrdiff_t>(size);
					}
					else
						return write(*bit_cast<stm*>(cookie),buf,buf+size)-buf;
				}
				catch(std::system_error const& err)
				{
					if(err.code().category()==std::generic_category())
						errno=err.code().value();
					else
						errno=EIO;
					return -1;
				}
				catch(...)
				{
					errno=EIO;
					return -1;
				}
			};
		}
		if constexpr(random_access_stream<stm>)
		{
			io_funcs.seek=[](void *cookie, off64_t *offset, int whence) noexcept->int
			{
				try
				{
					*offset=seek(*bit_cast<stm*>(cookie),*offset,static_cast<fast_io::seekdir>(whence));
					return 0;
				}
				catch(std::system_error const& err)
				{
					if(err.code().category()==std::generic_category())
						errno=err.code().value();
					else
						errno=EIO;
					return -1;
				}
				catch(...)
				{
					errno=EIO;
					return -1;
				}
			};
		}
		if(!(this->native_handle()=fopencookie(std::addressof(reff.get()),mode.data(),io_funcs)))[[unlikely]]
			throw std::system_error(errno,std::generic_category());
	}
/*
#elif defined(__unix__) || (defined(__APPLE__) && defined(__MACH__)) || defined (__BIONIC__)
Todo
	{

	}
*/
#else
//not supported platform like windows MSVCRT. We throw std::errc::operation_not_supported

	{
#ifdef __cpp_exceptions
		throw std::system_error(std::make_error_code(std::errc::operation_not_supported));
#else
		fast_terminate();
#endif
	}
#endif

	basic_c_file_impl(basic_c_file_impl const&)=delete;
	basic_c_file_impl& operator=(basic_c_file_impl const&)=delete;
	constexpr basic_c_file_impl(basic_c_file_impl&& b) noexcept :T(std::move(b)){}
	basic_c_file_impl& operator=(basic_c_file_impl&& b) noexcept
	{
		static_cast<T&>(*this)=std::move(b);
		return *this;
	}
	~basic_c_file_impl()
	{
		this->close_impl();
	}
	constexpr native_handle_type release() noexcept
	{
		auto temp{this->native_handle()};
		this->detach();
		return temp;
	}
};

}

template<std::integral ch_type>
using basic_c_io_handle=details::basic_c_io_handle_impl<basic_c_io_observer<ch_type>>;

template<std::integral ch_type>
using basic_c_file=details::basic_c_file_impl<basic_c_io_handle<ch_type>>;

template<std::integral ch_type>
using basic_c_io_handle_unlocked=details::basic_c_io_handle_impl<basic_c_io_observer_unlocked<ch_type>>;

template<std::integral ch_type>
using basic_c_file_unlocked=details::basic_c_file_impl<basic_c_io_handle_unlocked<ch_type>>;


template<std::integral ch_type>
inline auto redirect_handle(basic_c_io_observer<ch_type>& h)
{
#if defined(__WINNT__) || defined(_MSC_VER)
	return static_cast<basic_win32_io_observer<ch_type>>(h).native_handle();
#else
	return static_cast<basic_posix_io_observer<ch_type>>(h).native_handle();
#endif
}

using c_io_observer_unlocked=basic_c_io_observer_unlocked<char>;
using c_io_observer=basic_c_io_observer<char>;
using c_io_handle_unlocked = basic_c_io_handle_unlocked<char>;
using c_io_handle = basic_c_io_handle<char>;
using c_file = basic_c_file<char>;
using c_file_unlocked = basic_c_file_unlocked<char>;

using wc_io_observer_unlocked=basic_c_io_observer_unlocked<wchar_t>;
using wc_io_observer=basic_c_io_observer<wchar_t>;
using wc_io_handle_unlocked = basic_c_io_handle_unlocked<wchar_t>;
using wc_io_handle = basic_c_io_handle<wchar_t>;
using wc_file = basic_c_file<wchar_t>;
using wc_file_unlocked = basic_c_file_unlocked<wchar_t>;

#ifdef __linux__
template<std::integral ch_type>
inline auto zero_copy_in_handle(basic_c_io_observer_unlocked<ch_type>& h)
{
	return ::fileno_unlocked(h.native_handle());
}
template<std::integral ch_type>
inline auto zero_copy_out_handle(basic_c_io_observer_unlocked<ch_type>& h)
{
	return ::fileno_unlocked(h.native_handle());
}
#endif


template<output_stream output,std::integral intg>
inline constexpr void print_define(output& out,basic_c_io_observer_unlocked<intg> iob)
{
	print(out,fast_io::unsigned_view(iob.native_handle()));
}

template<output_stream output,std::integral intg>
inline constexpr void print_define(output& out,basic_c_io_observer<intg> iob)
{
	print(out,fast_io::unsigned_view(iob.native_handle()));
}

}
#ifdef _MSC_VER
#include"universal_crt.h"
#elif defined(__WINNT__)
#include"msvcrt.h"
#elif defined(__GLIBC__)
#include"glibc.h"
#else
#include"general.h"
#endif