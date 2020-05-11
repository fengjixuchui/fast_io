#include"../../include/fast_io.h"
#include"../../include/fast_io_device.h"
#include"../../include/fast_io_legacy.h"

int main()
{
	fast_io::c_file cf(fast_io::io_cookie,"wb",fast_io::out);
	fprintf(cf.native_handle(),"Hello World from fprintf, number: %d\n",5);
	println(cf,"Hello World from fast_io::println, number: ",100);
}