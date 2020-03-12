#include"../../include/fast_io.h"
#include"../../include/fast_io_legacy.h"

int main()
{
	fast_io::posix_file pf("a.txt",fast_io::open_interface<fast_io::open_mode::out>);
	print(pf,"Hello World\n");
	fast_io::win32_io_observer obs(pf);
	print(obs,"hello world from win32\n");
}