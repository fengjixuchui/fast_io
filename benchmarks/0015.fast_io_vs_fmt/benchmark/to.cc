#include"../../timer.h"

int main()
{
	constexpr std::uint32_t N(10000000);
	std::size_t value{};
	{
	fast_io::timer t("fast_io::to<std::string>");
	for(std::uint32_t i{};i!=N;++i)
		value+=fast_io::to<std::string>(i).size();
	}
	println("value:",value);
}