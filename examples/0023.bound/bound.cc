#include"../../include/fast_io.h"
#include"../../include/fast_io_in.h"

int main()
{
	std::size_t size;
	scan(fast_io::bound(size,0,10000));
	println(size);
}