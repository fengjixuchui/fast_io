#include <ctime>
#include <cstdio>
#include "../../../include/fast_io_device.h"
const int MAXN = 10000000;

int numbers[MAXN];

void fast_io_scan()
{
	fast_io::ibuf_file ibf("data.txt");
	for (int i=0;i<MAXN;i++)
		scan(ibf,numbers[i]);
}

int main()
{
	int start = clock();
	//DO SOMETHING
	fast_io_scan();
	printf("%.3lf\n",double(clock()-start)/CLOCKS_PER_SEC);
}