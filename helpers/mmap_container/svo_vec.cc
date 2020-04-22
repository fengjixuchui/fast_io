#include"../timer.h"
#include"svo_vector.h"
#include<vector>

int main()
{
	constexpr std::size_t N{5000000};
	constexpr std::size_t M{50};
	{
		std::size_t sum{};
		fast_io::timer tm("std::vector");
		for(std::size_t i{};i!=N;++i)
		{
		std::vector<std::size_t> vec(M);
		for(auto & e : vec)
		{
			sum+=e;
			e=sum;
		}
		}
		println("sum:",sum);
	}

	{
		std::size_t sum{};
		fast_io::timer tm("svo_vector");
		for(std::size_t i{};i!=N;++i)
		{
		fast_io::svo_vector<std::size_t,2048> vec(M);
		for(auto & e : vec)
		{
			sum+=e;
			e=sum;
		}
		}
		println("sum:",sum);
	}
	{
		std::size_t sum{};
		fast_io::timer tm("std::vector");
		for(std::size_t i{};i!=N;++i)
		{
		std::vector<std::size_t> vec(M);
		for(auto & e : vec)
		{
			sum+=e;
			e=sum;
		}
		}
		println("sum:",sum);
	}
}