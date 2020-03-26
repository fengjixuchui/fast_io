#include"../timer.h"
#include"../../include/fast_io_device.h"
#include"../../include/fast_io_legacy.h"
#include"../../include/fast_io_third_party.h"

template<fast_io::open_mode om=fast_io::open_mode::out|fast_io::open_mode::binary,std::size_t N=10000000>
inline void test(std::string_view text)
{
	fast_io::timer tm(text);
	fast_io::c_file_unlocked file(text,fast_io::open_interface<om>);
	for(std::size_t i{};i!=N;++i)
		println(file,i);
}

int main()
{
	test("cio_unlocked.txt");
}