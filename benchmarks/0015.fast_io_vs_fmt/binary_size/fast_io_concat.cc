#include"../../../include/fast_io.h"

int main()
{
	std::size_t value;
	scan(value);
	print(fast_io::concat(value).size());
}