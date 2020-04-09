#include"../../../timer.h"
#include<random>
#include<fmt/format.h>

int main()
{
	constexpr std::size_t N(20000000);
	std::mt19937_64 eng;	//use deterministic seed
	std::vector<std::size_t> vec(N);
	for(auto & e : vec)
		e=eng();
	std::size_t value{};
	{
	fast_io::timer t("fmt::format_int");
	for(std::size_t i{};i!=N;++i)
		value+=fmt::format_int(vec[i]).str().size();
	}
	println("value:",value);
}