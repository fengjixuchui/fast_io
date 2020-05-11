#include"../../include/fast_io_c_interface.h"

int main()
{
	void* device;
	int err=cxx_fast_io_c_fp_open(&device,stdout,true,false);
	if(err)
	{
		if(fprintf(stderr,"cxx_fast_io_c_fp_open() failed:%s\n",strerror(err))<0)
			abort();
		abort();
	}
	if(err = cxx_fast_io_print_c_str(device,"Hello World\n"))
	{
		if(fprintf(stderr,"cxx_fast_io_print_c_str() failed:%s\n",strerror(err))<0)
			abort();
		abort();
	}
	cxx_fast_io_release(device,false);
}