#pragma once

#if defined(__WINNT__) || defined(_MSC_VER)
#include"fast_io_hosted.h"
#include"fast_io_network/win32_box.h"

namespace fast_io
{

using namespace std::string_view_literals;
inline constexpr fast_io::native_box box("fast io"sv);
inline constexpr fast_io::wnative_box wbox(L"fast io"sv);

}

#endif