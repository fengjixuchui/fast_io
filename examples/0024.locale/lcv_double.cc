#include"../../include/fast_io.h"
#include"../../include/fast_io_locale.h"

int main()
{
	fast_io::c_locale loc(fast_io::c_locale_category::all);
	fast_io::c_lconv_storage stg(loc);
	println("default:",12141241241.436346436,"\nlocal:",fast_io::lcv(stg,12141241241.436346436));
}