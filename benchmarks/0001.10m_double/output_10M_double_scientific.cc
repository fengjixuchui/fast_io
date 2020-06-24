#include"../timer.h"
#include<fstream>
#include"../../include/fast_io_device.h"
#include"../../include/fast_io_legacy.h"
#include<exception>
#include<cmath>
#include<memory>
#include<cstdio>
#include<random>
#include<iomanip>
#include<charconv>

//#include"ryu.h"

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
	fast_io::timer t("cstyle file");
	fast_io::c_file cs("csfdb1_sc.txt","wb");
	for(std::size_t i(0);i!=N;++i)
		println(cs,fast_io::scientific(vec[i]));
	}
	{
	fast_io::timer t("cstyle file unlocked");
	fast_io::c_file_unlocked cs("csfdb2_sc.txt","wb");
	for(std::size_t i(0);i!=N;++i)
		println(cs,fast_io::scientific(vec[i]));
	}
	{
	fast_io::timer t("obuf_file");
	fast_io::obuf_file obuf_file("obuf_filedb_sc.txt");
	for(std::size_t i(0);i!=N;++i)
		println(obuf_file,fast_io::scientific(vec[i]));
	}
#ifdef RYU_H
	{
	fast_io::timer t("ryu source");
	fast_io::obuf_file obuf_file("ryu_source.txt");
	std::array<char,40> arr;
	for(std::size_t i(0);i!=N;++i)
	{
		auto v(d2s_buffered_n(vec[i],arr.data()));
		arr[v]='\n';
		write(obuf_file,arr.data(),arr.data()+v+1);
	}
	}
#endif
	{
	fast_io::timer t("u8obuf_file");
	fast_io::u8obuf_file obuf_file("u8obuf_filedb_sc.txt");
	for(std::size_t i(0);i!=N;++i)
		println(obuf_file,fast_io::scientific(vec[i]));
	}
	{
	fast_io::timer t("u8obuf_file int hint");
	fast_io::u8obuf_file obuf_file("u8obuf_filedb_hint_sc.txt");
	for(std::size_t i(0);i!=N;++i)
		println(obuf_file,fast_io::int_hint(vec[i]));
	}
	{
	fast_io::timer t("stream_view");
	std::ofstream fout("smvdb.txt",std::ofstream::binary);
	fast_io::filebuf_handle stm_v(fout);
	for(std::size_t i(0);i!=N;++i)
		println(stm_v,vec[i]);
	}
#ifdef _MSC_VER
	{
		fast_io::timer t("charconv");
		fast_io::obuf_file obuf_file("charconv.txt");
		std::array<char,100> arr;
		for(std::size_t i(0);i!=N;++i)
		{
			auto [p,ec]=std::to_chars(arr.data(),arr.data()+arr.size(),vec[i]);
			*p='\n';
			write(obuf_file,arr.data(),++p);
		}
	}
#endif
	{
	fast_io::timer t("obuf_file_mutex");
	fast_io::obuf_file_mutex obuf_file("obuf_file_mutexdb_sc.txt");
	for(std::size_t i(0);i!=N;++i)
		println(obuf_file,fast_io::scientific(vec[i]));
	}

}
catch(std::exception const& e)
{
	perrln(e);
	return 1;
}
