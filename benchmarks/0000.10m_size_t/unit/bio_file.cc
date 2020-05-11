#include"../../timer.h"
#include"../../../include/fast_io_device.h"
#include"../../../include/fast_io_driver/openssl_driver.h"


int main()
{
	constexpr std::size_t N(10000000);
	{
	fast_io::timer t("output");
	fast_io::openssl::bio_file bio("BIO_printf.txt",fast_io::open_interface<fast_io::open_mode::binary|fast_io::open_mode::out>);
	for(std::size_t i{};i!=N;++i)
		println(bio,i);
	}
}
