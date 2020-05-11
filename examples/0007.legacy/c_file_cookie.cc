#include"../../include/fast_io.h"
#include"../../include/fast_io_legacy.h"

int main()
{
	fast_io::c_file cf(fast_io::io_cookie,"wb",std::in_place_type<fast_io::posix_file>,
		"c_file_cookie_posix_file.txt",fast_io::open_interface<fast_io::open_mode::out|fast_io::open_mode::binary>);
	fprintf(cf.native_handle(),"Hello World from fprintf, number: %d\n",5);
	println(cf,"Hello World from fast_io::println, number: ",100);
}