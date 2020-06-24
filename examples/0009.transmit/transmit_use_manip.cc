#include"../../include/fast_io.h"

int main()
{
	std::size_t bytes{};
	print(fast_io::transmission(bytes,fast_io::in()));
	println("Transmitted: ",bytes, " bytes");
}
