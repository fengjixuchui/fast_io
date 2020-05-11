#include <ctime>
#include <cstdio>
#ifdef MINGW32
#include <io.h>
#else
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#endif

const int MAXN = 10000000;
const int MAXS = 60*1024*1024;

int numbers[MAXN];
char buf[MAXS];

void analyse(char *buf,int len = MAXS)
{
	int i;
	numbers[i=0]=0;
	for (char *p=buf;*p && p-buf<len;p++)
		if (*p == ' ')
			numbers[++i]=0;
		else
			numbers[i] = numbers[i] * 10 + *p - '0';
}

void mmap_analyse()
{
    int fd = open("data.txt",O_RDONLY);
    int len = lseek(fd,0,SEEK_END);
    char *mbuf = (char *) mmap(NULL,len,PROT_READ,MAP_PRIVATE,fd,0);   
    analyse(mbuf,len);
}

int main()
{
	int start = clock();
	//DO SOMETHING
	mmap_analyse();
	printf("%.3lf\n",double(clock()-start)/CLOCKS_PER_SEC);
}