#include"../../timer.h"
#include"../../../include/fast_io.h"
#include"../../../include/fast_io_device.h"
#include"../../../include/fast_io_legacy.h"
#include<random>

int main()
{
	constexpr std::size_t N(10000000);
	std::vector<double> vec;
	vec.reserve(N);
	std::mt19937_64 eng;
	std::uniform_real_distribution dis(-10000.0,10000.0);
	for(std::size_t i(0);i!=N;++i)
		vec.emplace_back(dis(eng));
	std::vector<double> buffer(N);
	{
	fast_io::timer t("input");
	std::ifstream fin("obuf_file.txt",std::ios::binary);
	for(std::size_t i{};i!=N;++i)
		fin>>buffer[i];
	}
}