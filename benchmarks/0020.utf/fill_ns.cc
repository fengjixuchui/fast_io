#include"../../include/fast_io.h"
#include"../../include/fast_io_device.h"
#include"../../include/fast_io_legacy.h"

int main()
{
	fast_io::u8obuf_file utf8_file_out("u8obuf_file.txt");
	for(std::size_t i{};i!=10000000;++i)
		print(utf8_file_out,u8"我");
}