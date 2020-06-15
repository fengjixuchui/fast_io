#include"../../include/fast_io.h"
#include"../../include/fast_io_device.h"
#include"../../include/fast_io_legacy.h"
#include"../timer.h"

int main()
{
	fast_io::timer tm("fill 🚄");
	fast_io::obuf_utf8_file<char32_t> utf8_file_out("utf_file.txt");
	print(utf8_file_out,fast_io::fill_nc(100000000,U'🚄'));
}