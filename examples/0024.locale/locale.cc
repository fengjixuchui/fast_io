#include"../../include/fast_io.h"
#include"../../include/fast_io_locale.h"
#include"../../include/fast_io_device.h"

int main()
{
	fast_io::wobuf_file wobf("locale.txt");
	std::string_view str_vw("我是猪");
	fast_io::c_locale loc(fast_io::c_locale_category::all);
	print(wobf,fast_io::c_locale_mbstowcs(loc,str_vw.cbegin(),str_vw.cend()));
}
