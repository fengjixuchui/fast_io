#include"../../include/fast_io.h"

int main()
{
	std::size_t a,b;
	scan(fast_io::hex(a),fast_io::hex(b));
	println(fast_io::hex(a+b));
}