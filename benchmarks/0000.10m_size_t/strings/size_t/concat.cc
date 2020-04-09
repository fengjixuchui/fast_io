#include"../../../timer.h"

int main()
{
	constexpr std::size_t N(200000000);
	std::size_t value{};
	{
	fast_io::timer t("fast_io::concat");
	for(std::size_t i{};i!=N;++i)
		value+=fast_io::concat(i).size();
	}
	println("value:",value);
}