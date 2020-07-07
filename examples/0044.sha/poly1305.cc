#include"../../include/fast_io.h"
#include"../../include/fast_io_device.h"
#include"../../include/fast_io_crypto.h"

int main(int argc,char** argv)
try
{
	if(argc!=3)
	{
		perr("Usage: ",fast_io::chvw(*argv)," <file> <poly1305 key>\n");
		return 1;
	}
	auto t0{std::chrono::high_resolution_clock::now()};
	fast_io::poly1305 poly1305_mac(argv[2]);
	fast_io::hash_processor processor(poly1305_mac);
	fast_io::ibuf_file ibf(argv[1]);
	auto transmitted{transmit(processor,ibf)};
	processor.do_final();
	println(poly1305_mac," *",fast_io::chvw(argv[1]),"\nTransmitted:",transmitted,u8" bytes\tElapsed Time:",std::chrono::high_resolution_clock::now()-t0);
}
catch(std::exception const& e)
{
	perrln(e);
	return 2;
}