#include"../../../include/fast_io.h"
#include"../../timer.h"

int main()
{
	constexpr std::size_t N{100000000};
	fast_io::timer tm("fwrite");
	constexpr std::string_view view("Hello World\n");
	fast_io::c_file cfl("fwrite.txt","wb");
	for(std::size_t i{};i!=N;++i)
		fwrite(view.data(),1,view.size(),cfl.native_handle());
}