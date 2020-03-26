#include"../../include/fast_io.h"
#include"../../include/fast_io_legacy.h"

int main()
{
	FILE* fp=fopen("he.txt","wb");
	fast_io::c_io_observer_unlocked ciob(fp);
	print(ciob,"Let's print something to get buffer size");
	println(u8"BUFSIZ macro:\t",BUFSIZ,u8"\nreal buffer_size:\t",obuffer_end(ciob)-obuffer_begin(ciob));
}

/*
D:\hg\w4\f8\fast_io\helpers\bufsiz>g++ -o bufsiz bufsiz.cc -Ofast -std=c++2a -s

D:\hg\w4\f8\fast_io\helpers\bufsiz>bufsiz
BUFSIZ macro:   512
real buffer_size:       4096

BUFSIZ macro is WRONG!
*/