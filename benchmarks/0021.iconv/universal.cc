#include"../../include/fast_io_locale/iconv.h"
#include"../../include/fast_io.h"

int main(int argc,char** argv)
try
{
	if(argc!=5)
	{
		perr("Usage: ",fast_io::chvw(*argv)," <source encoding> <dest encoding> <source file name> <dest file name>\n");
		return 1;
	}
	auto t0{std::chrono::high_resolution_clock::now()};
	std::size_t transmitted{};
	{
	fast_io::posix_iconv picov(argv[2],argv[1]);
	fast_io::basic_ibuf_posix_iconv_file<char,char> utf8_file(picov,argv[3]);
	fast_io::obuf_file file(argv[4]);
	transmitted=transmit(file,utf8_file);
	}
	println(fast_io::chvw(argv[1])," => ",fast_io::chvw(argv[2])," code cvt (with POSIX iconv system) success!\nTransmitted:",transmitted," bytes\nElapsed Time:",std::chrono::high_resolution_clock::now()-t0);
}
catch(std::exception const& e)
{
	perrln(e);
	return 2;
}