#include"../../include/fast_io.h"
#include"../../include/fast_io_device.h"
#include<thread>

inline fast_io::task io_task(fast_io::win32_io_observer iocp)
{
	fast_io::win32_file file(fast_io::io_async,iocp,"w.txt",fast_io::open_mode::out|fast_io::open_mode::binary|fast_io::open_mode::no_block);
	co_await fast_io::async_println(file,"Hello World ",5," ",6," ",8," ",9," ",4.2);
}

int main()
{
	fast_io::win32_file iocp(fast_io::io_async);
	std::vector<std::jthread> pools;
	pools.reserve(std::thread::hardware_concurrency());
	pools.emplace_back(fast_io::win32::single_thread_io_async_scheduling,iocp);
	io_task(iocp);
}