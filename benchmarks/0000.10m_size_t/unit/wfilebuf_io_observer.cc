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
	std::wofstream fout("wfilebuf_io_observer.txt",std::ofstream::binary);
	fast_io::wfilebuf_io_observer fob{fout.rdbuf()};
	for(std::size_t i{};i!=N;++i)
		println(fob,i);
	}
	std::vector<std::size_t> vec(N);
	{
	fast_io::timer t("input");
	std::wifstream fin("wfilebuf_io_observer.txt",std::ifstream::binary);
	fast_io::wfilebuf_io_observer fob{fin.rdbuf()};
	for(std::size_t i{};i!=N;++i)
		scan(fob,vec[i]);
	}
}