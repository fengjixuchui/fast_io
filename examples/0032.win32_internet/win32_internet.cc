#include"../../include/fast_io.h"
#include"../../include/fast_io_driver/win32_internet.h"

int main()
{
	fast_io::win32_internet_https_client https_client("www.warcraftlogs.com","GET","/zone/rankings/24/");
	transmit(fast_io::out(),https_client);
}