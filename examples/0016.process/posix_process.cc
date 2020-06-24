#include"../../include/fast_io.h"
#include"../../include/fast_io_device.h"

int main()
try
{
	fast_io::native_pipe pipe;
	fast_io::posix_jprocess process(fast_io::native_interface);
	if(is_child(process))
	{
		pipe.in().close();
		fast_io::out()=pipe.out();
		pipe.out().close();
		fast_io::posix_exec("/usr/local/bin/g++",{"--version"});
	}
	pipe.out().close();
	transmit(fast_io::out(),pipe);
	println("Process ID:",process.id());
}
catch(std::exception const& e)
{
	perrln(e);
	return 1;
}