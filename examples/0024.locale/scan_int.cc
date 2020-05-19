#include"../../include/fast_io.h"
#include"../../include/fast_io_locale.h"
#include"../../include/fast_io_in.h"

int main()
{
	fast_io::c_locale loc(fast_io::c_locale_category::all,"C");
	fast_io::c_ctype_isspace c_isspace(loc);
	int value{};
	scan(fast_io::space(value,c_isspace));
	println(value);
}