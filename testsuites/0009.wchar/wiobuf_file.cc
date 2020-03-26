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
	fast_io::wobuf_file wobf("wobuf_file.txt");
	for(std::size_t i{};i!=N;++i)
		println(wobf,vec[i]);
	}
	std::vector<double> buffer(N);
	{
	fast_io::timer t("input");
	fast_io::wibuf_file wibf("wobuf_file.txt");
	fast_io::wobuf_file wobf_out("wobuf_file_verify.txt",fast_io::open_interface<fast_io::open_mode::out|fast_io::open_mode::binary>);
	for(std::size_t i{};i!=N;++i)
	{
		scan(wibf,buffer[i]);
		println(wobf_out,buffer[i]);
	}
	}
}