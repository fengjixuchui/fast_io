#pragma once

#if defined(__GLIBCXX__)
#include"libstdc++.h"
#elif defined(__LIBCPP_VERSION)
#include"libc++.h"
#elif defined(_MSVC_STL_UPDATE)
#include"msvc_stl.h"
#else
#error "Anyone knows how to hack brutal std::basic_string internal on this platform?"
#endif

#include"ostring_ref.h"