#include"../../include/fast_io.h"
#include"../../include/fast_io_in.h"

int main()
{
	double d;
	scan(fast_io::comma(d));
	println(fast_io::comma(d));
	println(fast_io::comma_fixed(d,20));
	println(fast_io::comma_scientific(d,20));
	println(fast_io::comma_general(d,20));
}
