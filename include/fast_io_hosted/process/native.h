#pragma once

#if defined(__WINNT__) || defined(_MSC_VER)
#include"nt_error.h"
#include"nt_fork.h"
#include"win32.h"
#else
#include"posix.h"
#endif

namespace fast_io
{

}