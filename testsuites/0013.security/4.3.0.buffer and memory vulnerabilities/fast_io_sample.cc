#include"../../../include/fast_io_in.h"
int main(){
	unsigned size;
	scan(fast_io::bound(size,0,1000)); // input func : scanf, input stream: stdin.
	//we restrict the size to be [0,1000]
	void * buf = malloc(size);
}