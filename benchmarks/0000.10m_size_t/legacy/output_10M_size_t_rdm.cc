#include"../timer.h"
#include<fstream>
#include"../../include/fast_io.h"
#include"../../include/fast_io_device.h"
//#include"../../include/fast_io_crypto.h"
#include"../../include/fast_io_legacy.h"
#include<exception>
#include<cmath>
#include<memory>
#include<cstdio>
#include<random>

int main()
#ifdef __cpp_exceptions
try
#endif
{
	constexpr std::size_t N(10000000);
	std::vector<std::uint64_t> vec;
	vec.reserve(N);
	std::random_device device;
	std::mt19937_64 eng(device());
	std::uniform_int_distribution<std::uint64_t> dis(0,std::numeric_limits<std::uint64_t>::max());
	for(std::size_t i(0);i!=N;++i)
		vec.emplace_back(dis(eng));
	{
	fast_io::timer t("u8obuf_file1");
	fast_io::u8obuf_file u8obuf_file("u8obuf_file1.txt");
	for(std::size_t i(0);i!=N;++i)
		println(u8obuf_file,vec[i]);
	}
	{
	fast_io::timer t("u8obuf_file");
	fast_io::u8obuf_file u8obuf_file("u8obuf_file.txt");
	for(std::size_t i(0);i!=N;++i)
		println(u8obuf_file,vec[i]);
	}
	{
	fast_io::timer t("u8obuf_file");
	fast_io::u8obuf_file u8obuf_file_old("u8obuf_file_old.txt");
	for(std::size_t i(0);i!=N;++i)
		println(u8obuf_file_old,fast_io::dec(vec[i]));
	}
}
#ifdef __cpp_exceptions
catch(std::exception const& e)
{
	println(fast_io::err,e);
	return 1;
}
#endif