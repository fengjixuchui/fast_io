#include"../../../include/fast_io.h"
#include"../../timer.h"

int main()
{
	constexpr std::size_t N{100000000};
	fast_io::timer tm("print");
	std::string view("Hello World\n");
	for(std::size_t i{};i!=N;++i)
		print(view);
}