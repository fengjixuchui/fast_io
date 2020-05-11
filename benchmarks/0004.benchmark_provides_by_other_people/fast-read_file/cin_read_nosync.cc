#include <ctime>
#include <cstdio>
#include <iostream>
const int MAXN = 10000000;

int numbers[MAXN];

void cin_read_nosync()
{
	freopen("data.txt","r",stdin);
	std::ios::sync_with_stdio(false);
	for (int i=0;i<MAXN;i++)
		std::cin >> numbers[i];
}

int main()
{
	int start = clock();
	//DO SOMETHING
	cin_read_nosync();
	printf("%.3lf\n",double(clock()-start)/CLOCKS_PER_SEC);
}