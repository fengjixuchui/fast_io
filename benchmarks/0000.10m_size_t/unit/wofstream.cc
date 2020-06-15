#include"../../timer.h"
#include<fstream>
#include"../../../include/fast_io.h"
#include"../../../include/fast_io_device.h"
#include"../../../include/fast_io_legacy.h"

int main()
{
	constexpr std::size_t N(10000000);
	{
	fast_io::timer t("output");
	std::wofstream fout("wofstream.txt",std::ofstream::binary);
	auto& rdbuf(*fout.rdbuf());
	for(std::size_t i{};i!=N;++i)
	{
		fout<<i;
		rdbuf.sputc('\n');
	}
	}
	std::vector<std::size_t> vec(N);
	{
	fast_io::timer t("input");
	std::wifstream fin("wofstream.txt",std::ifstream::binary);
	for(std::size_t i{};i!=N;++i)
		fin>>vec[i];
	}
}