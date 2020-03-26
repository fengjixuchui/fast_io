#pragma once

#include"fast_io_hosted.h"
//This header file defines in/out/err/log like traditional C/C++ does
//out and err will direct write to system call.
//The magic here is that data will first write to std::u8string and then write out
//There is no way to implement in without a buffer. input must have a buffer.

namespace fast_io
{
inline namespace
{
#if defined(__WINNT__) || defined(_MSC_VER)
inline native_io_handle out(native_stdout_number);
inline native_io_handle err(native_stderr_number);
#else
inline constinit native_io_handle out(native_stdout_number);
inline constinit native_io_handle err(native_stderr_number);
#endif

using log_type = basic_obuf<native_io_handle>;

inline auto out_buf()
{
	return log_type(native_stdout_number);
}

inline auto log()
{
	return log_type(native_stderr_number);
}

}
}

/*
I know putting global would be a problem. However, I think put some special cases to global would reduce abusing of using namespace

print is more nature and teachable for new C++ programmmers and most languages on the world (basic, lua, python) are all doing this

Also, it allows you for copying some other languages' code into C++
*/

template<typename T,typename... Args>
requires (!fast_io::output_stream<T>)&&requires(T&& t,Args&& ...args)
{
	fast_io::print(fast_io::out,std::forward<T>(t),std::forward<Args>(args)...);
}
inline constexpr void print(T&& t,Args&& ...args)
{
	fast_io::print(fast_io::out,std::forward<T>(t),std::forward<Args>(args)...);
}

template<typename T,typename... Args>
requires (!fast_io::output_stream<T>)&&requires(T&& t,Args&& ...args)
{
	fast_io::println(fast_io::out,std::forward<T>(t),std::forward<Args>(args)...);
}
inline constexpr void println(T&& t,Args&& ...args)
{
	fast_io::println(fast_io::out,std::forward<T>(t),std::forward<Args>(args)...);
}

template<typename... Args>
requires requires(Args&& ...args)
{
	fast_io::fprint(fast_io::out,std::forward<Args>(args)...);
}
inline constexpr void fprint(Args&& ...args)
{
	fast_io::fprint(fast_io::out,std::forward<Args>(args)...);
}


//Allow debug print
#ifndef NDEBUG

template<typename T,typename... Args>
requires (!fast_io::output_stream<T>)&&requires(T&& t,Args&& ...args)
{
	fast_io::print(fast_io::out,std::forward<T>(t),std::forward<Args>(args)...);
}
inline constexpr void debug_print(T&& t,Args&& ...args)
{
	fast_io::print(fast_io::out,std::forward<T>(t),std::forward<Args>(args)...);
}

template<typename T,typename... Args>
requires (!fast_io::output_stream<T>)&&requires(T&& t,Args&& ...args)
{
	fast_io::println(fast_io::out,std::forward<T>(t),std::forward<Args>(args)...);
}
inline constexpr void debug_println(T&& t,Args&& ...args)
{
	fast_io::println(fast_io::out,std::forward<T>(t),std::forward<Args>(args)...);
}

template<typename... Args>
requires requires(Args&& ...args)
{
	fast_io::fprint(fast_io::out,std::forward<Args>(args)...);
}
inline constexpr void debug_fprint(Args&& ...args)
{
	fast_io::fprint(fast_io::out,std::forward<Args>(args)...);
}

#endif