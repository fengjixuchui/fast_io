#include"../../timer.h"
#include<fstream>
#include"../../../include/fast_io.h"
#include"../../../include/fast_io_device.h"
//#include"../../include/fast_io_crypto.h"
#include"../../../include/fast_io_legacy.h"
#include<ext/stdio_filebuf.h>

int main()
{
	constexpr std::size_t N(10000000);
	{
	fast_io::timer t("output");
	fast_io::posix_file posix("streambuf_io_observer___gnu_cxx_stdio_filebuf.txt",fast_io::open_interface<fast_io::open_mode::binary|fast_io::open_mode::out>);
	__gnu_cxx::stdio_filebuf<char> stdio_filebuf(posix.native_handle(),std::ios::binary|std::ios::out,65536);
	fast_io::streambuf_io_observer fob{std::addressof(stdio_filebuf)};
	for(std::size_t i{};i!=N;++i)
		println(fob,i);
	}
	std::vector<std::size_t> vec(N);
	{
	fast_io::timer t("input");
	fast_io::posix_file posix("streambuf_io_observer___gnu_cxx_stdio_filebuf.txt",fast_io::open_interface<fast_io::open_mode::binary|fast_io::open_mode::in>);
	__gnu_cxx::stdio_filebuf<char> stdio_filebuf(posix.native_handle(),std::ios::binary|std::ios::in,65536);
	fast_io::streambuf_io_observer fob{std::addressof(stdio_filebuf)};
	for(std::size_t i{};i!=N;++i)
		scan(fob,vec[i]);
	}
}