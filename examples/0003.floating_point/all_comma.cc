#include"../../include/fast_io.h"
#include"../../include/fast_io_in.h"

int main()
{
	double d;
	scan(fast_io::comma(d));
	println("general:",fast_io::comma(d),
		"\nfixed:",fast_io::comma_fixed(d),
		"\nscientific:",
		fast_io::comma_scientific(d),
		"\ngeneral with 10 precisions:",
		fast_io::comma_general(d,10),
		"\nfixed with 10 precisions:",
		fast_io::comma_fixed(d,10),
		"\nscientific with 10 precisions:",
		fast_io::comma_scientific(d,10));
}