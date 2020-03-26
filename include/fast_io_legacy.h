#pragma once

//fast_io_legacy.h deals with legacy C <stdio.h> and C++ <iostream>/<fstream>/<sstream> interface
#include"fast_io_hosted.h"
#include"fast_io_legacy_impl/c/impl.h"
#include"fast_io_legacy_impl/cpp/streambuf_io_observer.h"

/*
#include<iostream>
#ifdef __GLIBCXX__
#include<ext/stdio_filebuf.h>
#endif
#include"fast_io_legacy_impl/stream_view.h"
#include"fast_io_legacy_impl/streambuf_view.h"
#include"fast_io_legacy_impl/streambuf_handle.h"
#include"fast_io_legacy_impl/fast_io_streambuf.h"
#include"fast_io_legacy_impl/fast_io_iostream.h"
#include"fast_io_legacy_impl/filebuf_handle.h"
#if defined (__GLIBCXX__) || defined (_MSC_VER)
#include"fast_io_legacy_impl/stream_file.h"
#endif
*/
namespace fast_io
{
inline namespace
{
inline c_io_handle c_stdin{stdin};
inline c_io_handle c_stdout{stdout};
inline c_io_handle c_stderr{stderr};

inline wc_io_handle wc_stdin{stdin};
inline wc_io_handle wc_stdout{stdout};
inline wc_io_handle wc_stderr{stderr};
//inline stream_view cpp_clog(std::clog);
}
}