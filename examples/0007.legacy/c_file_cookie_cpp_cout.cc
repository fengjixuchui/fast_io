#include"../../include/fast_io.h"
#include"../../include/fast_io_device.h"
#include"../../include/fast_io_legacy.h"
#include<iostream>

int main()
{
	std::ios::sync_with_stdio(false);
	fast_io::streambuf_io_observer smv{std::cout.rdbuf()};
	fast_io::c_file cf(fast_io::c_file_cookie,"wb",std::ref(smv));
	fprintf(cf.native_handle(),"Hello World from fprintf, number: %d\n",5);
	println(cf,"Hello World from fast_io::println for c_file, number: ",100);
	flush(cf);
	std::cout<<"Hello World from std::cout\n";
	println(smv,"Hello World from fast_io::println from io_observer, number: ",16);
}