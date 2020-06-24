#include"../../timer.h"
#include"../../../include/fast_io.h"
#include"../../../include/fast_io_device.h"
#include"../../../include/fast_io_network.h"

int main()
try
{
	signal(SIGCHLD, SIG_IGN);
	fast_io::timer tm("total");
	fast_io::onative_file log("proxy_log.txt");
	for(fast_io::tcp_server hd(2000);;)
	{
		fast_io::acceptor accept(hd);
		fast_io::process proc("./proxy_child_process",{},{.in=accept,.out=accept,.err=log});
	}
}
catch(std::exception const& e)
{
	perrln(e);
	return 1;
}