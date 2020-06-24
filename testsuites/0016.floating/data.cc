#include"../../include/fast_io.h"
#include"../../include/fast_io_device.h"

int main()
{
	fast_io::ibuf_file ibf("data.txt");
	fast_io::obuf_file obf("res.txt");
	for(double d;scan<true>(ibf,d);println(obf,d));
}
