#include"../../include/fast_io.h"

int main()
{
	println("concat:",fast_io::concat(),"\nconcatln:",fast_io::concatln(),"\n",fast_io::concat("ok"),fast_io::concat(std::string("ok"),"okokokok"));
}