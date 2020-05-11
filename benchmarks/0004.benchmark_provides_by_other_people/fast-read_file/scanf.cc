#include <ctime>
#include <cstdio>
const int MAXN = 10000000;

int numbers[MAXN];

void scanf_read()
{
	freopen("data.txt","r",stdin);
	for (int i=0;i<MAXN;i++)
		scanf("%d",&numbers[i]);
}

int main()
{
	int start = clock();
	//DO SOMETHING
	scanf_read();
	printf("%.3lf\n",double(clock()-start)/CLOCKS_PER_SEC);
}