#include"../../include/fast_io.h"
#include"../../include/fast_io_in.h"
#include"../../include/fast_io_locale.h"

int main()
{
	fast_io::c_locale loc(fast_io::c_locale_category::all);
	fast_io::c_lconv_storage stg(loc);
	__int128_t a,b;
	scan(fast_io::base<36>(a),fast_io::base<36>(b));
	println(fast_io::lcv(stg,fast_io::base<36,true>(a)),"(dec:",fast_io::lcv(stg,a),")+",fast_io::lcv(stg,fast_io::base<36,true>(b)),"(dec:",fast_io::lcv(stg,b),")=",fast_io::lcv(stg,fast_io::base<36,true>(a+b)),"(dec:",fast_io::lcv(stg,a+b),")");
}