#include<fstream>
#include<cstddef>
#include"../../helpers/timer.h"

int main()
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