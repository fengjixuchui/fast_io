#include"../../include/fast_io_driver/boost_iostreams.h"
#include"../../include/fast_io.h"
#include <boost/iostreams/device/file_descriptor.hpp>

int main()
{
	fast_io::posix_file pf("boost_file_descriptor.txt",fast_io::open_mode::out|fast_io::open_mode::binary);
	fast_io::boost_iostreams<boost::iostreams::file_descriptor> fdstream{{pf.native_handle(),boost::iostreams::never_close_handle}};
	print(fdstream,"hello world from boost fd stream\n");
}