#include<zlib.h>
#include"../../include/fast_io.h"
#include"../../include/fast_io_driver/zlib_driver.h"
#include"../../include/fast_io_device.h"

int main(int argc,char** argv)
try
{
	if(argc!=3)
	{
		perr("Usage: ",fast_io::chvw(*argv)," <source gz file path> <dest decompress file path>\n");
		return 1;
	}
	auto t0{std::chrono::high_resolution_clock::now()};
	std::size_t transmitted{};
	{
	fast_io::zlib::gz_file gf(argv[1],"rb");
	fast_io::obuf_file file(argv[2]);
	transmitted=transmit(file,gf);
	}
	println(u8"gz decompression (with zlib) success!\nTransmitted:",transmitted,u8" bytes\nElapsed Time:",std::chrono::high_resolution_clock::now()-t0);
}
catch(std::exception const& e)
{
	perrln(e);
	return 2;
}