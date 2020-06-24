//requires -maes -msse2

#include"../../timer.h"
#include<fstream>
#include"../../../include/fast_io_device.h"
#include"../../../include/fast_io_crypto.h"
#include"../../../include/fast_io_legacy.h"
#include<exception>
#include<cmath>
#include<memory>
#include<cstdio>
#include<random>
#include<iomanip>
#include<charconv>

//standard library implementation is just too slow that wastes my time

int main()
try
{
	std::size_t constexpr N(10000000);
	std::vector<double> vec;
	vec.reserve(N);
	std::random_device device;
	std::mt19937_64 eng(device());
	std::uniform_real_distribution dis(-1000.0,1000.0);
	for(std::size_t i(0);i!=N;++i)
		vec.emplace_back(dis(eng));

	{
	fast_io::timer t("u8obuf_file");
	fast_io::u8obuf_file obuf_file("u8obuf_filedb.txt");
	for(std::size_t i(0);i!=N;++i)
		println(obuf_file,vec[i]);
	}
	{
	fast_io::timer t("u8obuf_file_aes");
	std::array<unsigned char, 16> key{1,2,3,4,5,6,7,8,1,2,3,4,5,6,7,8};
	std::array<unsigned char, 16> iv{1,2,3,4,5,6,7,8,1,2,3,4,5,6,7,8};
	fast_io::crypto::ocbc_encrypt<fast_io::obuf_file, fast_io::crypto::aes::aes_enc_128> 
	ob(std::piecewise_construct,std::forward_as_tuple("aes_db_encrypt.txt"),
	std::forward_as_tuple(std::as_writable_bytes(std::span(key)), std::as_writable_bytes(std::span(iv))));
	for(std::size_t i(0);i!=N;++i)
		println(ob,vec[i]);
	}
	{
	fast_io::timer t("u8obuf_file_speck");
	std::array<unsigned char, 16> key{1,2,3,4,5,6,7,8,1,2,3,4,5,6,7,8};
	std::array<unsigned char, 16> iv{1,2,3,4,5,6,7,8,1,2,3,4,5,6,7,8};
	fast_io::crypto::ocbc_encrypt<fast_io::obuf_file, fast_io::crypto::speck::speck_enc_128_128> 
	ob(std::piecewise_construct,std::forward_as_tuple("speck_db_encrypt.txt"),
	std::forward_as_tuple(std::as_writable_bytes(std::span(key)), std::as_writable_bytes(std::span(iv))));
	for(std::size_t i(0);i!=N;++i)
		println(ob,vec[i]);
	}
}
catch(std::exception const& e)
{
	perrln(e);
	return 1;
}
