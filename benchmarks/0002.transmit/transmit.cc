#include"../timer.h"
#include"../../include/fast_io.h"
#include"../../include/fast_io_device.h"
#include"../../include/fast_io_legacy.h"
#include"../../include/fast_io_crypto.h"
#include<fstream>

int main()
try
{
	{
		fast_io::timer tm("ofstream <= ifstream");
		std::ifstream ib("large_file.txt",std::ifstream::binary);
		std::ofstream ob("large_file_ifstream_to_ofstream.txt",std::ofstream::binary);
		ob<<ib.rdbuf();
	}
	{
		fast_io::timer tm("ofstream fiob <= ifstream fiob");
		std::ifstream ib("large_file.txt",std::ifstream::binary);
		std::ofstream ob("large_file_ifstream_fiob_to_ofstream_fiob.txt",std::ofstream::binary);
		fast_io::filebuf_io_observer ib_fiob{ib.rdbuf()};
		fast_io::filebuf_io_observer ob_fiob{ob.rdbuf()};

		transmit(ob_fiob,ib_fiob);
	}
	{
		fast_io::timer tm("obuf_file <= ibuf_file");
		fast_io::ibuf_file ib("large_file.txt");
		fast_io::obuf_file ob("large_file_ibuf_to_obuf.txt");
		transmit(ob,ib);
	}
	{
		fast_io::timer tm("onative_file <= inative_file");
		fast_io::inative_file ib("large_file.txt");
		fast_io::onative_file ob("large_file_inative_file_to_onative_file.txt");
		transmit(ob,ib);
	}
	{
		fast_io::timer tm("c_file <= ibuf_file");
		fast_io::ibuf_file ib("large_file.txt");
		fast_io::c_file csf("large_file_ibuf_to_c_file.txt","wb");
		transmit(csf,ib);
	}
/*
	{
		fast_io::timer tm("spec enc 128 128 ctr crypt obuf file <= ibuf_file");
		std::array<unsigned char, 16> key{1,2,3,4,5,6,7,8,1,2,3,4,5,6,7,8};
		std::array<unsigned char, 16> iv{1,2,3,4,5,6,7,8,1,2,3,4,5,6,7,8};
		fast_io::ibuf_file ib("large_file.txt");
		fast_io::crypto::octr_encrypt<fast_io::obuf_file, fast_io::crypto::speck::speck_enc_128_128> 
		ob(std::piecewise_construct,std::forward_as_tuple("speck_ctr_encrypt.txt"),
		std::forward_as_tuple(std::as_writable_bytes(std::span(key)), std::as_writable_bytes(std::span(iv))));
		transmit(ob,ib);
	}
	{
		fast_io::timer tm("aes_enc_128 ctr crypt obuf file <= ibuf_file");
		std::array<unsigned char, 16> key{1,2,3,4,5,6,7,8,1,2,3,4,5,6,7,8};
		std::array<unsigned char, 16> iv{1,2,3,4,5,6,7,8,1,2,3,4,5,6,7,8};
		fast_io::ibuf_file ib("large_file.txt");
		fast_io::crypto::octr_encrypt<fast_io::obuf_file, fast_io::crypto::aes::aes_enc_128> 
		ob(std::piecewise_construct,std::forward_as_tuple("aes_ctr_encrypt.txt"),
		std::forward_as_tuple(std::as_writable_bytes(std::span(key)), std::as_writable_bytes(std::span(iv))));
		transmit(ob,ib);
	}*/
}
catch(std::exception const& e)
{
	perrln(e);
}
