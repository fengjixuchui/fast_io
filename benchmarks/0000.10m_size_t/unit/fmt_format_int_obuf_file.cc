#include"../../timer.h"
#include"../../../include/fast_io_device.h"
#include<fmt/format.h>

int main()
{
	constexpr std::size_t N(10000000);
	{
	fast_io::timer t("fmt::format_int + obuf_file");
	fast_io::obuf_file obf("format_int_obuf_file.txt");
	for(std::size_t i{};i!=N;++i)
	{
		auto form{fmt::format_int(i)};
		write(obf,form.data(), form.data()+form.size());
		put(obf,u8'\n');
	}
	}
}