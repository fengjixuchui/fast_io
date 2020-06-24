#include"../../include/fast_io.h"
#include"../../include/fast_io_device.h"
#include"../../include/fast_io_crypto.h"

int main(int argc,char** argv)
{
	fast_io::hmac_sha256 sha("Hello");
	fast_io::hash_processor processor(sha);
	print(processor,"Hello hmac sha256");
	processor.do_final();
	println(sha);
}