#include"../../timer.h"
#include"../../../include/fast_io.h"
#include"../../../include/fast_io_device.h"
#include"../../../include/fast_io_legacy.h"

int main()
{
	constexpr std::size_t N(10000000);
	{
	fast_io::timer t("output");
	fast_io::wobuf_file obf("wobuf_file.txt");
	for(std::size_t i{};i!=N;++i)
		println(obf,i);
	}
	std::vector<std::size_t> vec(N);
	{
	fast_io::timer t("input");
	fast_io::wibuf_file ibf("wobuf_file.txt");
	for(std::size_t i{};i!=N;++i)
		scan(ibf,vec[i]);
	}
}