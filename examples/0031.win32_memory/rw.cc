#include"../../include/fast_io_device.h"
#include"../../include/fast_io.h"
#include"../../include/fast_io_driver/win32_memory.h"

int main(int argc,char** argv)
try
{
	if(argc<4)
	{
		perr("Usage:",std::string_view(*argv)," <window name> <base address> <output file>\n");
		return 1;
	}
	fast_io::win32_memory_file wfl(fast_io::win32_desired_access::process_all_access,
		false,fast_io::get_process_id_from_window_name(argv[1]),fast_io::to<std::uintptr_t>(argv[2]));
	
	auto mob{find_read_start(wfl)};
	auto mem_info{fast_io::win32_virtual_query(mob)};
	println("start at:",mob.base_addr,"\n",mem_info,"\nverify to transmit:",mem_info.region_size-(mob.base_addr-mem_info.base_address),"\nregion address end:",mem_info.base_address+mem_info.region_size);
	fast_io::onative_file onv{std::string_view(argv[3])};
	transmit(onv,mob,mem_info.region_size-(mob.base_addr-mem_info.base_address));
}
catch(std::exception const& e)
{
	perrln(e);
	return 1;
}