#include"../../include/fast_io.h"
#include"../../include/fast_io_network.h"

int main()
{
	fast_io::tcp_client hd(fast_io::ipv4{127,0,0,1},2000);
	transmit(fast_io::out(),hd);
}