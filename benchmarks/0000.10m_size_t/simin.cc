#include"../timer.h"
#include"../../include/fast_io_device.h"
#include"../../include/fast_io_legacy.h"
#include"../../include/fast_io_third_party.h"
#include<charconv>

int main()
{
	std::size_t constexpr N(10000000);
	std::vector<std::size_t> v(N);
	{
	fast_io::timer t("ibuf");
	fast_io::ibuf_file ibuf_file("native.txt");
	for(std::size_t i(0);i!=N;++i)
	{
		scan(ibuf_file,v[i]);
	}
	}
	{
	fast_io::timer t("ibuf discard");
	fast_io::ibuf_file ibuf_file("native.txt");
	for(std::size_t i(0);i!=N;++i)
	{
		scan(ibuf_file,fast_io::no_decoration(v[i]));
		discard(ibuf_file);
	}
	}
	std::string str;
	str.reserve(30);
	{
	fast_io::timer t("ibuf");
	fast_io::ibuf_file ibuf_file("native.txt");
	for(std::size_t i(0);i!=N;++i)
	{
		scan(ibuf_file,str);
	}
	}
	std::vector<std::string> strs;
	strs.reserve(N);
//	str.reserve(30);
	{
	fast_io::timer t("ibuf");
	fast_io::ibuf_file ibuf_file("native.txt");
	for(std::size_t i(0);i!=N;++i)
	{
		std::string str;
		scan(ibuf_file,str);
		strs.emplace_back(std::move(str));
	}
	}
	{
		fast_io::timer t("strv");
		for(std::size_t i(0);i!=N;++i)
		{
			fast_io::istring_view isv(strs[i]);
			scan(isv,v[i]);
		}
	}
	{
		fast_io::timer t("charconv");
		for(std::size_t i(0);i!=N;++i)
		{
			std::string_view str(strs[i]);
			auto [p,ec]=std::from_chars(str.data(),str.data()+str.size(),v[i]);
		}
	}
	{
		fast_io::timer t("no_decoration");
		for(std::size_t i(0);i!=N;++i)
		{
			fast_io::istring_view isv(strs[i]);
			scan(isv,fast_io::no_decoration(v[i]));
		}
	}
}