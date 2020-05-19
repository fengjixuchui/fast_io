#include"../../timer.h"
#include"../../../include/fast_io.h"
#include"../../../include/fast_io_device.h"
#include"../../../include/fast_io_legacy.h"
#include"../../../include/fast_io_locale.h"
#include"../../../include/fast_io_locale_device.h"

int main()
{
	constexpr std::size_t N(10000000);
	fast_io::c_locale loc(fast_io::c_locale_category::all,"C");
	fast_io::c_lconv_storage stg(loc);
	{
	fast_io::timer t("output");
	fast_io::c_locale_obuf_file obf{{"c_locale_obuf_file_C.txt"},{.lconv=stg}};
	for(std::size_t i{};i!=N;++i)
		println(obf,i);
	}

	std::vector<std::size_t> vec(N);
	{
	fast_io::c_ctype_isspace isspace(loc);
	fast_io::timer t("input");
	fast_io::c_locale_ibuf_file ibf("c_locale_obuf_file_C.txt",{.isspace=isspace,.lconv=stg});
	for(std::size_t i{};i!=N;++i)
		scan(ibf,vec[i]);
	}
}