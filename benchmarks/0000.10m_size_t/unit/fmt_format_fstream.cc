#include"../../timer.h"
#include"../../../include/fast_io_device.h"
#include<fmt/format.h>
#include<fstream>

int main()
{
	constexpr std::size_t N(10000000);
	{
	fast_io::timer t("fmt::format");
	std::ofstream fout("format.txt",std::ofstream::binary);
	for(std::size_t i{};i!=N;++i)
	{
		fout<<fmt::format("{}\n",i);
	}
	}
}