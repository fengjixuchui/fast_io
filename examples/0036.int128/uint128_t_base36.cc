#include"../../include/fast_io.h"
#include"../../include/fast_io_in.h"

int main()
{
	__uint128_t a,b;
	scan(fast_io::base<36>(a),fast_io::base<36>(b));
	println(fast_io::base<36,true>(a),"(dec:",a,")+",fast_io::base<36,true>(b),"(dec:",b,")=",fast_io::base<36,true>(a+b),"(dec:",a+b,")");
}