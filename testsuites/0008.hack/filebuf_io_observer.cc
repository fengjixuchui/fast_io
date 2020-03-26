#include"../timer.h"
#include<fstream>
#include"../../include/fast_io.h"
#include"../../include/fast_io_device.h"
//#include"../../include/fast_io_crypto.h"
#include"../../include/fast_io_legacy.h"

int main()
{
	constexpr std::size_t N(10000000);
	{
	fast_io::timer t("output");
	std::ofstream fout("filebuf_io_observer.txt",std::ofstream::binary);
	fast_io::filebuf_io_observer fob{fout.rdbuf()};
	for(std::size_t i{};i!=N;++i)
		println(fob,i);
	}

	{
	fast_io::timer t("input");
	std::ifstream fin("filebuf_io_observer.txt",std::ifstream::binary);
	fast_io::filebuf_io_observer fob{fin.rdbuf()};
	std::ofstream fout("filebuf_io_observer_verify.txt",std::ofstream::binary);
	fast_io::filebuf_io_observer fob_out{fout.rdbuf()};
	for(std::size_t i{};i!=N;++i)
	{
		std::size_t value;
		scan(fob,value);
		println(fob_out,value);
	}
	}
}