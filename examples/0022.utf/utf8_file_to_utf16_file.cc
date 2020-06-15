#include"../../include/fast_io.h"
#include"../../include/fast_io_device.h"

int main(int argc,char** argv)
try
{
	if(argc!=3)
	{
		print(fast_io::err,"Usage: ",*argv," <source UTF8 file name> <dest UTF16 (",std::endian::native==std::endian::little?"LE":"BE",") file name>\n");
		return 1;
	}
	auto t0{std::chrono::high_resolution_clock::now()};
	std::size_t transmitted{};
	{
	fast_io::ibuf_utf8_file<char16_t> utf8_file_in{argv[1]};
	fast_io::basic_obuf_file<char16_t> utf16_file{argv[2]};
	put(utf16_file,65279);	//write bom. 65279 is the code page for UTF-16 and UTF-32
	transmitted=transmit(utf16_file,utf8_file_in);
	}
	println(u8"UTF8 => UTF16 (",std::endian::native==std::endian::little?"LE":"BE",") code cvt success!\nTransmitted:",transmitted,u8" UTF16 code points\nElapsed Time:",std::chrono::high_resolution_clock::now()-t0);
}
catch(std::exception const& e)
{
	println(fast_io::err,e);
	return 2;
}