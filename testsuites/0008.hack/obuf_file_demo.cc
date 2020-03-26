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
	fast_io::obuf_file obf("obuf_file.txt",fast_io::open_interface<fast_io::open_mode::out|fast_io::open_mode::binary>);
	for(std::size_t i{};i!=N;++i)
		println(obf,i);
	}
	{
	fast_io::timer t("input");
	fast_io::ibuf_file obf("obuf_file.txt",fast_io::open_interface<fast_io::open_mode::in|fast_io::open_mode::binary>);
	fast_io::obuf_file obf_out("obuf_file_verify.txt",fast_io::open_interface<fast_io::open_mode::out|fast_io::open_mode::binary>);
	for(std::size_t i{};i!=N;++i)
	{
		std::size_t value;
		scan(obf,value);
		println(obf_out,value);
	}
	}
}