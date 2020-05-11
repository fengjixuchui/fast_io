#include"../../../include/fast_io.h"
#include"../../../include/fast_io_device.h"
#include"../../../include/fast_io_driver/openssl_driver.h"


int main()
{
	fast_io::openssl::bio_file bio(fast_io::io_cookie,std::in_place_type<fast_io::onative_file>,"w.txt");
	print(bio,"Hello World from fast_io::print\n");
	BIO_printf(bio.native_handle(),"Hello World from BIO_printf\n");
}
