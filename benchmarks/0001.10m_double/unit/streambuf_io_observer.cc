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
	std::vector<double> vec;
	vec.reserve(N);
	std::random_device device;
	std::mt19937_64 eng(device());
	std::uniform_real_distribution dis(-1000.0,1000.0);
	for(std::size_t i(0);i!=N;++i)
		vec.emplace_back(dis(eng));
	{
	fast_io::timer t("output");
	std::ofstream fout("streambuf_io_observer.txt",std::ofstream::binary);
	fast_io::streambuf_io_observer fob{fout.rdbuf()};
	for(std::size_t i{};i!=N;++i)
		println(fob,vec[i]);
	}
	std::vector<double> buffer(N);
	{
	fast_io::timer t("input");
	std::ifstream fin("streambuf_io_observer.txt",std::ifstream::binary);
	fast_io::streambuf_io_observer fob{fin.rdbuf()};
	for(std::size_t i{};i!=N;++i)
		scan(fob,buffer[i]);
	}
}