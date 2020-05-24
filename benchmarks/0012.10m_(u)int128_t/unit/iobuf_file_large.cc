#include"../../timer.h"
#include"../../../include/fast_io.h"
#include"../../../include/fast_io_device.h"
#include"../../../include/fast_io_legacy.h"

int main()
{
	constexpr std::size_t N(10000000);
	{
	fast_io::timer t("output");
	fast_io::obuf_file obf("obuf_file.txt");
	for(__uint128_t i{};i!=N;++i)
		println(obf,i*10000000000000000ULL);
	}
	std::vector<__uint128_t> vec(N);
	{
	fast_io::timer t("input");
	fast_io::ibuf_file ibf("obuf_file.txt");
	for(std::size_t i{};i!=N;++i)
		scan(ibf,vec[i]);
	}
}