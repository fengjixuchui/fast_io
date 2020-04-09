#include"../../../include/fast_io.h"
#include"../../../include/fast_io_in.h"
#include"../../../include/fast_io_network.h"
#include<thread>
#include<csignal>

int main()
{
	fast_io::tcp_client dest(fast_io::ipv4{127,0,0,1},2001);
	std::jthread t0([&dest]{
		transmit(fast_io::out,dest);
	});
	transmit(dest,fast_io::in);
}