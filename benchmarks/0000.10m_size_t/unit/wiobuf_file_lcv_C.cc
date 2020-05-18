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
	fast_io::wobuf_file obf("wobuf_file_lcv_C.txt");
	fast_io::c_locale loc(fast_io::c_locale_category::all,"C");
	fast_io::wc_lconv_storage stg(loc);
	for(std::size_t i{};i!=N;++i)
		println(obf,fast_io::lcv(stg,i));
	}
	std::vector<std::size_t> vec(N);
	{
	fast_io::timer t("input");
	fast_io::wibuf_file ibf("wobuf_file_lcv_C.txt");
	for(std::size_t i{};i!=N;++i)
		scan(ibf,vec[i]);
	}
}