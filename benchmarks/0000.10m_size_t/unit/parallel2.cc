#include"../../../include/fast_io.h"
#include"../../../include/fast_io_device.h"
#include"../../timer.h"

int main()
{
	fast_io::timer t("output");
	fast_io::u8onative_file onv("parrallel.txt");
	print(onv,fast_io::parrallel_counter([](fast_io::output_stream auto& output,std::size_t i,std::size_t stop_number)
	{
		for(;i!=stop_number;++i)
			print(output,fast_io::line(i));
	},10000000,22));
}