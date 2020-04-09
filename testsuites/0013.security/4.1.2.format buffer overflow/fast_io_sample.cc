#include"../../../include/fast_io.h"
int main()
{
	std::string str;
	fast_io::ostring_ref ostrref(str);
	print(ostrref,"AAAAAAAAAAAAA");	//Not possible to be a buffer overflow
}