#include"../../include/fast_io.h"
#include"../../include/fast_io_legacy.h"
#ifdef _MSC_VER
#include<charconv>
#endif

int main()
{
	double d(23535782139572189357.0);
	print(u8"fast_io:",d,u8"\nmicrosoft STL charconv:");
	char buffer[100];
	auto [p,ec]=std::to_chars(buffer,buffer+100,d);
	*p=u8'\n';
	write(fast_io::c_stdout(),buffer,++p);
	put(u8'\n');
}
//cl -EHsc -Ox fp.cc /std:c++latest /experimental:concepts