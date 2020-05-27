#include"../../include/fast_io.h"
#include"../../include/fast_io_locale.h"

int main()
{
	fast_io::c_locale loc(fast_io::c_locale_category::all,"C");
	fast_io::c_ctype_isspace c_isspace(loc);
	std::string str{};
	scan(fast_io::space(str,c_isspace));
	println(str);
}