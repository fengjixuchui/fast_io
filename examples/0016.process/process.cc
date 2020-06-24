#include"../../include/fast_io.h"
#include"../../include/fast_io_device.h"

int main()
try
{
	fast_io::native_pipe pipe;
	fast_io::jprocess process("/usr/local/bin/g++",{"-v"},{.out=pipe,.err=pipe});
	fast_io::native_pipe pipe1;
	fast_io::jprocess process1("./transmit",{},{.in=pipe,.out=pipe1,.err=pipe1});
	fast_io::native_pipe pipe2;
	fast_io::jprocess process2("./transmit",{},{.in=pipe1,.out=pipe2,.err=pipe2});
	fast_io::onative_file onv("on.txt");
	transmit(onv,pipe2);
}
catch(std::exception const& e)
{
	perrln(e);
	return 1;
}