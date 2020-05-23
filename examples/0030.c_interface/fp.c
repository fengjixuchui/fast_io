#include"../../include/fast_io_c_interface/fast_io_c_stdio_interface.h"
#include<time.h>
#include<stddef.h>
#include<stdlib.h>

int main()
{
	clock_t t=clock();
	FILE* fp=fopen("fp_test.txt","wb");
	if(fp==NULL)
	{
		perror("fopen failed()");
		abort();
	}
	for(size_t i=0;i!=10000000;++i)
		PRINTLN_UNLOCKED(fp,i);
	fclose(fp);
	PRINTLN(stdout,((double)(clock()-t))/CLOCKS_PER_SEC);
}