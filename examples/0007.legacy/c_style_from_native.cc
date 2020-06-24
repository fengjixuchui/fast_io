//windows only

#include"../../include/fast_io.h"

int main()
{
	fast_io::c_file csf(fast_io::native_stdout(),
	fast_io::open_interface<fast_io::open_mode::out|fast_io::open_mode::binary>);
	print(csf,"Hello World from fast_io::print\n");
}
