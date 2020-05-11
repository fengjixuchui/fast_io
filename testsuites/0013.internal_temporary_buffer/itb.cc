#include"../../include/fast_io.h"

int main()
{
	fast_io::internal_temporary_buffer<char> buffer;
	for(std::size_t i{};i!=10000;++i)
	print(buffer,"hello world\n");
	write(fast_io::out,buffer.beg_ptr,buffer.end_ptr);
	print(buffer.capacity_ptr-buffer.beg_ptr);
//	for()
}