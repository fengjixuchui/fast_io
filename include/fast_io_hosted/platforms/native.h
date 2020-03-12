#pragma once
#if defined(__WINNT__) || defined(_MSC_VER)
#include"win32_api.h"
#include"win32_error.h"
#include"nt_api.h"
#include"nt_error.h"
#include"nt.h"
#include"win32.h"
#include"win32_mapping.h"
#endif

#include"posix.h"
#ifdef _POSIX_C_SOURCE
#include"posix_mapping.h"
#endif

#if defined(__WINNT__) || defined(_MSC_VER)
#include"win32_transmit.h"
#endif

namespace fast_io
{

#if defined(__WINNT__) || defined(_MSC_VER)
inline constexpr auto native_stdin_number(win32_stdin_number);
inline constexpr auto native_stdout_number(win32_stdout_number);
inline constexpr auto native_stderr_number(win32_stderr_number);
using native_io_observer = win32_io_observer;
using native_io_handle = win32_io_handle;
using native_file = win32_file;
using native_pipe = win32_pipe;
using u8native_io_observer = u8win32_io_observer;
using u8native_io_handle = u8win32_io_handle;
using u8native_file = u8win32_file;
using u8native_pipe = u8win32_pipe;
using native_file_map = win32_file_map;

#else
inline constexpr auto native_stdin_number(posix_stdin_number);
inline constexpr auto native_stdout_number(posix_stdout_number);
inline constexpr auto native_stderr_number(posix_stderr_number);

using native_io_observer = posix_io_observer;
using native_io_handle = posix_io_handle;
using native_file = posix_file;
using native_pipe = posix_pipe;

using u8native_io_observer = u8posix_io_observer;
using u8native_io_handle = u8posix_io_handle;
using u8native_file = u8posix_file;
using u8native_pipe = u8posix_pipe;
using native_file_map = posix_file_map;
#endif


inline native_io_handle native_stdin()
{
	return native_io_handle{native_stdin_number};
}
inline native_io_handle native_stdout()
{
	return native_io_handle{native_stdout_number};
} 
inline native_io_handle native_stderr()
{
	return native_io_handle{native_stderr_number};
}

}