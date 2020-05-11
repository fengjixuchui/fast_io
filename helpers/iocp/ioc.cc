#include"../../include/fast_io.h"
#include"../../include/fast_io_device.h"

int main()
{
	fast_io::native_file iocp(fast_io::io_async);
	fast_io::native_file onv(fast_io::io_async,iocp,"ioc.txt",fast_io::open_mode::out|fast_io::open_mode::binary|fast_io::open_mode::no_block);
	std::string_view view("hello world");
	async_write(onv,view.data(),view.data()+view.size());
	cancel(onv);
}