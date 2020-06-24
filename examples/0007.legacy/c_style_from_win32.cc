//windows only

#include"../../include/fast_io.h"

int main()
{
	fast_io::c_file csf(fast_io::win32_stdout(),fast_io::open::interface<fast_io::open::out|fast_io::open::binary>);
	print(csf,"Hello World from fast_io::print\n");
}
