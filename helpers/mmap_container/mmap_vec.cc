
#include"../timer.h"
#include"mmap_svector.h"
#include<vector>

int main()
{
	constexpr std::size_t N{100};
	constexpr std::size_t M{10485760};
	{
		std::size_t sum{};
		{
		fast_io::timer tm("mmap_svector");
		for(std::size_t i{};i!=N;++i)
		{
		fast_io::mmap_svector<std::size_t,65536> vec(M);
		for(auto const & e : vec)
			sum+=e;
		}
		}
		println("sum:",sum);
	}
	{
		std::size_t sum{};
		{
		fast_io::timer tm("std::vector");
		for(std::size_t i{};i!=N;++i)
		{
		std::vector<std::size_t> vec(M);
		for(auto const & e : vec)
			sum+=e;
		}
		}
		println("sum:",sum);
	}
}