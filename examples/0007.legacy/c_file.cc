#include"../../include/fast_io_legacy.h"

int main()
{
	fast_io::c_file cfl("cfile.txt",fast_io::open_interface<fast_io::open_mode::out|fast_io::open_mode::binary>);
	fprintf(cfl.native_handle(),"Hello World from fprintf\n");
	print(cfl,"Hello World from fast_io::print\n");
}
