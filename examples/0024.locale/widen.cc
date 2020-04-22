#include"../../include/fast_io.h"
#include"../../include/fast_io_device.h"
#include<iostream>
#include"../../include/fast_io_legacy.h"

int main()
{
	std::locale::global(std::locale("C"));
//THIS IS SHIT
	fast_io::cpp_locale_wrapper<fast_io::obuf_file> obf("w.txt");
	println(obf,"std::locale is damn shit: ",421421.51);


}