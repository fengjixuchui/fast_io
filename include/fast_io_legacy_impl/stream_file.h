#pragma once

namespace fast_io
{

namespace details
{

inline constexpr std::ios::openmode calculate_fstream_file_open_mode(open_mode om)
{
	std::ios::openmode ios_om{};
	if((om&open_mode::app)!=open_mode::none)
		ios_om=ios_om|std::ios::app;
	if((om&open_mode::binary)!=open_mode::none)
		ios_om=ios_om|std::ios::binary;
	if((om&open_mode::in)!=open_mode::none)
		ios_om=ios_om|std::ios::in;
	if((om&open_mode::out)!=open_mode::none)
		ios_om=ios_om|std::ios::out;
	if((om&open_mode::trunc)!=open_mode::none)
		ios_om=ios_om|std::ios::trunc;
	if((om&open_mode::ate)!=open_mode::none)
		ios_om=ios_om|std::ios::ate;
	return ios_om;
}

template<open_mode om>
struct fstream_open_mode
{
	inline static constexpr auto value=calculate_fstream_file_open_mode(om);
};

}


template<typename stream_type>
requires std::same_as<typename stream_type::char_type,typename stream_type::traits_type::char_type>
class basic_stream_file
{
public:
	using char_type = typename stream_type::char_type;
	using traits_type = typename stream_type::traits_type;
	using filebuf_type =
#ifdef __GLIBCXX__
__gnu_cxx::stdio_filebuf
#elif defined(_MSC_VER)
std::basic_filebuf
#endif
<char_type,traits_type>;

	using c_io_handle_type = basic_c_io_handle_unlocked<char_type>;
	using c_file_type = basic_c_file_unlocked<char_type>;
private:
	c_file_type bcf;
	filebuf_type hd;
	stream_type stm;
public:
	using native_handle_type = stream_type;
	template<open_mode om>
	basic_stream_file(c_io_handle_type&& ciohd,open_interface_t<om>):
		bcf(std::move(static_cast<c_file_type&&>(ciohd))),
		hd(bcf.native_handle()
#ifdef __GLIBCXX__
,details::fstream_open_mode<om>::value,65536
#endif
),stm(std::addressof(hd))
	{
		stm.rdbuf(std::addressof(hd));
		if(!stm)
#ifdef __cpp_exceptions
			throw posix_error(EIO);
#else
			fast_terminate();
#endif
#ifdef __GLIBCXX__
		std::setbuf(bcf.native_handle(),nullptr);
#endif
	}

	basic_stream_file(c_io_handle_type&& ciohd,open_mode om):
		bcf(std::move(static_cast<c_file_type&&>(ciohd))),hd(bcf.native_handle()
#ifdef __GLIBCXX__
,details::calculate_fstream_file_open_mode(om),65536
#endif
),stm(std::addressof(hd))
	{
		if(!stm)
#ifdef __cpp_exceptions
			throw posix_error(EIO);
#else
			fast_terminate();
#endif
#ifdef __GLIBCXX__
		std::setbuf(bcf.native_handle(),nullptr);
#endif
	}
	basic_stream_file(c_io_handle_type&& ciohd,std::string_view om):
		bcf(std::move(static_cast<c_file_type&&>(ciohd))),hd(bcf.native_handle()
#ifdef __GLIBCXX__
,from_c_mode(om),65536
#endif
),stm(std::addressof(hd))
	{
		if(!stm)
#ifdef __cpp_exceptions
			throw posix_error(EIO);
#else
			fast_terminate();
#endif
		std::setbuf(bcf.native_handle(),nullptr);
	}

	template<open_mode om>
	basic_stream_file(basic_posix_io_handle<char_type>&& ciohd,open_interface_t<om>):
		basic_stream_file(c_file_type(std::move(ciohd),open_interface<om>),open_interface<om>){}

	basic_stream_file(basic_posix_io_handle<char_type>&& ciohd,open_mode om):
		basic_stream_file(c_file_type(std::move(ciohd),om),om){}

	basic_stream_file(basic_posix_io_handle<char_type>&& ciohd,std::string_view om):
		basic_stream_file(c_file_type(std::move(ciohd),om),om){}

#if defined(__WINNT__) || defined(_MSC_VER)
	template<open_mode om>
	basic_stream_file(basic_win32_io_handle<char_type>&& ciohd,open_interface_t<om>):
		basic_stream_file(c_file_type(std::move(ciohd),open_interface<om>),open_interface<om>){}

