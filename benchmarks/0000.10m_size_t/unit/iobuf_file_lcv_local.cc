#include"../../timer.h"
#include"../../../include/fast_io.h"
#include"../../../include/fast_io_device.h"
#include"../../../include/fast_io_legacy.h"
#include"../../../include/fast_io_locale.h"

int main()
{
	constexpr std::size_t N(10000000);
	{
	fast_io::timer t("output");
	fast_io::c_locale loc(fast_io::c_locale_category::all);
	fast_io::c_lconv_storage stg(loc);
	fast_io::obuf_file obf("obuf_file_lcv_local.txt");
	for(std::size_t i{};i!=N;++i)
		println(obf,fast_io::lcv(stg,i));
	}
}