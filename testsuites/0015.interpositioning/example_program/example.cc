#include <stdio.h>
#include <malloc.h>
#include <new>
int main()
{
	void *ptr = malloc(32);
	int *p = new (ptr) int;
	free(ptr);

}