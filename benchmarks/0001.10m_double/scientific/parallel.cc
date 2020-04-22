#include"../../timer.h"
#include"../../../include/fast_io.h"
#include"../../../include/fast_io_device.h"
//#include"../../include/fast_io_crypto.h"
#include"../../../include/fast_io_legacy.h"
#include<random>
#include<thread>
#include<cfloat>
int main()
{
	constexpr std::size_t N(10000000);
	std::vector<double> vec;
	vec.reserve(N);
	std::mt19937_64 eng;
	std::uniform_real_distribution dis(DBL_MIN,DBL_MAX);
	for(std::size_t i(0);i!=N;++i)
		vec.emplace_back(dis(eng));
	{
	fast_io::timer t("output");
	fast_io::obuf_file obf("parallel.txt");
	print(obf,fast_io::parallel(vec,[](auto const& e)
	{
		return fast_io::line(fast_io::scientific(e));
	}));
	}
}