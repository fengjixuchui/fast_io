#include"../timer.h"
#include"../../include/fast_io.h"
#include"../../include/fast_io_device.h"
//#include"../../include/fast_io_crypto.h"
#include"../../include/fast_io_legacy.h"

int main()
{
	constexpr std::size_t N(10000000);
	{
	fast_io::timer t("output");
	fast_io::c_file_unlocked cful_out("cful.txt",fast_io::open_interface<fast_io::open_mode::out|fast_io::open_mode::binary>);
	for(std::size_t i{};i!=N;++i)
		println(cful_out,i);
	}
	{
	fast_io::timer t("input");
	fast_io::c_file_unlocked cful("cful.txt",fast_io::open_interface<fast_io::open_mode::in|fast_io::open_mode::binary>);
	fast_io::c_file_unlocked cful_out("cful_verify.txt",fast_io::open_interface<fast_io::open_mode::out|fast_io::open_mode::binary>);
	for(std::size_t i{};i!=N;++i)
	{
		std::size_t value;
		scan(cful,value);
		println(cful_out,value);
	}
	}
}