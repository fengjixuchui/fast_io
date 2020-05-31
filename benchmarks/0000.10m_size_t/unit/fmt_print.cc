#include"../../timer.h"
#include"../../../include/fast_io_device.h"
#include<fmt/format.h>
#include<fstream>

int main()
{
	constexpr std::size_t N(10000000);
	{
	fast_io::timer t("fmt::format");
	fast_io::c_file cf("fmt_print.txt",fast_io::open_mode::binary|fast_io::open_mode::out);
	for(std::size_t i{};i!=N;++i)
	{
		fmt::print(cf.native_handle(),"{}\n",i);
	}
	}
}