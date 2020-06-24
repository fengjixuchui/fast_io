#include"../../include/fast_io.h"

int main()
try
{
	double d;
	scan(d);
	println(d);
}
catch(std::exception const& e)
{
	perrln(e);
	return 1;
}