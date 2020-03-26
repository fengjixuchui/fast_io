#include"../timer.h"
#include<fstream>
#include"../../include/fast_io_device.h"
//#include"../../include/fast_io_crypto.h"
#include"../../include/fast_io_legacy.h"
#include<exception>
#include<cmath>
#include<memory>
#include<cstdio>
#include<random>
#include<iomanip>
#include<charconv>

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
	fast_io::timer t("fprintf");
	fast_io::c_file cs("csfdb.txt","wb");
	auto fp(cs.native_handle());
	for(std::size_t i(0);i!=N;++i)
		fprintf(fp,"%g\n",vec[i]);
	}
	{
	fast_io::timer t("ofstream");
	std::ofstream fout("ofs.txt");
	for(std::size_t i(0);i!=N;++i)
		fout<<vec[i]<<'\n';
	}
	{
	fast_io::timer t("ofstream tricks");
	std::ofstream fout("ofs_tricks.txt");
	auto &rdbuf(*fout.rdbuf());
	for(std::size_t i(0);i!=N;++i)
	{
		fout<<vec[i];
		rdbuf.sputc('\n');
	}
	}
	{
	fast_io::timer t("ofstream");
	std::ofstream fout("ofs.txt");
	for(std::size_t i(0);i!=N;++i)
		fout<<vec[i]<<'\n';
	}

	{
	fast_io::timer t("cstyle file");
	fast_io::c_file cs("csfdb1.txt","wb");
	for(std::size_t i(0);i!=N;++i)
		println(cs,vec[i]);
	}
	{
	fast_io::timer t("cstyle file unlocked");
	fast_io::c_file_unlocked cs("csfdb1.txt","wb");
	for(std::size_t i(0);i!=N;++i)
		println(cs,vec[i]);
	}
	{
	fast_io::timer t("c_file_unlocked");
	fast_io::c_file_unlocked cs("csfdb2.txt","wb");
	for(std::size_t i(0);i!=N;++i)
		println(cs,vec[i]);
	}
	{
	fast_io::timer t("obuf_file");
	fast_io::obuf_file obuf_file("obuf_filedb.txt");
	for(std::size_t i(0);i!=N;++i)
		println(obuf_file,vec[i]);
	}
	{
	fast_io::timer t("u8obuf_file grisu_exact");
	fast_io::u8obuf_file obuf_file("u8obuf_filedb_grisu_exact.txt");
	for(std::size_t i(0);i!=N;++i)
		println(obuf_file,vec[i]);
	}
#ifndef _MSC_VER
	{
	fast_io::timer t("u8obuf_file int hint");
	fast_io::u8obuf_file obuf_file("u8obuf_filedb_hint.txt");
	for(std::size_t i(0);i!=N;++i)
		println(obuf_file,fast_io::int_hint(vec[i]));
	}
#endif
#if defined(__GLIBCXX__) || defined(_MSC_VER)
	{
	fast_io::timer t("ostream_file");
	fast_io::ostream_file osf("smfdb.txt");
	for(std::size_t i(0);i!=N;++i)
		println(osf,vec[i]);
	}
#endif
#ifdef _MSC_VER
	{
		fast_io::timer t("charconv");
		fast_io::obuf_file obuf_file("charconv.txt");
		std::array<char,100> arr;
		for(std::size_t i(0);i!=N;++i)
		{
			auto [p,ec]=std::to_chars(arr.data(),arr.data()+arr.size(),vec[i]);
			*p=u8'\n';
			write(obuf_file,arr.data(),++p);
		}
	}
#endif
	{
	fast_io::timer t("obuf_file_mutex");
	fast_io::obuf_file_mutex obuf_file("obuf_file_mutexdb.txt");
	for(std::size_t i(0);i!=N;++i)
		println(obuf_file,vec[i]);
	}
/*	{
	fast_io::timer t(u8"speck128/128");
	fast_io::crypto::basic_octr<fast_io::obuf_file, fast_io::crypto::speck::speck_enc_128_128> enc_stream(
		std::array<uint8_t, 16>{u8'8',u8'3',u8'3',u8'4',u8';',u8'2',u8'3',u8'4',u8'a',u8'2',u8'c',u8'4',u8']',u8'0',u8'3',u8'4'}, "encdb.txt");
	}*/
}
catch(std::exception const& e)
{
	println(fast_io::err,e);
	return 1;
}
