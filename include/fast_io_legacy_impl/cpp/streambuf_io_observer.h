#pragma once
#include<streambuf>
#include<fstream>
#include<sstream>
#ifdef __GLIBCXX__
#include"fp_hack/libstdc++.h"
#elif defined(_MSVC_STL_UPDATE)
#include"fp_hack/msvc_stl.h"
#elif defined(__LIBCPP_VERSION)
#include"fp_hack/libc++.h"
#endif


namespace fast_io
{

template<typename T>
requires std::derived_from<T,std::basic_streambuf<typename T::char_type,typename T::traits_type>>
class basic_general_streambuf_io_observer
{
public:
	using streambuf_type = T;
	using char_type = typename streambuf_type::char_type;
	using traits_type = typename streambuf_type::traits_type;
	using native_handle_type = streambuf_type*;
	native_handle_type rdb{};
	inline constexpr native_handle_type& native_handle() const noexcept
	{
		return rdb;
	}
	inline constexpr native_handle_type& native_handle() noexcept
	{
		return rdb;
	}
#if defined(__GLIBCXX__) || defined(__LIBCPP_VERSION)  || defined(_MSVC_STL_UPDATE)
	explicit operator basic_c_io_observer_unlocked<char_type>()
	{
		return basic_c_io_observer_unlocked<char_type>{details::streambuf_hack::fp_hack(rdb)};
	}
	explicit operator basic_c_io_observer<char_type>()
	{
		return basic_c_io_observer<char_type>{details::streambuf_hack::fp_hack(rdb)};
	}
	explicit operator basic_posix_io_observer<char_type>()
	{
		return static_cast<basic_posix_io_observer<char_type>>(static_cast<basic_c_io_observer<char_type>>(*this));
	}
#if defined(__WINNT__) || defined(_MSC_VER)
	explicit operator basic_win32_io_observer<char_type>()
	{
		return static_cast<basic_win32_io_observer<char_type>>
		(static_cast<basic_posix_io_observer<char_type>>(*this));
	}
	explicit operator basic_nt_io_observer<char_type>()
	{
		return static_cast<basic_nt_io_observer<char_type>>
		(static_cast<basic_posix_io_observer<char_type>>(*this));
	}
#endif
#endif
};

template<typename T,std::contiguous_iterator Iter>
inline Iter read(basic_general_streambuf_io_observer<T>& t,Iter begin,Iter end)
{
	using char_type = typename T::char_type;
	return begin+(t.rdb->sgetn(static_cast<char_type*>(static_cast<void*>(std::to_address(begin))),(end-begin)*sizeof(*begin)/sizeof(char_type))*sizeof(char_type)/sizeof(*begin));
}

template<typename T,std::contiguous_iterator Iter>
inline Iter write(basic_general_streambuf_io_observer<T>& t,Iter begin,Iter end)
{
	using char_type = typename T::char_type;
/*
	if(!t.rdb->sputn(static_cast<char_type const*>(static_cast<void const*>(std::to_address(begin))),(end-begin)*sizeof(*begin)/sizeof(char_type)))
#ifdef __cpp_exceptions
		throw std::system_error(std::make_error_code(std::errc::io_error));
#else
		fast_terminate();
#endif*/
	return begin+(t.rdb->sputn(static_cast<char_type const*>(static_cast<void const*>(std::to_address(begin))),(end-begin)*sizeof(*begin)/sizeof(char_type)))*sizeof(char_type)/sizeof(*begin);
}

template<std::integral CharT,typename Traits = std::char_traits<CharT>>
using basic_streambuf_io_observer = basic_general_streambuf_io_observer<std::basic_streambuf<CharT,Traits>>;

template<std::integral CharT,typename Traits = std::char_traits<CharT>>
using basic_filebuf_io_observer = basic_general_streambuf_io_observer<std::basic_filebuf<CharT,Traits>>;

template<std::integral CharT,typename Traits = std::char_traits<CharT>>
using basic_stringbuf_io_observer = basic_general_streambuf_io_observer<std::basic_stringbuf<CharT,Traits>>;


using streambuf_io_observer = basic_streambuf_io_observer<char>;
using wstreambuf_io_observer = basic_streambuf_io_observer<wchar_t>;
using u8streambuf_io_observer = basic_streambuf_io_observer<char8_t>;

using filebuf_io_observer = basic_filebuf_io_observer<char>;
using wfilebuf_io_observer = basic_filebuf_io_observer<wchar_t>;
using u8filebuf_io_observer = basic_filebuf_io_observer<char8_t>;

using stringbuf_io_observer = basic_stringbuf_io_observer<char>;
using wstringbuf_io_observer = basic_stringbuf_io_observer<wchar_t>;
using u8stringbuf_io_observer = basic_stringbuf_io_observer<char8_t>;

template<output_stream output,typename T>
inline constexpr void print_define(output& out,basic_general_streambuf_io_observer<T> iob)
{
	print(out,fast_io::unsigned_view(iob.native_handle()));
}


}


#if defined(__GLIBCXX__) || defined(__LIBCPP_VERSION) || defined(_MSVC_STL_UPDATE)
#include"general.h"
#endif
