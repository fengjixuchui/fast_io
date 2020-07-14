#include"../../include/fast_io.h"
#include"../../include/fast_io_device.h"
#include"../../include/fast_io_driver/liburing.h"
#include<coroutine>
#include"../../include/fast_io_hosted/async_coro.h"

inline fast_io::task io_task(fast_io::io_uring_observer ior)
{
	fast_io::onative_file nv("test.txt");
	std::ptrdiff_t offset{};
	for(std::size_t i{};i!=1000;++i)
		offset+=co_await fast_io::async_println(ior,offset,nv,"Hello World\t",i,"\tsdg\t",7.8);
}

int main()
{
	using namespace std::chrono_literals;
	fast_io::io_uring ior(fast_io::io_async);
	io_task(ior);
	for(;;fast_io::linux::io_async_wait_timeout(ior,1ms));
}
