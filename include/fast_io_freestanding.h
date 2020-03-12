#pragma once

//fast_io_freestanding.h is usable when the underlining system implements dynamic memory allocations and exceptions

#include"fast_io_core.h"
#include<stdexcept>
#include<string>
#include<bitset>
#include<system_error>
//#include<cmath>

#include"fast_io_freestanding_impl/concat.h"
#include"fast_io_freestanding_impl/manip.h"
#include"fast_io_freestanding_impl/scan_print.h"
#include"fast_io_freestanding_impl/exception.h"
//compile floating point is slow since it requires algorithms like ryu
#include"fast_io_freestanding_impl/floating.h"
#include"fast_io_freestanding_impl/iobuf.h"
#include"fast_io_freestanding_impl/dynamic.h"
#include"fast_io_freestanding_impl/send_receive.h"
#include"fast_io_freestanding_impl/natural.h"
#include"fast_io_freestanding_impl/memptr.h"
#include"fast_io_freestanding_impl/code_cvt/utf.h"
//#include"fast_io_freestanding_impl/ucs.h"
#ifdef __cpp_coroutines
#include<coroutine>		//coroutine is freestanding
#include"fast_io_freestanding_impl/generator.h"
#endif

namespace fast_io
{
using ostring = basic_ostring<std::string>;
using u8ostring = basic_ostring<std::u8string>;

using ostring_ref = basic_ostring_ref<std::string>;
using u8ostring_ref = basic_ostring_ref<std::u8string>;
}
