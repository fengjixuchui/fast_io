#include"../../../include/fast_io.h"
#include"../../../include/fast_io_device.h"
#include"../../timer.h"

int main()
{
	constexpr std::size_t N{100000000};
	fast_io::timer tm("obuf_file mutex");
	std::string view("Hello World\n");
	fast_io::obuf_file_mutex obf("obuf_file_mutex.txt");
	for(std::size_t i{};i!=N;++i)
		print(obf,view);
}