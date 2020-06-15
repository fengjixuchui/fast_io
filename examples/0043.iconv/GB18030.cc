#include"../../include/fast_io_locale/iconv.h"
#include"../../include/fast_io.h"

int main(int argc,char** argv)
try
{
	if(argc!=3)
	{
		print(fast_io::err,"Usage: ",*argv," <source UTF8 file name> <dest GB18030 file name>\n");
		return 1;
	}
	auto t0{std::chrono::high_resolution_clock::now()};
	std::size_t transmitted{};
	{
	fast_io::posix_iconv picov("GB18030","UTF-8");
	fast_io::basic_ibuf_posix_iconv_file<char,char8_t> utf8_file(picov,argv[1]);
	fast_io::obuf_file file(argv[2]);
	transmitted=transmit(file,utf8_file);
	}
	println(u8"UTF8 => GB18030 code cvt (with POSIX iconv system) success!\nTransmitted:",transmitted,u8" bytes\nElapsed Time:",std::chrono::high_resolution_clock::now()-t0);
}
catch(std::exception const& e)
{
	println(fast_io::err,e);
	return 2;
}