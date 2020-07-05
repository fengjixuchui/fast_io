#include"../../include/fast_io_legacy.h"

int main()
{
	fast_io::posix_io_handle posix_out(1);	//stdout number 1
	fast_io::c_file csf(std::move(posix_out),fast_io::open_mode::out|fast_io::open_mode::binary);	//call fdopen. We can use C++ style open mode
	print(csf,"Hello World from fast_io::print\n");
}
