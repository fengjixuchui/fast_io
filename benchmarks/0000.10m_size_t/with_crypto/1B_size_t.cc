#include"../../timer.h"
#include"../../../include/fast_io.h"
#include"../../../include/fast_io_device.h"
#include"../../../include/fast_io_crypto.h"
#include"../../../include/fast_io_legacy.h"
//standard library implementation is just too slow that wastes my time
int main()
#ifdef __cpp_exceptions
try
#endif
{
	std::size_t constexpr N(1000000000ULL);
	{
	fast_io::timer t("u8obuf_file");
	fast_io::u8obuf_file u8obuf_file("u8obuf_file.txt");
	for(std::size_t i(0);i!=N;++i)
		println(u8obuf_file,i);
	}
	{
	fast_io::timer t("u8obuf_file_aes");
	std::array<unsigned char, 16> key{1,2,3,4,5,6,7,8,1,2,3,4,5,6,7,8};
	std::array<unsigned char, 16> iv{1,2,3,4,5,6,7,8,1,2,3,4,5,6,7,8};
	fast_io::crypto::ocbc_encrypt<fast_io::obuf_file, fast_io::crypto::aes::aes_enc_128> 
	ob(std::piecewise_construct,std::forward_as_tuple("aes_db_encrypt.txt"),
	std::forward_as_tuple(std::as_writable_bytes(std::span(key)), std::as_writable_bytes(std::span(iv))));
	for(std::size_t i(0);i!=N;++i)
		println(ob,i);
	}
	{
	fast_io::timer t("u8obuf_file_speck");
	std::array<unsigned char, 16> key{1,2,3,4,5,6,7,8,1,2,3,4,5,6,7,8};
	std::array<unsigned char, 16> iv{1,2,3,4,5,6,7,8,1,2,3,4,5,6,7,8};
	fast_io::crypto::ocbc_encrypt<fast_io::obuf_file, fast_io::crypto::speck::speck_enc_128_128> 
	ob(std::piecewise_construct,std::forward_as_tuple("speck_db_encrypt.txt"),
	std::forward_as_tuple(std::as_writable_bytes(std::span(key)), std::as_writable_bytes(std::span(iv))));
	for(std::size_t i(0);i!=N;++i)
		println(ob,i);
	}
}
#ifdef __cpp_exceptions
catch(std::exception const& e)
{
	perrln(e);
	return 1;
}
#endif