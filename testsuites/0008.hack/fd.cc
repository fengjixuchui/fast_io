#include<iostream>
#include"../../include/fast_io.h"
#include"../../include/fast_io_legacy.h"

int main()
{
	fast_io::streambuf_io_observer siob{std::cout.rdbuf()};
	auto cio{static_cast<fast_io::c_io_observer>(siob)};
	auto pio{static_cast<fast_io::posix_io_observer>(siob)};
	println(u8"std::cout.rdbuf():",fast_io::unsigned_view(siob.native_handle()),
	u8"\nFILE*:",fast_io::unsigned_view(cio.native_handle()),u8"\nfile descriptor:",pio.native_handle()
#if defined(__WINNT__) || defined(_MSC_VER)
	,u8"\nwin32 handle:",fast_io::unsigned_view(static_cast<fast_io::win32_io_observer>(siob).native_handle())
	,u8"\nnt handle:",fast_io::unsigned_view(static_cast<fast_io::win32_io_observer>(siob).native_handle())
#endif
	);
}