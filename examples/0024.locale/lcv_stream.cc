#include"../../include/fast_io.h"
#include"../../include/fast_io_locale_device.h"

int main()
{
	fast_io::c_locale loc(fast_io::c_locale_category::all);
	fast_io::c_lconv_storage lconv(loc);
	fast_io::c_ctype_isspace isspace(loc);

	fast_io::c_locale_obuf_file obflc{{"lcv_stream.txt"},{.lconv=lconv}};
	fast_io::c_locale_ibuf_file ibflc{{"s.txt"},{.isspace=isspace,.lconv=lconv}};
	println(obflc,"Hello World:",412412436346);
	int w;
	scan(ibflc,w);
}