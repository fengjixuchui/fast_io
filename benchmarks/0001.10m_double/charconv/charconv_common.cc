#include"../../timer.h"
#include"../../../include/fast_io.h"
#include"../../../include/fast_io_device.h"
//#include"../../include/fast_io_crypto.h"
#include"../../../include/fast_io_legacy.h"
#include<random>
#include<charconv>

int main()
{
	constexpr std::size_t N(10000000);
	std::vector<double> vec;
	vec.reserve(N);
	std::mt19937_64 eng;
	std::uniform_real_distribution dis(-10000.0,10000.0);
	for(std::size_t i(0);i!=N;++i)
		vec.emplace_back(dis(eng));
	{
	fast_io::timer t("output");
	fast_io::obuf_file obf("charconv_common.txt");
	for(std::size_t i{};i!=N;++i)
	{
		std::array<char,40> buffer;
		auto [p,ec]=to_chars(buffer.data(),buffer.data()+buffer.size(),vec[i],std::chars_format::general);
		*p++='\n';
		write(obf,buffer.data(),p);
	}
	}
}