#include"../../timer.h"
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
	std::uniform_real_distribution dis(-10000.0L,10000.0L);
	for(std::size_t i(0);i!=N;++i)
		vec.emplace_back(dis(eng));
	{
	fast_io::timer t("output");
	fast_io::c_file_unlocked cful_out("cful.txt",fast_io::open_interface<fast_io::open_mode::out|fast_io::open_mode::binary>);
	for(std::size_t i{};i!=N;++i)
		println(cful_out,vec[i]);
	}
}