//Please run output_10M_size_t before this

#include"../timer.h"
#include<fstream>
#include"../../include/fast_io.h"
#include"../../include/fast_io_device.h"
#include"../../include/fast_io_legacy.h"
//#include"../../include/fast_io_crypto.h"
#include<exception>
#include<memory>
#include<cstdio>
#include<vector>

int main()
try
{
	std::size_t constexpr N(10000000);
	std::vector<std::size_t> v(N);
	{
	fast_io::timer t("std::FILE*");
	std::unique_ptr<std::FILE,decltype(fclose)*> fp(std::fopen("filebuf_io_observer.txt","rb"),fclose);
	for(std::size_t i(0);i!=N;++i)
		auto const ret(fscanf(fp.get(),"%zu",v.data()+i));
	}
	{
	fast_io::timer t("std::ifstream");
	std::ifstream fin("filebuf_io_observer.txt",std::ifstream::binary);
	for(std::size_t i(0);i!=N;++i)
		fin>>v[i];
	}
	
	{
	fast_io::timer t("ibuf");
	fast_io::ibuf_file ibuf_file("filebuf_io_observer.txt");
	for(std::size_t i(0);i!=N;++i)
		scan(ibuf_file,v[i]);
	}
/*	{
	fast_io::timer t("cful");
	fast_io::c_file_unlocked cfu("filebuf_io_observer.txt",fast_io::open_interface<fast_io::open_mode::binary|fast_io::open_mode::in>);
	for(std::size_t i(0);i!=N;++i)
		scan(cfu,v[i]);
	}*/

	{
	fast_io::timer t("ibuf_mutex");
	fast_io::ibuf_file_mutex ibuf_file("filebuf_io_observer.txt");
	for(std::size_t i(0);i!=N;++i)
		scan(ibuf_file,v[i]);
	}

	{
	fast_io::timer t("filebuf");
	std::ifstream fin("filebuf_io_observer.txt",std::ifstream::binary);
	fast_io::filebuf_io_observer fiob(fin.rdbuf());
	for(std::size_t i(0);i!=N;++i)
		scan(fiob,v[i]);
	}
}
catch(std::exception const& e)
{
	println(fast_io::err,e);
	return 1;
}