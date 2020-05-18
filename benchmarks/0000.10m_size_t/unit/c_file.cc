#include"../../timer.h"
#include"../../../include/fast_io.h"
#include"../../../include/fast_io_device.h"
#include"../../../include/fast_io_legacy.h"

int main()
{
	constexpr std::size_t N(10000000);
	{
	fast_io::timer t("output");
	fast_io::c_file cf_out("cf.txt",fast_io::open_interface<fast_io::open_mode::out|fast_io::open_mode::binary>);
	for(std::size_t i{};i!=N;++i)
		println(cf_out,i);
	}
	std::vector<std::size_t> vec(N);
	{
	fast_io::timer t("input");
	fast_io::c_file cf("cf.txt",fast_io::open_interface<fast_io::open_mode::in|fast_io::open_mode::binary>);
	for(std::size_t i{};i!=N;++i)
		scan(cf,vec[i]);
	}
}