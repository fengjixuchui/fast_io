#include"../../include/fast_io_device.h"
#include"../timer.h"

int main()
{
	constexpr std::size_t N{100000000};
	char const* test_str ="Hello, world!";
	fast_io::timer tm("fprintf");
	fast_io::c_file obf("fprintf.txt","wb");
	for(std::size_t i{};i!=N;++i)
		fprintf(obf.native_handle(),"%s\n",test_str);
}