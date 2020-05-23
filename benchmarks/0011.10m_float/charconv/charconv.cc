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
	std::vector<float> vec;
	vec.reserve(N);
	std::mt19937_64 eng;
	std::uniform_real_distribution dis(-10000.0f,10000.0f);
	for(std::size_t i(0);i!=N;++i)
		vec.emplace_back(dis(eng));
	{
	fast_io::timer t("output");
	fast_io::obuf_file obf("charconv.txt");
	for(std::size_t i{};i!=N;++i)
	{
		auto start = oreserve(obf,40);
		if(start)[[likely]]
		{
			auto [p,ec]=to_chars(start,start+40,vec[i],std::chars_format::general);
			*p++='\n';
			orelease(obf,p);
		}
		else
		{
			std::array<char,40> buffer;
			auto [p,ec]=to_chars(buffer.data(),buffer.data()+buffer.size(),vec[i],std::chars_format::general);
			*p++='\n';
			write(obf,buffer.data(),p);
		}
	}
	}
}