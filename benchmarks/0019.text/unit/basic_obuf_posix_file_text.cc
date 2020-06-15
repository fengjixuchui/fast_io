#include"../../timer.h"
#include"../../../include/fast_io.h"
#include"../../../include/fast_io_device.h"
#include"../../../include/fast_io_legacy.h"

int main()
{
	constexpr std::size_t N(10000000);
	{
	fast_io::timer t("output");
	fast_io::basic_obuf<fast_io::posix_file> obf("basic_obuf_posix_file_text.txt",fast_io::open_mode::out|fast_io::open_mode::trunc|fast_io::open_mode::creat);
	for(std::size_t i{};i!=N;++i)
		println(obf,i);
	}
	std::vector<std::size_t> vec(N);
	{
	fast_io::timer t("input");
	fast_io::basic_ibuf<fast_io::posix_file> ibf("basic_obuf_posix_file_text.txt",fast_io::open_mode::in);
	for(std::size_t i{};i!=N;++i)
		scan(ibf,vec[i]);
	}
}