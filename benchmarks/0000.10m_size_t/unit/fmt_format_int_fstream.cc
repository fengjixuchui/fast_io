#include"../../timer.h"
#include"../../../include/fast_io_device.h"
#include<fmt/format.h>
#include<fstream>

int main()
{
	constexpr std::size_t N(10000000);
	{
	fast_io::timer t("fmt::format_int + ofstream + tricks");
	std::ofstream fout("format_int_fstream.txt",std::ofstream::binary);
	auto& rdbuf(*fout.rdbuf());
	for(std::size_t i{};i!=N;++i)
	{
		auto form{fmt::format_int(i)};
		fout.write(form.data(), form.size());
		rdbuf.sputc('\n');
	}
	}
}