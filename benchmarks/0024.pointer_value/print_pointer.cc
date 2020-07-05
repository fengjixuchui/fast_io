#include"../../include/fast_io_device.h"
#include"../timer.h"

int main()
{
	constexpr std::size_t N{100000000};
	char const* test_str ="Hello, world!";
	fast_io::timer tm("println pointer");
	fast_io::obuf_file obf("fast_io_println_pointer.txt");
	for(std::size_t i{};i!=N;++i)
		println(obf,test_str);	//THIS IS NOT PRINT STRING
}