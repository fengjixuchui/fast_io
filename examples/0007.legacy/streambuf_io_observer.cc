#include<iostream>
#include"../../include/fast_io_legacy.h"

int main()
{
	fast_io::streambuf_io_observer iob(std::cout.rdbuf());
	print(iob,"Hello World\n");
}
