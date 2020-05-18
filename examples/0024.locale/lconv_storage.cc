#include"../../include/fast_io.h"
#include"../../include/fast_io_locale.h"


int main()
{
	fast_io::c_locale loc(fast_io::c_locale_category::all);
	fast_io::c_lconv_storage stg(loc);
	for(auto const& e : stg.grouping())
		println(static_cast<int>(e));
//	println("grouping:",stg.grouping(),
//	"\nnegative_sign:",stg.negative_sign(),
//	"\ncurrency sign:",stg.currency_symbol());
}