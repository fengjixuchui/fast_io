#include"../../timer.h"
#include"../../../include/fast_io_device.h"
#include"../../../include/fast_io.h"

int main()
{
	constexpr std::size_t N{1000000};
	std::vector<double> buffer(N);
	{
		fast_io::timer tm("input");
		fast_io::c_file cf("very_long.txt","rb");
		for(std::size_t i{};i!=N;++i)
			fscanf(cf.native_handle(),"%lf",buffer.data()+i);
	}
	{
		fast_io::timer t("output");
		fast_io::obuf_file obf("fscanf.txt");
		for(std::size_t i{};i!=N;++i)
			println(obf,buffer[i]);
	}
}