#include"../../include/fast_io.h"

int main()
{
	fast_io::black_hole<char> black_hole;
	transmit(black_hole,fast_io::in());
}