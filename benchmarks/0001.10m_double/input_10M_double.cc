//Please run output_10M_double before this

#include"../timer.h"
#include<fstream>
#include"../../include/fast_io.h"
#include"../../include/fast_io_device.h"
#include"../../include/fast_io_legacy.h"
#include<exception>
#include<memory>
#include<cstdio>
#include<vector>

int main()
try
{
	std::size_t constexpr N(10000000);
	std::vector<double> v(N);
/*	{
	cqw::timer t("std::FILE*");
	std::unique_ptr<std::FILE,decltype(fclose)*> fp(std::fopen("obufdb.txt","rb"),fclose);
	for(std::size_t i(0);i!=N;++i)
		fscanf(fp.get(),"%lf",v.data()+i);
	}
	{
	cqw::timer t("std::ifstream");
	std::ifstream fin("obufdb.txt",std::ifstream::binary);
	for(std::size_t i(0);i!=N;++i)
		fin>>v[i];
	}
	{
	cqw::timer t("stream_view for std::ifstream");
	fast_io::stream_view<std::ifstream> view("cfilestardb.txt",std::ifstream::binary);
	for(std::size_t i(0);i!=N;++i)
		scan(view,v[i]);
	}
	{
	cqw::timer t("streambuf_view for std::ifstream");
	std::ifstream fin("cfilestardb.txt",std::ifstream::binary);
	fast_io::streambuf_view view(fin.rdbuf());
	for(std::size_t i(0);i!=N;++i)
		scan(view,v[i]);
	}*/
	{
	fast_io::timer t("ibuf");
	fast_io::ibuf_file ibuf("obuf_filedb.txt");
	for(std::size_t i(0);i!=N;++i)
		scan(ibuf,v[i]);
	}
	{
	fast_io::timer t("hacked c_file_unlocked");
	fast_io::obuf_file obf("csful.txt");
	fast_io::ibuf_file csfu("obuf_filedb.txt");
//	std::array<char,65536> buffer;
//	setvbuf(csfu.fp,buffer.data(),_IOFBF,buffer.size());
	for(std::size_t i(0);i!=N;++i)
	{
		scan(csfu,v[i]);
		println(obf,v[i]);
	}
	}
/*	{
	cqw::timer t("ibuf_mutex ryu");
	fast_io::ibuf_mutex ibuf("obufdb.txt");
	for(std::size_t i(0);i!=N;++i)
		scan(ibuf,v[i]);
	}
	{
	cqw::timer t("ibuf text");
	fast_io::text_view<fast_io::ibuf> view("obufdb.txt");
	for(std::size_t i(0);i!=N;++i)
		scan(view,v[i]);
	}
	{
	cqw::timer t("dynamic standard input stream ibuf");
	fast_io::dynamic_character_input_stream ibuf(std::in_place_type<fast_io::ibuf>,"cfilestardb.txt");
	for(std::size_t i(0);i!=N;++i)
		scan(ibuf,v[i]);
	}
	{
	cqw::timer t("ibuf_dynamic inative_file");
	fast_io::ibuf_dynamic ibuf(std::in_place_type<fast_io::inative_file>,"cfilestardb.txt");
	for(std::size_t i(0);i!=N;++i)
		scan(ibuf,v[i]);
	}
	{
	cqw::timer t("speck128/128");
	fast_io::crypto::basic_ictr<fast_io::ibuf, fast_io::crypto::speck::speck_dec_128_128> enc_stream(
		std::array<uint8_t, 16>{'8',u8'3',u8'3',u8'4',u8';',u8'2',u8'3',u8'4',u8'a',u8'2',u8'c',u8'4',u8']',u8'0',u8'3',u8'4'},
		std::array<uint8_t, 8>{'1',u8'2',u8'3',u8'4',u8'1',u8'2',u8'3',u8'4'},"speckdb.txt");
	for(auto & e : v)
		scan(enc_stream,e);
	}*/
}
catch(std::exception const& e)
{
	perrln(e);
	return 1;
}