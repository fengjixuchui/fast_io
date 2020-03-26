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
	fast_io::wc_file_unlocked wcful_out("wcful.txt",fast_io::open_interface<fast_io::open_mode::out|fast_io::open_mode::binary>);
	for(std::size_t i{};i!=N;++i)
		println(wcful_out,i);
	}
	{
	fast_io::timer t("input");
	fast_io::wc_file_unlocked wcful("wcful.txt",fast_io::open_interface<fast_io::open_mode::in|fast_io::open_mode::binary>);
	fast_io::wc_file_unlocked wcful_out("wcful_verify.txt",fast_io::open_interface<fast_io::open_mode::out|fast_io::open_mode::binary>);
	for(std::size_t i{};i!=N;++i)
	{
		std::size_t value;
		scan(wcful,value);
		println(wcful_out,value);
	}
	}
}