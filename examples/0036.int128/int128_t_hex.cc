#include"../../include/fast_io.h"
#include"../../include/fast_io_in.h"

int main()
{
	__int128_t a,b;
	scan(fast_io::hex(a),fast_io::hex(b));
	println(fast_io::hexupper(a),"(dec:",a,")+",fast_io::hexupper(b),"(dec:",b,")=",fast_io::hexupper(a+b),"(dec:",a+b,")");
}