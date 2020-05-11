#include"../../include/fast_io.h"
#include"../../include/fast_io_device.h"
int main()
{
	fast_io::obuf_file obf("w.txt");
	print(obf,fast_io::width(100000,4,false,u8'0'));
}