#include"../../include/fast_io.h"

/*
I wasn't thought to add shit like this. However, fmt library author keeps using stupid benchmarks to claim he is better than every else.
This print_reserver will defeat every excuse he has.
*/

int main()
{
	int d(45);
	auto p{fast_io::print_reserve(d)};
	println(fast_io::chvw(p.c_str()));
}