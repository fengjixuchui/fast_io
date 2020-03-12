#include"../../include/fast_io.h"
#include"../../include/fast_io_device.h"
#include"../../include/fast_io_legacy.h"

int main()
{
	using namespace std::string_view_literals;
	auto wstr{fast_io::concat<std::u16string>(fast_io::code_cvt(u8"abcdefgh我"sv))};
	for(auto const & e : wstr)
		println(fast_io::c_stdout,e);
}