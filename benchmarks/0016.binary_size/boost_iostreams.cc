#include <boost/iostreams/stream.hpp>
#include <boost/iostreams/stream_buffer.hpp>
#include <boost/iostreams/device/file_descriptor.hpp>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main()
{
	namespace io = boost::iostreams;
	io::stream_buffer<io::file_descriptor_sink> fdstreambuf{io::file_descriptor_source(::open("hello.txt",O_WRONLY|O_TRUNC),boost::iostreams::close_handle)};
	
}