#include"../../include/fast_io_device.h"
#include"../../include/fast_io_in.h"
#include"../timer.h"

int main()
{
	std::size_t n,m;
	scan(n,m);
	fast_io::obuf_file obf("log.txt");
	fast_io::timer tm("timer");
	for(std::size_t i{};i!=n;++i)
	{
		auto ptr{new std::size_t[m]};
		println(obf,fast_io::unsigned_view(ptr));
		delete[] ptr;
	}
}