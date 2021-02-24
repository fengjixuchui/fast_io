#pragma once

#ifndef _MSC_VER
#include"../../fast_io_crypto/hash/hash_processor.h"
#include"../../fast_io_crypto/hash/sha.h"
#endif

#ifdef _WIN32
#include"win32_api.h"
#include"win32_error.h"
#include"nt_api.h"
#include"nt_error.h"
#include"nt.h"
#include"win32_iocp_overlapped.h"
#include"win32.h"
#include"win32_path_dealer.h"
//#include"com_error.h"
#else
#include"posix_path_dealer.h"
#endif
#include"linux/system_call.h"
#include"posix.h"

namespace fast_io
{

#ifdef _WIN32
inline constexpr auto native_stdin_number(win32_stdin_number);
inline constexpr auto native_stdout_number(win32_stdout_number);
inline constexpr auto native_stderr_number(win32_stderr_number);

using native_at_entry = nt_at_entry;
using native_fs_dirent = nt_fs_dirent;

template<std::integral ch_type>
using basic_native_io_observer = basic_win32_io_observer<ch_type>;
template<std::integral ch_type>
using basic_native_io_handle = basic_win32_io_handle<ch_type>;
template<std::integral ch_type>
using basic_native_file = basic_win32_file<ch_type>;
template<std::integral ch_type>
using basic_native_pipe = basic_win32_pipe<ch_type>;
#else
inline constexpr auto native_stdin_number(posix_stdin_number);
inline constexpr auto native_stdout_number(posix_stdout_number);
inline constexpr auto native_stderr_number(posix_stderr_number);

using native_at_entry = posix_at_entry;
using native_fs_dirent = posix_fs_dirent;

template<std::integral ch_type>
using basic_native_io_observer = basic_posix_io_observer<ch_type>;
template<std::integral ch_type>
using basic_native_io_handle = basic_posix_io_handle<ch_type>;
template<std::integral ch_type>
using basic_native_file = basic_posix_file<ch_type>;
template<std::integral ch_type>
using basic_native_pipe = basic_posix_pipe<ch_type>;

#endif

using native_io_observer = basic_native_io_observer<char>;
using native_io_handle = basic_native_io_handle<char>;
using native_file = basic_native_file<char>;
using native_pipe = basic_native_pipe<char>;

#ifndef __MSDOS__
using wnative_io_observer = basic_native_io_observer<wchar_t>;
using wnative_io_handle = basic_native_io_handle<wchar_t>;
using wnative_file = basic_native_file<wchar_t>;
using wnative_pipe = basic_native_pipe<wchar_t>;
#endif

using u8native_io_observer = basic_native_io_observer<char8_t>;
using u8native_io_handle = basic_native_io_handle<char8_t>;
using u8native_file = basic_native_file<char8_t>;
using u8native_pipe = basic_native_pipe<char8_t>;

using u16native_io_observer = basic_native_io_observer<char16_t>;
using u16native_io_handle = basic_native_io_handle<char16_t>;
using u16native_file = basic_native_file<char16_t>;
using u16native_pipe = basic_native_pipe<char16_t>;

using u32native_io_observer = basic_native_io_observer<char32_t>;
using u32native_io_handle = basic_native_io_handle<char32_t>;
using u32native_file = basic_native_file<char32_t>;
using u32native_pipe = basic_native_pipe<char32_t>;

}