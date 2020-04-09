#include"../timer.h"
#include<unistd.h>

int main()
{
	fast_io::timer tm("runtime_error");
	for(std::size_t i{};i!=1000000;++i)
	{
		try
		{
			throw std::runtime_error("rte");
		}
		catch(std::exception const&e)
		{

		}
	}
}