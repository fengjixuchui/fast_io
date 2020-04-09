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
	fast_io::timer t("ibuf");
	fast_io::c_file_unlocked cfu("cfilestar.txt",fast_io::open_interface<fast_io::open_mode::in>);
	for(std::size_t i(0);i!=N;++i)
	{
		scan(cfu,v[i]);
	}
	}
}
catch(std::exception const& e)
{
	println(fast_io::err,e);
	return 1;
}