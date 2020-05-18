#include"../../include/fast_io.h"
#include"../../include/fast_io_locale.h"

int main()
{
	fast_io::c_locale loc(fast_io::c_locale_category::all);
	fast_io::c_lconv_storage stg(loc);
	print(fast_io::lcv(stg,fast_io::hexupper(412412436346)));
}