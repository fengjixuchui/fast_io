#include"../../timer.h"
#include"../../../include/fast_io.h"
#include"../../../include/fast_io_network.h"

int main()
{
try
{
	fast_io::timer tm("total");
	auto t0{std::chrono::high_resolution_clock::now()};
	fast_io::tcp_client hd(fast_io::ipv4{127,0,0,1},2000);
	perrln(u8"connection :\t",std::chrono::high_resolution_clock::now()-t0);
	for(std::size_t i{};i!=100;++i)
	{
		fast_io::timer tm1("some");
		print(hd,"Hello World\n");
		transmit_once(fast_io::out(),hd);
	}
}
catch(std::exception const& e)
{
	perrln(e);
	return 1;
}
}