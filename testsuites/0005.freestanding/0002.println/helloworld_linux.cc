#include"../../../include/fast_io.h"

extern "C" [[noreturn]] void _start() noexcept
{
	println("Hello World\n",5);
	fast_io::fast_exit(0);
}

//g++ -o helloworld_linux helloworld_linux.cc -Ofast -std=c++2a -s -fno-exceptions -fno-rtti -DNDEBUG -ffreestanding -nodefaultlibs -static -lgcc -nostartfiles -DFAST_IO_GLOBAL_NEW
//binary size: 768 bytes

/*
$ ldd ./helloworld_linux
        not a dynamic executable
*/