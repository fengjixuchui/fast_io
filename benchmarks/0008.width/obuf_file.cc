
#include"../../include/fast_io.h"
#include"../../include/fast_io_device.h"
#include"../../include/fast_io_legacy.h"
#include"../timer.h"
int main()
{
	fast_io::timer tm("obuf_file");
	fast_io::obuf_file obf("obuf_file.txt",fast_io::open_interface<fast_io::open_mode::out|fast_io::open_mode::binary>);
	for(std::size_t i{};i!=10000000;++i)
		println(obf,fast_io::right_width(i,20,u8'0'));
}