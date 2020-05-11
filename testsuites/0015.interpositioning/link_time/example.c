#include <stdio.h>
#include <malloc.h>

int main()
{
	printf("Hello World\n");
}

/*


gcc -c example.c -Ofast
g++ -c stdio_tracker.cc -Ofast -std=c++20
g++ -o example example.o stdio_tracker.o -Wl,--wrap,vfprintf -Wl,--wrap,fprintf -Wl,--wrap,vsprintf -Wl,--wrap,sprintf -Wl,--wrap,vsnprintf -Wl,--wrap,vprintf -Wl,--wrap,vscanf -Wl,--wrap,scanf -Wl,--wrap,vfscanf -Wl,--wrap,fscanf -Wl,--wrap,sscanf -Wl,--wrap,vsscanf -Wl,--wrap,printf -Wl,--wrap,vprintf -Wl,--wrap,puts -Wl,--wrap,fputs -s

*/