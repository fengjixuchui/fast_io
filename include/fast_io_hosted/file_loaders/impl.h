#pragma once
#include"posix_file_loader.h"
#if defined(_WIN32) || defined(__CYGWIN__)
#include"win32_file_loader.h"
#endif


namespace fast_io
{

#if defined(_WIN32)
using native_file_loader = win32_file_loader;
#elif (!defined(__NEWLIB__)||defined(__CYGWIN__)) && !defined(__MSDOS__)
using native_file_loader = posix_file_loader;
#else
using native_file_loader = allocation_file_loader;
#endif


}