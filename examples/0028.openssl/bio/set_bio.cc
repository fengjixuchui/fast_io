#include"../../../include/fast_io.h"
#include"../../../include/fast_io_device.h"
#include"../../../include/fast_io_driver/openssl_driver.h"


int main()
{
	fast_io::openssl::bio_file rbio(fast_io::io_cookie,std::in_place_type<fast_io::black_hole<char>>);
	std::string str;
	fast_io::openssl::bio_file wbio(fast_io::io_cookie,std::in_place_type<fast_io::ostring_ref<char>>,str);
	fast_io::openssl::ssl_context ssl_ctx(fast_io::openssl::tls_method::tls);
	fast_io::openssl::ssl_file ssl(std::in_place,ssl_ctx);
	set_bio(ssl,std::move(rbio),std::move(wbio));
	try
	{
		connect(ssl);
	}
	catch(fast_io::openssl::openssl_error const& e)
	{
		println(e);
	}
	println("str length:",str.size());
	for(std::size_t i{};i!=str.size();++i)
		println(fast_io::right_width(fast_io::bin(static_cast<char8_t>(str[i])),8,u8'0'),"    ",fast_io::hex(str[i]));
}
