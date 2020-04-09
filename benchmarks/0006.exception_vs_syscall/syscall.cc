#include"../timer.h"
#include<unistd.h>

int main()
{
	fast_io::timer tm("::close");
	for(std::size_t i{};i!=1000000;++i)
	{
		close(1);
	}
}