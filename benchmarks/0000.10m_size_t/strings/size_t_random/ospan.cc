#include"../../../timer.h"
#include<random>

int main()
{
	constexpr std::size_t N(20000000);
	std::mt19937_64 eng;	//use deterministic seed
	std::vector<std::size_t> vec(N);
	for(auto & e : vec)
		e=eng();
	std::size_t value{};
	{
	fast_io::timer t("fast_io::ospan");
	for(std::size_t i{};i!=N;++i)
	{
		std::array<char,50> a;
		fast_io::ospan os(a);
		print(os,vec[i]);
		value+=std::string(a.data(),os.internal_pointer).size();
	}
	}
	println("value:",value);
}