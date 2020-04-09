#include"../../../timer.h"

int main()
{
	constexpr std::size_t N(200000000);
	std::size_t value{};
	{
	fast_io::timer t("fast_io::ospan");
	for(std::size_t i{};i!=N;++i)
	{
		std::array<char,50> a;
		fast_io::ospan os(a);
		print(os,i);
		value+=std::string(a.data(),os.internal_pointer).size();
	}
	}
	println("value:",value);
}