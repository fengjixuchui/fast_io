#include"../../timer.h"
#include<fstream>
#include<vector>
#include<random>

int main()
{
	constexpr std::size_t N(10000000);
	std::vector<long double> vec;
	vec.reserve(N);
	std::mt19937_64 eng;
	std::uniform_real_distribution dis(-10000.0L,10000.0L);
	for(std::size_t i(0);i!=N;++i)
		vec.emplace_back(dis(eng));
	{
	fast_io::timer t("output");
	std::ofstream fout("ofstream.txt",std::ofstream::binary);
	auto& rdbuf(*fout.rdbuf());
	for(std::size_t i{};i!=N;++i)
	{
		fout<<vec[i];
		rdbuf.sputc(u8'\n');
	}
	}
}