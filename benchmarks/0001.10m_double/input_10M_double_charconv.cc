//Please run output_10M_double before this

#include"../timer.h"
#include<fstream>
#include"../../include/fast_io.h"
#include"../../include/fast_io_device.h"
#include<exception>
#include<memory>
#include<cstdio>
#include<vector>
#include<charconv>

int main()
try
{
	std::size_t constexpr N(10000000);
	std::vector<double> v(N);
	
	{
	fast_io::timer t("charconv");
	fast_io::ibuf_file ibuf("obuf_filedb.txt");
	std::string str;
	str.reserve(30);
	for(std::size_t i(0);i!=N;++i)
	{
		scan(ibuf,str);
		auto [p,ec]=std::from_chars(str.data(),str.data()+str.size(),v[i]);
	}
	}
}
catch(std::exception const& e)
{
	perrln(e);
	return 1;
}