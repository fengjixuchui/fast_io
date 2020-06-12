#include"../../include/fast_io.h"

int main()
{
	for(std::size_t val{};scan<true>(val);println(val));
}
//this won't throw exceptions since fast_io understands how stdio.h internal works