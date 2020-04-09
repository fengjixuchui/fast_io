#include"../../../include/fast_io.h"
#include"../../../include/fast_io_device.h"
#include"../../../include/fast_io_network.h"
#include<csignal>

int main()
{
	signal(SIGCHLD, SIG_IGN);
	fast_io::onative_file log("log.txt");
	for(fast_io::tcp_server hd(2000);;)
	{
		fast_io::acceptor accept(hd);
		fast_io::process proc("./server_child_process",{},{.in=accept,.out=accept,.err=log});
		println(log,u8"connected from: ",accept.info());
	}
}