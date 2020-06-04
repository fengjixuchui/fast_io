#include"../../../include/fast_io.h"
#include"../../../include/fast_io_legacy.h"
#include"../../timer.h"

int main()
{
	constexpr std::size_t N{100000000};
	{
	fast_io::timer tm("filebuf_file");
	fast_io::filebuf_file cfl("filebuf_file.txt","wb");
	constexpr std::string_view view("Hello World\n");
	for(std::size_t i{};i!=N;++i)
		print(cfl,view);
	}
}