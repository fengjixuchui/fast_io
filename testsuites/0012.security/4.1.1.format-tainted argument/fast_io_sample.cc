#include"../../../include/fast_io.h"
#include"../../../include/fast_io_in.h"
int main()
{
	std::string str;
	scan(str);	//No need assign buffer size. Avoid potential buffer overflow
	print(str);	//Not possible to control by external source
}