#include"../../include/fast_io.h"
#include"../../include/fast_io_network.h"

int main()
try
{
	fast_io::client hd(fast_io::dns_once("localhost"),2000,fast_io::sock::type::datagrams);
	transmit(fast_io::out(),hd);
}
catch(std::exception const & e)
{
	perrln(e);
	return 1;
}