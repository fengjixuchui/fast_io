#include"../../../include/fast_io.h"
#include"../../../include/fast_io_device.h"
#include"../../timer.h"

int main()
{
	fast_io::timer t("output");
	fast_io::u8onative_file onv("parallel_unit.txt");
	print(onv,fast_io::parallel_unit([](auto const& i)
	{
		return fast_io::line(i);
	},10000000));
}