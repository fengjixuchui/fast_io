#include"../timer.h"
#include"../../include/fast_io_device.h"
#include"../../include/fast_io_legacy.h"

int main()
{
	constexpr std::size_t N=10000000;
	fast_io::timer tm("omap");
	fast_io::omap_file pf("om.txt",	fast_io::open_interface<fast_io::open_mode::trunc|fast_io::open_mode::in|fast_io::open_mode::out|fast_io::open_mode::binary>);
	for(std::size_t i{};i!=N;++i)
		println(pf,i);
}