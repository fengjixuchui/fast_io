#include"../../../include/fast_io.h"

extern "C" [[noreturn]] void _start() noexcept
{
	println(fast_io::out(),"Hello World\n",5,"\nLOL",4.1489124809);
	fast_io::fast_exit(0);
}

// g++ -o helloworld_linux_writev_floating_point helloworld_linux_writev_floating_point.cc -Ofast -std=c++2a -s -fno-exceptions -fno-rtti -DNDEBUG -nodefaultlibs -static -lgcc -nostartfiles -DFAST_IO_OPTIMIZE_SIZE

/*
cqwrteur@cqwrteur:~/fast_io/testsuites/0005.freestanding/0002.println$ g++ -o helloworld_linux_writev_floating_point helloworld_linux_writev_floating_point.cc -Ofast -std=c++2a -s -fno-exceptions -fno-rtti -DNDEBUG -nodefaultlibs -static -lgcc -nostartfiles -DFAST_IO_OPTIMIZE_SIZE
helloworld_linux_writev_floating_point.cc: In function 'void _start()':
helloworld_linux_writev_floating_point.cc:7:1: warning: 'noreturn' function does return
    7 | }
      | ^
cqwrteur@cqwrteur:~/fast_io/testsuites/0005.freestanding/0002.println$ ./helloworld_linux_writev_floating_point
Hello World
5
LOL4.1489124809
cqwrteur@cqwrteur:~/fast_io/testsuites/0005.freestanding/0002.println$ ldd ./helloworld_linux_writev_floating_point
        not a dynamic executable
cqwrteur@cqwrteur:~/fast_io/testsuites/0005.freestanding/0002.println$
*/