	basic_stream_file(basic_win32_io_handle<char_type>&& ciohd,open_mode om):
		basic_stream_file(c_file_type(std::move(ciohd),om),om){}

	basic_stream_file(basic_win32_io_handle<char_type>&& ciohd,std::string_view om):
		basic_stream_file(c_file_type(std::move(ciohd),om),om){}
#endif

	template<open_mode om,typename... Args>
	basic_stream_file(std::string_view file,open_interface_t<om>,Args&& ...args):
		basic_stream_file(c_file_type(file,open_interface<om>,std::forward<Args>(args)...),
			open_interface<om>)
	{}

	template<typename... Args>
	basic_stream_file(std::string_view file,open_mode om,Args&& ...args):
		basic_stream_file(c_file_type(file,om,std::forward<Args>(args)...),om)
	{}
	template<typename... Args>
	basic_stream_file(std::string_view file,std::string_view mode,Args&& ...args):
		basic_stream_file(c_file_type(file,mode,std::forward<Args>(args)...),mode)
	{}

	native_handle_type& native_handle()
	{
		return stm;
	}
	c_file_type& c_file()
	{
		return bcf;
	}
	filebuf_type& filebuf()
	{
		return hd;
	}
	explicit operator basic_c_io_observer_unlocked<char_type>() const
	{
		return bcf.native_handle();
	}
	explicit operator basic_posix_io_observer<char_type>() const
	{
		return static_cast<basic_posix_io_observer<char_type>>(
			static_cast<basic_c_io_observer_unlocked<char_type>>(*this));
	}
#if defined(__WINNT__) || defined(_MSC_VER)
	explicit operator basic_win32_io_observer<char_type>() const
	{
		return static_cast<basic_win32_io_observer<char_type>>(
			static_cast<basic_posix_io_observer<char_type>>(*this));
	}
#endif
};

template<typename stream_type,std::contiguous_iterator Iter>
inline Iter read(basic_stream_file<stream_type>& cfhd,Iter begin,Iter end)
{
	streambuf_view buf(std::addressof(cfhd.filebuf()));
	return read(buf,begin,end);
}

template<typename stream_type,std::contiguous_iterator Iter>
inline auto write(basic_stream_file<stream_type>& cfhd,Iter begin,Iter end)
{
	streambuf_view buf(std::addressof(cfhd.filebuf()));
	return write(buf,begin,end);
}

template<typename stream_type>
inline void flush(basic_stream_file<stream_type>& cfhd)
{
	streambuf_view buf(std::addressof(cfhd.filebuf()));
	flush(buf);
}
template<typename stream_type>
inline auto oreserve(basic_stream_file<stream_type>& cfhd,std::size_t n)
{
	streambuf_view buf(std::addressof(cfhd.filebuf()));
	return oreserve(buf,n);
}

template<typename stream_type>
inline void orelease(basic_stream_file<stream_type>& cfhd,std::size_t n)
{
	streambuf_view buf(std::addressof(cfhd.filebuf()));
	orelease(buf,n);
}

template<typename stream_type>
inline void put(basic_stream_file<stream_type>& cfhd,typename basic_stream_file<stream_type>::char_type ch)
{
	streambuf_view buf(std::addressof(cfhd.filebuf()));
	put(buf,ch);
}

template<typename stream_type,typename... Args>
inline auto seek(basic_stream_file<stream_type>& cfhd,Args&& ...args)
{
	cfhd.native_handle().flush();
	cfhd.native_handle().clear();
	return seek(cfhd.c_file(),std::forward<Args>(args)...);
}

template<typename stream_type>
requires zero_copy_input_stream<typename basic_stream_file<stream_type>::c_file_type>
inline auto zero_copy_in_handle(basic_stream_file<stream_type>& h)
{
	return zero_copy_in_handle(h.c_file());
}

template<typename stream_type>
requires zero_copy_output_stream<typename basic_stream_file<stream_type>::c_file_type>
inline auto zero_copy_out_handle(basic_stream_file<stream_type>& h)
{
	return zero_copy_out_handle(h.c_file());
}

template<typename stream_type>
requires redirect_stream<typename basic_stream_file<stream_type>::c_file_type>
inline auto redirect_handle(basic_stream_file<stream_type>& h)
{
	return redirect_handle(h.c_file());
}

using stream_file = basic_stream_file<std::iostream>;
using istream_file = input_file_wrapper<basic_stream_file<std::istream>>;
using ostream_file = output_file_wrapper<basic_stream_file<std::ostream>>;
using iostream_file = io_file_wrapper<stream_file>;

}