#include"../../../timer.h"
#include<fmt/format.h>

int main()
{
	constexpr std::size_t N(200000000);
	std::size_t value{};
	{
	fast_io::timer t("fmt::format_int");
	for(std::size_t i{};i!=N;++i)
		value+=fmt::format_int(i).str().size();
	}
	println("value:",value);
}