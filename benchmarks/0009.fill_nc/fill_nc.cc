#include"../../include/fast_io_device.h"
#include"../../include/fast_io.h"
#include"../timer.h"

int main(int argc, char** argv)
{
	if(argc!=2)
	{
		print(fast_io::err,"Usage: ", *argv," <filesize>\n");
		return 1;
	}
	auto bytes(fast_io::to<std::size_t>(argv[1]));
	fast_io::timer tm("fill_nc");
	fast_io::obuf_file obf("largefile.txt");
	print(obf,fast_io::fill_nc(bytes,u8'0'));
}