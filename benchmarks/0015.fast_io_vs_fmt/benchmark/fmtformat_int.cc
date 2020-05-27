#include"../../timer.h"
#include<fmt/format.h>

int main()
{
	constexpr std::uint32_t N(10000000);
	std::size_t value{};
	{
	fast_io::timer t("fmt::format_int");
	for(std::uint32_t i{};i!=N;++i)
		value+=fmt::format_int(i).str().size();
	}
	println("value:",value);
}