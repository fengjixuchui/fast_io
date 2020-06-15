#include"../../timer.h"
#include"../../../include/fast_io.h"
#include"../../../include/fast_io_device.h"
#include"../../../include/fast_io_legacy.h"

int main()
{
	constexpr std::size_t N(10000000);
	{
	fast_io::timer t("output");
	fast_io::obuf_utf8_file<char16_t> obf("iobuf_utf8_file_char16.txt");
	for(std::size_t i{};i!=N;++i)
		println(obf,i);
	}
	std::vector<std::size_t> vec(N);
	{
	fast_io::timer t("input");
	fast_io::ibuf_utf8_file<char16_t> ibf("iobuf_utf8_file_char16.txt");
	for(std::size_t i{};i!=N;++i)
		scan(ibf,vec[i]);
	}
}