#include"../../timer.h"
#include"../../../include/fast_io.h"
#include"../../../include/fast_io_device.h"
#include"../../../include/fast_io_legacy.h"

int main()
{
	constexpr std::size_t N(10000000);
	{
	fast_io::timer t("output");
	fast_io::filebuf_file fbf_out("fbf.txt",fast_io::open_interface<fast_io::open_mode::out|fast_io::open_mode::binary>);
	for(std::size_t i{};i!=N;++i)
		println(fbf_out,i);
	}
	std::vector<std::size_t> vec(N);
	{
	fast_io::timer t("input");
	fast_io::filebuf_file fbf("fbf.txt",fast_io::open_interface<fast_io::open_mode::in|fast_io::open_mode::binary>);
	for(std::size_t i{};i!=N;++i)
		scan(fbf,vec[i]);
	}
}