#include"../timer.h"
#include<fstream>
#include"../../include/fast_io.h"
#include"../../include/fast_io_device.h"
#include"../../include/fast_io_legacy.h"

int main()
{
	fast_io::timer t("filebuf_io_observer");
	std::ofstream fout("filebuf_io_observer.txt",std::ofstream::binary);
	fast_io::filebuf_io_observer fob{fout.rdbuf()};
	for(std::size_t i{};i!=10000000;++i)
		println(fob,fast_io::right_width(i,20,u8'0'));
}