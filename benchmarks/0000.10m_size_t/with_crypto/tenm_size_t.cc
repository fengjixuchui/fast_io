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
	std::size_t constexpr N(10000000);
	{
	fast_io::timer t("u8obuf_file plain_text");
	fast_io::u8obuf_file u8obuf_file("plain_text.txt");
	for(std::size_t i(0);i!=N;++i)
		println(u8obuf_file,i);
	}
	{
	fast_io::timer t("u8obuf_file ecb speck");
	std::array<unsigned char, 16> key{1,2,3,4,5,6,7,8,1,2,3,4,5,6,7,8};
	fast_io::crypto::oecb<fast_io::obuf_file, fast_io::crypto::speck::speck_enc_128_128> 
	ob(std::piecewise_construct,std::forward_as_tuple("speck_ecb_encrypt.txt"),
	std::forward_as_tuple(std::as_bytes(std::span(key))));
	for(std::size_t i(0);i!=N;++i)
		println(ob,i);
	}

	{
	fast_io::timer t("u8obuf_file ecb aes");
	std::array<unsigned char, 16> key{1,2,3,4,5,6,7,8,1,2,3,4,5,6,7,8};
	fast_io::crypto::oecb<fast_io::obuf_file, fast_io::crypto::aes::aes_enc_128> 
	ob(std::piecewise_construct,std::forward_as_tuple("aes_ecb_encrypt.txt"),
	std::forward_as_tuple(std::as_bytes(std::span(key))));
	for(std::size_t i(0);i!=N;++i)
		println(ob,i);
	}
	{
	fast_io::timer t("u8obuf_file cbc speck");
	std::array<unsigned char, 16> key{1,2,3,4,5,6,7,8,1,2,3,4,5,6,7,8};
	std::array<unsigned char, 16> iv{1,2,3,4,5,6,7,8,1,2,3,4,5,6,7,8};
	fast_io::crypto::ocbc_encrypt<fast_io::obuf_file, fast_io::crypto::speck::speck_enc_128_128> 
	ob(std::piecewise_construct,std::forward_as_tuple("speck_cbc_encrypt.txt"),
	std::forward_as_tuple(std::as_bytes(std::span(key)), std::as_bytes(std::span(iv))));
	for(std::size_t i(0);i!=N;++i)
		println(ob,i);
	}
	{
	fast_io::timer t("u8obuf_file cbc aes");
	std::array<unsigned char, 16> key{1,2,3,4,5,6,7,8,1,2,3,4,5,6,7,8};
	std::array<unsigned char, 16> iv{1,2,3,4,5,6,7,8,1,2,3,4,5,6,7,8};
	fast_io::crypto::ocbc_encrypt<fast_io::obuf_file, fast_io::crypto::aes::aes_enc_128> 
	ob(std::piecewise_construct,std::forward_as_tuple("aes_cbc_encrypt.txt"),
	std::forward_as_tuple(std::as_bytes(std::span(key)),std::as_bytes(std::span(iv))));
	for(std::size_t i(0);i!=N;++i)
		println(ob,i);
	}
	{
	fast_io::timer t("u8obuf_file ctr le aes");
	std::array<unsigned char, 16> key{1,2,3,4,5,6,7,8,1,2,3,4,5,6,7,8};
	std::array<unsigned char, 8> nonce{1,2,3,4,5,6,7,8};
	fast_io::crypto::octr_little_endian<fast_io::obuf_file, fast_io::crypto::aes::aes_enc_128> 
	ob(std::piecewise_construct,std::forward_as_tuple("aes_ctr_le_encrypt.txt"),
	std::forward_as_tuple(std::as_bytes(std::span(key)), std::as_bytes(std::span(nonce))));
	for(std::size_t i(0);i!=N;++i)
		println(ob,i);
	}
	{
	fast_io::timer t("u8obuf_file ctr le speck");
	std::array<unsigned char, 16> key{1,2,3,4,5,6,7,8,1,2,3,4,5,6,7,8};
	std::array<unsigned char, 8> nonce{1,2,3,4,5,6,7,8};
	fast_io::crypto::octr_little_endian<fast_io::obuf_file, fast_io::crypto::speck::speck_enc_128_128> 
	ob(std::piecewise_construct,std::forward_as_tuple("speck_ctr_le_encrypt.txt"),
	std::forward_as_tuple(std::as_bytes(std::span(key)), std::as_bytes(std::span(nonce))));
	for(std::size_t i(0);i!=N;++i)
		println(ob,i);
	}
	{
	fast_io::timer t("u8obuf_file ctr be aes");
	std::array<unsigned char, 16> key{1,2,3,4,5,6,7,8,1,2,3,4,5,6,7,8};
	std::array<unsigned char, 8> nonce{1,2,3,4,5,6,7,8};
	fast_io::crypto::octr_big_endian<fast_io::obuf_file, fast_io::crypto::aes::aes_enc_128> 
	ob(std::piecewise_construct,std::forward_as_tuple("aes_ctr_be_encrypt.txt"),
	std::forward_as_tuple(std::as_bytes(std::span(key)), std::as_bytes(std::span(nonce))));
	for(std::size_t i(0);i!=N;++i)
		println(ob,i);
	}
	{
	fast_io::timer t("u8obuf_file ctr be speck");
	std::array<unsigned char, 16> key{1,2,3,4,5,6,7,8,1,2,3,4,5,6,7,8};
	std::array<unsigned char, 8> nonce{1,2,3,4,5,6,7,8};
	fast_io::crypto::octr_big_endian<fast_io::obuf_file, fast_io::crypto::speck::speck_enc_128_128> 
	ob(std::piecewise_construct,std::forward_as_tuple("speck_ctr_be_encrypt.txt"),
	std::forward_as_tuple(std::as_bytes(std::span(key)), std::as_bytes(std::span(nonce))));
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