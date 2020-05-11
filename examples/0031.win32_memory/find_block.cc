#include"../../include/fast_io_device.h"
#include"../../include/fast_io.h"
#include"../../include/fast_io_driver/win32_memory.h"

int main(int argc,char** argv)
try
{
	if(argc<4)
	{
		print(fast_io::err,"Usage:",*argv," <window name> <base address> <output file>\n");
		return 1;
	}
	fast_io::win32_memory_file wfl(fast_io::win32_desired_access::process_all_access,
		false,fast_io::get_process_id_from_window_name(argv[1]),fast_io::to<std::uintptr_t>(argv[2]));
	auto wmf{find_usable_region(wfl)};

	auto mem_info{fast_io::win32_virtual_query(wmf)};
	wmf.base_address()=mem_info.base_address;
	println(mem_info);

//	fast_io::win32_virtual_protect_guard guard(wmf,mem_info.region_size,fast_io::win32_memory_page_protect::readwrite);

	fast_io::onative_file onv{std::string_view(argv[3])};
	transmit(onv,wmf,mem_info.region_size);
}
catch(std::exception const& e)
{
	println(fast_io::err,e);
	return 1;
}