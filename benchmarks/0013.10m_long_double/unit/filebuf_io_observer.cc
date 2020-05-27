#include"../../timer.h"
#include<fstream>
#include"../../../include/fast_io.h"
#include"../../../include/fast_io_device.h"
//#include"../../include/fast_io_crypto.h"
#include"../../../include/fast_io_legacy.h"
#include<random>

int main()
{
	constexpr std::size_t N(10000000);
	std::vector<long double> vec;
	vec.reserve(N);
	std::mt19937_64 eng;
	std::uniform_real_distribution dis(-10000.0,10000.0);
	for(std::size_t i(0);i!=N;++i)
		vec.emplace_back(dis(eng));
	{
	fast_io::timer t("output");
	std::ofstream fout("filebuf_io_observer.txt",std::ofstream::binary);
	fast_io::filebuf_io_observer fob{fout.rdbuf()};
	for(std::size_t i{};i!=N;++i)
		println(fob,vec[i]);
	}
}