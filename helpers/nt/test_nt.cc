#include<exception>
#include<cstdint>
#include"../../include/fast_io.h"

int main()
try
{
	throw fast_io::nt_error(2);
}
/*
catch(fast_io::nt_error const& e)
{
	perrln(e);
	return 1;
}
*/
catch(std::exception const& e)
{
	perrln(e);
	return 1;
}