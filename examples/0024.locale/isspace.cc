#include"../../include/fast_io.h"
#include"../../include/fast_io_locale.h"

int main()
{
	fast_io::c_locale loc(fast_io::c_locale_category::all,"C");
	fast_io::c_ctype_isspace space(loc);
	for(std::size_t i{};i!=256;++i)
	{
		println(i," ",space(static_cast<char>(i)));
	}
}