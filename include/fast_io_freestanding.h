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
#include"fast_io_freestanding_impl/exception.h"
//compile floating point is slow since it requires algorithms like ryu
#include"fast_io_freestanding_impl/floating_point/floating.h"
#include"fast_io_freestanding_impl/iobuf.h"
#include"fast_io_freestanding_impl/io_io_file.h"
#include"fast_io_freestanding_impl/send_receive.h"
#include"fast_io_freestanding_impl/natural.h"
#include"fast_io_freestanding_impl/memptr.h"
#include"fast_io_freestanding_impl/reserve_read_write.h"
#include"fast_io_freestanding_impl/code_cvt/utf.h"
//#include"fast_io_freestanding_impl/ucs.h"
#if __cpp_coroutines >= 201902
#include<coroutine>		//coroutine is freestanding
#include"fast_io_freestanding_impl/generator.h"
#endif

namespace fast_io
{
using ostring = basic_ostring<std::string>;
using u8ostring = basic_ostring<std::u8string>;

using ostring_ref = basic_ostring_ref<std::string>;
using u8ostring_ref = basic_ostring_ref<std::u8string>;

template<std::integral char_type>
using basic_iobuf_io_io_observer = basic_iobuf<basic_io_io_observer<char_type>>;
template<std::integral char_type>
using basic_iobuf_io_io_handle = basic_iobuf<basic_io_io_handle<char_type>>;
template<std::integral char_type>
using basic_iobuf_io_file = basic_iobuf<basic_io_file<char_type>>;

using iobuf_io_io_observer = basic_iobuf_io_io_observer<char>;
using iobuf_io_io_handle = basic_iobuf_io_io_handle<char>;
using iobuf_io_file = basic_iobuf_io_file<char>;

using u8iobuf_io_io_observer = basic_iobuf_io_io_observer<char8_t>;
using u8iobuf_io_io_handle = basic_iobuf_io_io_handle<char8_t>;
using u8iobuf_io_file = basic_iobuf_io_file<char8_t>;

using wiobuf_io_io_observer = basic_iobuf_io_io_observer<wchar_t>;
using wiobuf_io_io_handle = basic_iobuf_io_io_handle<wchar_t>;
using wiobuf_io_file = basic_iobuf_io_file<wchar_t>;

}
