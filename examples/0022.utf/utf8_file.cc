#include"../../include/fast_io.h"
#include"../../include/fast_io_device.h"
#include"../../include/fast_io_legacy.h"
#include <string>

int main()
{
	fast_io::ibuf_utf8_file<char32_t> utf8_file_in("utf_file.txt");
	fast_io::obuf_utf8_file<char32_t> utf8_file_out("utf2_file.txt");
	for(std::u32string utf32str;scan<true>(utf8_file_in,fast_io::line(utf32str));println(utf8_file_out,utf32str));
}