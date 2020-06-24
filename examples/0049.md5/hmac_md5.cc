#include"../../include/fast_io.h"
#include"../../include/fast_io_device.h"
#include"../../include/fast_io_crypto.h"

/*
This is just for demo purpose. You should avoid md5 in general because it is extremely insecure.
https://en.wikipedia.org/wiki/MD5
*/

int main(int argc,char** argv)
try
{
	if(argc!=3)
	{
		perr("Usage: ",fast_io::chvw(*argv)," <file> <hmac md5 key>\n");
		return 1;
	}
	auto t0{std::chrono::high_resolution_clock::now()};
	fast_io::hmac_md5 m(argv[2]);
	fast_io::hash_processor processor(m);
	fast_io::ibuf_file ibf(argv[1]);
	auto transmitted{transmit(processor,ibf)};
	processor.do_final();
	println(m," *",fast_io::chvw(argv[1]),"\nTransmitted:",transmitted,u8" bytes\tElapsed Time:",std::chrono::high_resolution_clock::now()-t0);
}
catch(std::exception const& e)
{
	perrln(e);
	return 2;
}