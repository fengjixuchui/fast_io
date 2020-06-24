#include"../../timer.h"
#include"../../../include/fast_io_device.h"
#include"../../../include/fast_io.h"
#include<charconv>

int main()
{
	constexpr std::size_t N{400000};
	std::vector<double> buffer(N);
	fast_io::ibuf_file ibf("very_long.txt");
	{
		fast_io::timer tm("input");
		std::string str;
		str.reserve(20000);
		for(std::size_t i{};i!=N;++i)
		{
			scan(ibf,str);
			std::from_chars(str.data(),str.data()+str.size(),buffer[i]);
		}
	}
	{
		fast_io::timer t("output");
		fast_io::obuf_file obf("charconv.txt");
		for(std::size_t i{};i!=N;++i)
			println(obf,buffer[i]);
	}
}