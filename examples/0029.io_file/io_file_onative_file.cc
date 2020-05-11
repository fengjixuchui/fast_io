#include"../../include/fast_io.h"
#include"../../include/fast_io_device.h"

int main()
{
	fast_io::io_file file(fast_io::io_cookie,std::in_place_type<fast_io::onative_file>,"io_file_onative_file.txt");
	print(file,"Hello World\n");
}