#include"../../include/fast_io.h"
#include"../../include/fast_io_device.h"
#include"../../include/fast_io_crypto.h"

/*
This is just for demo purpose. You should avoid sha1 in general because it is insecure.
https://en.wikipedia.org/wiki/SHA-1
*/

int main(int argc,char** argv)
try
{
	if(argc!=2)
	{
		perr("Usage: ",fast_io::chvw(*argv)," <file>\n");
		return 1;
	}
	auto t0{std::chrono::high_resolution_clock::now()};
	fast_io::sha1 sha;
	fast_io::hash_processor processor(sha);
	fast_io::ibuf_file ibf(argv[1]);
	auto transmitted{transmit(processor,ibf)};
	processor.do_final();
	println(sha," *",fast_io::chvw(argv[1]),"\nTransmitted:",transmitted,u8" bytes\tElapsed Time:",std::chrono::high_resolution_clock::now()-t0);
}
catch(std::exception const& e)
{
	perrln(e);
	return 2;
}