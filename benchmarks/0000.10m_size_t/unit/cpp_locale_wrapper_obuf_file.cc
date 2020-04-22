#include"../../timer.h"
#include"../../../include/fast_io.h"
#include"../../../include/fast_io_device.h"
#include"../../../include/fast_io_legacy.h"

int main()
{
	constexpr std::size_t N(10000000);
	{
	fast_io::timer t("output");
	fast_io::cpp_locale_wrapper<fast_io::obuf_file> obf("cpp_locale_wrapper_obuf_file.txt");
	for(std::size_t i{};i!=N;++i)
		println(obf,i);
	}
}