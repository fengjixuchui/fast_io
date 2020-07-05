#include"../../include/fast_io_legacy.h"

int main()
{
	fast_io::posix_file psxf("posix_to_c_style.txt",fast_io::open_mode::out|fast_io::open_mode::binary);	//gets its internal posix handle
	fast_io::c_file csf(std::move(psxf),"wb");	//call fdopen. Must use std::move since c style file will steal resource from posix handle
	print(csf,"Hello World from fast_io::print\n");
}
