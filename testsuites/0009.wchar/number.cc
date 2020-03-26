#include<cstdio>
#include"../../include/fast_io_device.h"
#include"../../include/fast_io.h"

int main()
{
	fast_io::basic_obuf<fast_io::basic_posix_file<wchar_t>> baof("defaultone.txt","wb");
	for(std::size_t i{};i!=10000000;++i)
		println(baof,i);
}