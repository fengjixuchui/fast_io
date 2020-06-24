#include"../../../include/fast_io_device.h"
#include"../../../include/fast_io.h"
#include<random>

int main()
{

	constexpr std::size_t N(200000);
	std::mt19937_64 eng;
	std::uniform_int_distribution<std::size_t> digits(17,150);
	std::uniform_int_distribution<std::size_t> digits2(0,10000);
	std::uniform_int_distribution<char8_t> chs(u8'0',u8'9');
	std::bernoulli_distribution ber;
	fast_io::obuf_file obf("very_long.txt");
	for(std::size_t i{};i!=N;++i)
	{
		auto sz{digits(eng)};
		for(std::size_t j{};j!=sz;++j)
			put(obf,chs(eng));
		if(ber(eng))
		{
			put(obf,u8'.');
			auto sz{digits2(eng)};
			for(std::size_t j{};j!=sz;++j)
				put(obf,chs(eng));
		}
		put(obf,u8'\n');
	}
	for(std::size_t i{};i!=N;++i)
	{
		put(obf,u8'0');
		put(obf,u8'.');
		auto sz{digits2(eng)};
		for(std::size_t j{};j!=sz;++j)
			put(obf,u8'0');
		auto sz1{digits2(eng)};
		for(std::size_t j{};j!=sz1;++j)
			put(obf,chs(eng));
		put(obf,u8'\n');
	}
}