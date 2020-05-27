#pragma once

#include"fast_io_hosted.h"

#include"fast_io_legacy_impl/c/impl.h"

namespace fast_io
{

static inline constexpr posix_io_observer in(posix_stdin());
static inline constexpr posix_io_observer out(posix_stdout());
static inline constexpr posix_io_observer err(posix_stderr());

using log_type = basic_obuf<native_io_observer>;
inline auto out_buf()
{
	native_io_handle hd{native_stdout_number};
	return log_type(hd);
}

inline auto log()
{
	native_io_handle hd{native_stderr_number};
	return log_type(hd);
}
using in_buf_type = basic_ibuf<native_io_observer>;
inline auto in_buf()
{
	native_io_handle hd{native_stdin_number};
	return log_type(hd);
}

}

template<typename T,typename... Args>
inline constexpr void print(T&& t,Args&& ...args)
{
	if constexpr(fast_io::output_stream<std::remove_cvref_t<T>>)
		fast_io::print(std::forward<T>(t),std::forward<Args>(args)...);
	else
	{
		fast_io::c_io_observer c_stdout(stdout);
		fast_io::print(c_stdout,std::forward<T>(t),std::forward<Args>(args)...);
	}
}

template<typename T,typename... Args>
inline constexpr void println(T&& t,Args&& ...args)
{
	if constexpr(fast_io::output_stream<std::remove_cvref_t<T>>)
		fast_io::println(std::forward<T>(t),std::forward<Args>(args)...);
	else
	{
		fast_io::c_io_observer c_stdout(stdout);
		fast_io::println(c_stdout,std::forward<T>(t),std::forward<Args>(args)...);
	}
}


//Allow debug print
#ifndef NDEBUG

template<typename T,typename... Args>
inline constexpr void debug_print(T&& t,Args&& ...args)
{
	if constexpr(fast_io::output_stream<std::remove_cvref_t<T>>)
		fast_io::debug_print(std::forward<T>(t),std::forward<Args>(args)...);
	else
	{
		fast_io::c_io_observer c_stdout(stdout);
		fast_io::debug_print(c_stdout,std::forward<T>(t),std::forward<Args>(args)...);
	}
}

template<typename T,typename... Args>
inline constexpr void debug_println(T&& t,Args&& ...args)
{
	if constexpr(fast_io::output_stream<std::remove_cvref_t<T>>)
		fast_io::debug_println(std::forward<T>(t),std::forward<Args>(args)...);
	else
	{
		fast_io::c_io_observer c_stdout(stdout);
		fast_io::debug_println(c_stdout,std::forward<T>(t),std::forward<Args>(args)...);
	}
}

#endif

template<bool report_eof=false,typename T,typename... Args>
inline constexpr auto scan(T&& t,Args&& ...args)
{
	if constexpr(fast_io::input_stream<std::remove_cvref_t<T>>)
		return fast_io::scan<report_eof>(std::forward<T>(t),std::forward<Args>(args)...);
	else
	{
		fast_io::c_io_observer c_stdin(stdin);
		return scan<report_eof>(c_stdin,std::forward<T>(t),std::forward<Args>(args)...);
	}
}
