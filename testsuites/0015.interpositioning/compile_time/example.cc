#include <stdio.h>
#include <malloc.h>
#include <new>
#include "../../../include/fast_io.h"

#ifdef COMPILETIME
/* malloc wrapper function */
void *mymalloc(size_t size)
{
void *ptr = malloc(size);
debug_println("malloc(",size,")=",fast_io::unsigned_view(ptr));
return ptr;
}
/* free wrapper function */
void myfree(void *ptr)
{
free(ptr);
debug_print("free(",fast_io::unsigned_view(ptr),")");
}
#endif
#define malloc(size) mymalloc(size)
#define free(ptr) myfree(ptr)
void *mymalloc(size_t size);
void myfree(void *ptr);

int main()
{
	void *ptr = malloc(32);
	int *p = new (ptr) int;
	free(ptr);

}