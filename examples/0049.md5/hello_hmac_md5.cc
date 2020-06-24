#include"../../include/fast_io.h"
#include"../../include/fast_io_device.h"
#include"../../include/fast_io_crypto.h"

int main(int argc,char** argv)
{
	fast_io::hmac_md5 m("Hello");
	fast_io::hash_processor processor(m);
	print(processor,"Hello hmac md5");
	processor.do_final();
	println(m);
}