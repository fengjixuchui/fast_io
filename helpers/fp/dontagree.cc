#include<random>
#include<iostream>
#include<cstring>

int main()
{
	std::mt19937_64 eng;
	std::uniform_real_distribution dis(-10000.0f,10000.0f);
	float v{};
	for(std::size_t i(0);i!=36;++i)
		v=dis(eng);
	static_assert(sizeof(float)==sizeof(std::uint32_t));
	std::uint32_t puned;
	memcpy(std::addressof(puned),std::addressof(v),sizeof(std::uint32_t));
	std::cout<<puned<<'\n';
}