#include"../../include/fast_io.h"
#include"../../include/fast_io_legacy.h"

int main()
{
	fast_io::nt_io_observer ob{static_cast<fast_io::nt_io_observer>(fast_io::out())};
	print(ob,"Hello World\n");
}