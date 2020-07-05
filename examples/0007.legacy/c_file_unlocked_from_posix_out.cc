#include"../../include/fast_io_legacy.h"

int main()
{
	fast_io::posix_io_handle posix_out(1);	//stdout number
	fast_io::c_file_unlocked csf(std::move(posix_out),"wb");	//call fdopen. Must use std::move since c style file will steal resource from posix handle
	print(csf,"Hello World from fast_io::print\n");
}