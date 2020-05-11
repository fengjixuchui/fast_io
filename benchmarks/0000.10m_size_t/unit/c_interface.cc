#include"../../timer.h"
#include"../../../include/fast_io.h"
#include"../../../include/fast_io_device.h"
#include"../../../include/fast_io_legacy.h"
#include"../../../include/fast_io_c_interface.h"

int main()
{
	constexpr std::size_t N(10000000);
	{
	fast_io::timer t("output");
	fast_io::posix_file pf("c_interface_file.txt",fast_io::open_interface<fast_io::open_mode::out|fast_io::open_mode::binary>);
	fast_io::c_interface_file_buffered obf;
	cxx_fast_io_posix_fd_open(std::addressof(obf.native_handle()),pf.native_handle(),true,true);
	for(std::size_t i{};i!=N;++i)
		cxx_fast_io_bufferred_println_size_t(obf.native_handle(),i);
	}
	std::vector<std::size_t> vec(N);
	{
	fast_io::timer t("input");
	fast_io::posix_file pf("c_interface_file.txt",fast_io::open_interface<fast_io::open_mode::in|fast_io::open_mode::binary>);
	fast_io::c_interface_file_buffered ibf;
	cxx_fast_io_posix_fd_open(std::addressof(ibf.native_handle()),pf.native_handle(),true,true);
	for(std::size_t i{};i!=N;++i)
		cxx_fast_io_bufferred_scan_size_t(ibf.native_handle(),vec.data()+i);
	}
}