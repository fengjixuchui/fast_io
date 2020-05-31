#include"../../include/fast_io.h"

int main()
{
	fast_io::basic_obuf<fast_io::posix_file> pf("fast_io_posix_file.txt",fast_io::open_mode::binary|fast_io::open_mode::out);
}