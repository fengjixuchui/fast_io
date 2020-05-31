#include"../../timer.h"
#include"../../../include/fast_io.h"
#include"../../../include/fast_io_device.h"
#include <boost/iostreams/stream.hpp>
#include <boost/iostreams/stream_buffer.hpp>
#include <boost/iostreams/device/file_descriptor.hpp>
#include<ostream>
#include<fstream>

int main()
{
	constexpr std::size_t N(10000000);
	{
	fast_io::timer t("output");
	fast_io::posix_file pf("boost_fdstream.txt",fast_io::open_mode::binary|fast_io::open_mode::out);
	boost::iostreams::stream<boost::iostreams::file_descriptor_sink> fdstream{boost::iostreams::file_descriptor_sink(pf.native_handle(),boost::iostreams::never_close_handle)};
	for(std::size_t i{};i!=N;++i)
		fdstream<<i<<'\n';
	}
	std::vector<std::size_t> vec(N);
	{
	fast_io::timer t("input");
	fast_io::posix_file pf("boost_fdstream.txt",fast_io::open_mode::binary|fast_io::open_mode::in);
	boost::iostreams::stream<boost::iostreams::file_descriptor_source> fdstream
	(boost::iostreams::file_descriptor_source(pf.native_handle(),boost::iostreams::never_close_handle));
	for(std::size_t i{};i!=N;++i)
		fdstream>>vec[i];
	}
}