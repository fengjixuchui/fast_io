#include<stdio.h>
#include"../../include/fast_io.h"
#include"../../include/fast_io_device.h"
#include"../../include/fast_io_legacy.h"

int main()
{
	fast_io::c_file_unlocked cfu("w.txt","wb");
#ifndef NDEBUG

	debug_println(fast_io::unsigned_view(cfu.fp->_base),"\t",fast_io::unsigned_view(cfu.fp->_ptr),"\t",cfu.fp->_cnt,"\t",cfu.fp->_bufsiz);
#endif	
	for(std::size_t i{};i!=1250;++i)
	{
		println(cfu,i);
	}

}