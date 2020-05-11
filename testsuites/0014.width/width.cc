
#include"../../include/fast_io.h"
#include"../../include/fast_io_device.h"
#include"../../include/fast_io_legacy.h"
#include"../timer.h"
int main()
{
	fast_io::timer tm("c_file_unlocked");
	fast_io::c_file_unlocked cf("c_file_unlocked.txt",fast_io::open_interface<fast_io::open_mode::out|fast_io::open_mode::binary>);
	for(std::size_t i{};i!=10000000;++i)
		println(cf,fast_io::right_width(20.214124124124,20,u8'0'));
}