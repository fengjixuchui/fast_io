#pragma once

#include"fast_io_device.h"
#include"fast_io_locale.h"

namespace fast_io
{
using c_locale_ibuf_file = c_locale_wrapper<ibuf_file>;
using c_locale_obuf_file = c_locale_wrapper<obuf_file>;
using c_locale_iobuf_file = c_locale_wrapper<iobuf_file>;

using c_locale_ibuf_file_mutex = c_locale_wrapper<ibuf_file_mutex>;
using c_locale_obuf_file_mutex = c_locale_wrapper<obuf_file_mutex>;
using c_locale_iobuf_file_mutex = c_locale_wrapper<iobuf_file_mutex>;

}