#include"../../include/fast_io_device.h"
#include"../../include/fast_io.h"
#include"../../include/fast_io_driver/win32_memory.h"

int main(int argc,char** argv)
try
{
	if(argc<4)
	{
		perr("Usage:",std::string_view(*argv)," <process id> <base address> <output file path>\n");
		return 1;
	}
	fast_io::win32_memory_file wmf(fast_io::win32_desired_access::process_all_access,
		false,fast_io::to<std::uint32_t>(argv[1]),fast_io::to<std::uintptr_t>(argv[2]));
	auto mem_info{fast_io::win32_virtual_query(wmf)};
	wmf.base_address()=mem_info.base_address;
	println(mem_info);
	fast_io::onative_file onv(argv[3]);
	transmit(onv,wmf,mem_info.region_size);
}
catch(std::exception const& e)
{
	perrln(e);
	return 1;
}