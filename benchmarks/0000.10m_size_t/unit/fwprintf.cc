#include"../../timer.h"
#include"../../../include/fast_io.h"
#include"../../../include/fast_io_device.h"
#include"../../../include/fast_io_legacy.h"

int main()
{
	constexpr std::size_t N(10000000);
	{
	fast_io::timer t("output");
	fast_io::c_file cf("fwprintf.txt",fast_io::open_interface<fast_io::open_mode::out|fast_io::open_mode::binary>);
	for(std::size_t i{};i!=N;++i)
		fwprintf(cf.native_handle(),L"%zu\n",i);
	}
	std::vector<std::size_t> vec(N);
	{
	fast_io::timer t("input");
	fast_io::c_file cf("fwprintf.txt",fast_io::open_interface<fast_io::open_mode::in|fast_io::open_mode::binary>);
	for(std::size_t i{};i!=N;++i)
		fwscanf(cf.native_handle(),L"%zu",vec.data()+i);
	}
}