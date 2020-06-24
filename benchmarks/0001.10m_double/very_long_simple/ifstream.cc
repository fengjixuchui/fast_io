#include"../../timer.h"
#include"../../../include/fast_io_device.h"
#include"../../../include/fast_io.h"
#include<fstream>

int main()
{
	constexpr std::size_t N{1000000};
	std::vector<double> buffer(N);
	{
		fast_io::timer tm("input");
		std::ifstream fin("very_long.txt",std::ifstream::binary);
		for(std::size_t i{};i!=N;++i)
			fin>>buffer[i];
	}
	{
		fast_io::timer t("output");
		fast_io::obuf_file obf("ifstream.txt");
		for(std::size_t i{};i!=N;++i)
			println(obf,buffer[i]);
	}
}