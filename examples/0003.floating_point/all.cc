#include"../../include/fast_io.h"
#include"../../include/fast_io_in.h"

int main()
{
	double d;
	scan(d);
	println("general:",d,
		"\nfixed:",fast_io::fixed(d),
		"\nscientific:",fast_io::scientific(d),
		"\ngeneral with 10 precisions:",fast_io::general(d,10),
		"\nfixed with 10 precisions:",fast_io::fixed(d,10),
		"\nscientific with 10 precisions:",fast_io::scientific(d,10));
}