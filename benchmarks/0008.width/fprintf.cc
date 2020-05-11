#include"../../include/fast_io.h"
#include"../../include/fast_io_device.h"
#include"../../include/fast_io_legacy.h"
#include"../timer.h"
int main()
{
	fast_io::timer tm("fprintf");
	fast_io::c_file cf("fprintf.txt",fast_io::open_interface<fast_io::open_mode::out|fast_io::open_mode::binary>);
	for(std::size_t i{};i!=10000000;++i)
		fprintf(cf.native_handle(),"%0*zu\n",20,i);
}