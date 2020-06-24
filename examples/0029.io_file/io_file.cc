#include"../../include/fast_io.h"
#include"../../include/fast_io_device.h"

int main()
{
	fast_io::io_file file(fast_io::io_cookie,fast_io::out());
	auto f2(file);
	print(file,"Hello World file\n");
	print(f2,"Hello World f2\n");
}