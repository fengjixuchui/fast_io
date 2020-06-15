#include"../../timer.h"
#include"../../../include/fast_io.h"
#include"../../../include/fast_io_device.h"
#include"../../../include/fast_io_legacy.h"

int main()
{
	constexpr std::size_t N(10000000);
	{
	fast_io::timer t("output");
	fast_io::obuf_text_file obf("obuf_text_file.txt");
	for(std::size_t i{};i!=N;++i)
		println(obf,i);
	}
	std::vector<std::size_t> vec(N);
	{
	fast_io::timer t("input");
	fast_io::ibuf_text_file ibf("obuf_text_file.txt");
	for(std::size_t i{};i!=N;++i)
		scan(ibf,vec[i]);
	}
}