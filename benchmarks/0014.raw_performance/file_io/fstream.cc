#include"../../../include/fast_io.h"
#include"../../timer.h"
#include<fstream>

int main()
{
	constexpr std::size_t N{100000000};
	fast_io::timer tm("fstream");
	std::string view("Hello World\n");
	std::ofstream fout("fstream.txt",std::ofstream::binary);
	auto& rdbuf(*fout.rdbuf());
	for(std::size_t i{};i!=N;++i)
		rdbuf.sputn(view.data(),view.size());
}