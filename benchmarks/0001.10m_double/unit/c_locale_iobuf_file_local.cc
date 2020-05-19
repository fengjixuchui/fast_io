#include"../../timer.h"
#include"../../../include/fast_io.h"
#include"../../../include/fast_io_device.h"
//#include"../../include/fast_io_crypto.h"
#include"../../../include/fast_io_legacy.h"
#include"../../../include/fast_io_locale.h"
#include"../../../include/fast_io_locale_device.h"
#include<random>

int main()
{
	constexpr std::size_t N(10000000);
	std::vector<double> vec;
	vec.reserve(N);
	std::mt19937_64 eng;
	std::uniform_real_distribution dis(-10000.0,10000.0);
	for(std::size_t i(0);i!=N;++i)
		vec.emplace_back(dis(eng));
	fast_io::c_locale loc(fast_io::c_locale_category::all);
	fast_io::c_lconv_storage stg(loc);
	fast_io::c_ctype_isspace space(loc);
	{
	fast_io::timer t("output");
	fast_io::c_locale_obuf_file obf("c_locale_obuf_file_local.txt",{.lconv=stg});
	for(std::size_t i{};i!=N;++i)
		println(obf,vec[i]);
	}
}