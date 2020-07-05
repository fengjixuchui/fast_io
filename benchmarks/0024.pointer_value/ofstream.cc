#include"../../include/fast_io_device.h"
#include"../timer.h"
#include<fstream>

int main()
{
	constexpr std::size_t N{100000000};
	char const* test_str ="Hello, world!";
	fast_io::timer tm("fstream");
	std::ofstream fout("fstream.txt",std::ofstream::binary|std::ofstream::out);
	for(std::size_t i{};i!=N;++i)
		fout<<test_str<<'\n';
}