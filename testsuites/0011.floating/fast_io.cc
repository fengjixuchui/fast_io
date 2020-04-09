#include"../../include/fast_io.h"

int main()
try
{
	throw fast_io::to<std::runtime_error>("asfasf");
}
catch(std::exception const& e)
{
	println(fast_io::err,e);
}