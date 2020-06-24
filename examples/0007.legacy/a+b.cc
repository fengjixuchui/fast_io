#include"../../include/fast_io.h"

int main()
{
	std::size_t a,b;
	scan(fast_io::c_stdin(),a,b);
	println(fast_io::c_stdout(),a+b);
}
