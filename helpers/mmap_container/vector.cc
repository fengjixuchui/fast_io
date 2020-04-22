#include"../timer.h"
#include<vector>

int main()
{
	constexpr std::size_t N{100};
	constexpr std::size_t M{1000000};

	
	std::size_t sum{};
	fast_io::timer tm("std::vector");
	for(std::size_t i{};i!=N;++i)
	{
		std::vector<std::size_t> vec(M,1);
		for(auto & e : vec)
		{
			sum+=e;
			e+=sum;
		}
	}
	println("sum:",sum);
}