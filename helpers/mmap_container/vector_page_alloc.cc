#include"../timer.h"
#include"../../include/fast_io_device.h"
#include<vector>
#ifdef FAST_IO_PAGE_ALLOC
#include"page_alloc.h"
#endif

int main()
{
	constexpr std::size_t N{100};
	constexpr std::size_t M{1000000};

	fast_io::obuf_file obf("vec.txt");
	fast_io::timer tm("std::vector");

	for(std::size_t i{};i!=N;++i)
	{
		std::vector<std::size_t> vec;
//		vec.reserve(M);
		for(std::size_t j{};j!=M;++j)
			vec.emplace_back(j);

		println(obf,fast_io::unsigned_view(vec.data()));
	}
}