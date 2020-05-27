#include"../../include/fast_io.h"

int main()
{
	std::size_t a,b;
	scan(fast_io::bin(a),fast_io::bin(b));
	println(fast_io::bin(a),"(dec:",a,")+",fast_io::bin(b),"(dec:",b,")=",fast_io::bin(a+b),"(dec:",a+b,")");

}