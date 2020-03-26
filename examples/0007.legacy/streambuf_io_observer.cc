#include<iostream>
#include"../../include/fast_io_legacy.h"

int main()
{
	fast_io::streambuf_io_observer iob(std::cout.rdbuf());
	println(iob,"Hello World\n");
}
