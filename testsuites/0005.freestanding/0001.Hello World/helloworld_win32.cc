#include"../../../include/fast_io.h"

extern "C" int __stdcall wWinMain() noexcept
{
	auto out{fast_io::win32_stdout()};
	print(out,"Hello World\n");
	return 0;
}

//g++ -o helloworld_win32 helloworld_win32.cc -Ofast -std=c++2a -s -fno-exceptions -fno-rtti -DNDEBUG -ffreestanding -static -lkernel32 -nostartfiles
//binary size: 3584 bytes

/*
ldd ./helloworld_win32.exe
        ntdll.dll => /c/WINDOWS/SYSTEM32/ntdll.dll (0x7fff9bfb0000)
        KERNEL32.DLL => /c/WINDOWS/System32/KERNEL32.DLL (0x7fff9ac80000)
        KERNELBASE.dll => /c/WINDOWS/System32/KERNELBASE.dll (0x7fff99700000)

*/