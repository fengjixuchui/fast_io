#include"../timer.h"
#include"../../include/fast_io.h"
#include"../../include/fast_io_device.h"
#include"../../include/fast_io_legacy.h"
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
	fast_io::wc_file_unlocked wcful_out("wcful.txt",fast_io::open_interface<fast_io::open_mode::out|fast_io::open_mode::binary>);
	for(std::size_t i{};i!=N;++i)
		println(wcful_out,vec[i]);
	}

	std::vector<double> buffer(N);
	{
	fast_io::timer t("input");
	fast_io::wc_file_unlocked wcful("wcful.txt",fast_io::open_interface<fast_io::open_mode::in|fast_io::open_mode::binary>);
	fast_io::wc_file_unlocked wcful_out("wcful_verify.txt",fast_io::open_interface<fast_io::open_mode::out|fast_io::open_mode::binary>);
	for(std::size_t i{};i!=N;++i)
	{
		scan(wcful,buffer[i]);
		println(wcful_out,buffer[i]);
	}
	}
}