#include<stdio.h>
#include<stdlib.h>

int main()
{
	if(printf("Hello World\n")<0)
		abort();
}

// gcc -o hw hw.c -flto -Ofast -DNDEBUG -s
// no static linking
//binary size: 15kb