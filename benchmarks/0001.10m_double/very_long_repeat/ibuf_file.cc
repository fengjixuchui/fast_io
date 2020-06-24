#include"../../timer.h"
#include"../../../include/fast_io_device.h"
#include"../../../include/fast_io.h"

int main()
{
	constexpr std::size_t N{1000000};
	std::vector<double> buffer(N);
	{
		fast_io::timer tm("input");
		fast_io::ibuf_file ibf("very_long.txt");
		for(std::size_t i{};i!=N;++i)
			scan(ibf,buffer[i]);
	}
	{
		fast_io::timer t("output");
		fast_io::obuf_file obf("ibuf_file.txt");
		for(std::size_t i{};i!=N;++i)
			println(obf,buffer[i]);
	}
}