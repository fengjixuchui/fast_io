#include<iostream>
#include"../../include/fast_io.h"
#include"../../include/fast_io_device.h"
#include"../../include/fast_io_legacy.h"

int main()
{
	using namespace std::string_view_literals;
//	auto str{u8"std_to_chars_obuf_file.txt"sv};
//	std::array<char16_t,1000> arr{};
//	auto it{fast_io::code_cvt_from_utf8_to_utf16(str.data(),str.data()+str.size(),arr.data())};

	auto wstr{fast_io::concat<std::u16string>(fast_io::code_cvt(u8"std_to_chars_obuf_file.txt"sv))};
	for(auto const & e : wstr)
		println(e);
}