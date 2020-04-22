#include"../../include/fast_io_device.h"
#include"../../include/fast_io_in.h"

int main()
{
	constexpr std::size_t N{100000};
	constexpr std::size_t M{100};
	for(std::size_t i{};i!=2;++i)
	{
	auto ptr{new int};
	delete ptr;
	}
}