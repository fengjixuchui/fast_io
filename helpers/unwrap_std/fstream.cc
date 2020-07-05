#include<fstream>
#include<cstddef>
#include"../../helpers/timer.h"

int main()
{
	{
	fast_io::timer tm("ofstream");
	std::ofstream fout("fst.txt",std::ofstream::binary);
	auto& rdbuf(*fout.rdbuf());
	for(std::size_t i{};i!=10000000;++i)
	{
		fout<<i;
		rdbuf.sputc('\n');
	}
	}
	std::vector<std::size_t> vec(10000000);
	{
	fast_io::timer tm("input");
	std::ifstream fin("fst.txt",std::ifstream::binary);
	for(std::size_t i{};i!=10000000;++i)
	{
		fin>>vec[i];
	}
	}
	{
	fast_io::timer tm("verify");
	std::ofstream fout("fst_verify.txt",std::ofstream::binary);
	auto& rdbuf(*fout.rdbuf());
	for(std::size_t i{};i!=10000000;++i)
	{
		fout<<i;
		rdbuf.sputc('\n');
	}
	}
}