#include"../../../include/fast_io.h"

extern "C" [[noreturn]] void _start() noexcept
{
	println(fast_io::out(),"Hello World\n",5,"\nLOL");
	fast_io::fast_exit(0);
}

//g++ -o helloworld_linux_writev helloworld_linux_writev.cc -Ofast -std=c++2a -s -fno-exceptions -fno-rtti -DNDEBUG -nodefaultlibs -static -lgcc -nostartfiles -DFAST_IO_OPTIMIZE_SIZE

/*
$ ldd ./helloworld_linux_writev
        not a dynamic executable
*/
