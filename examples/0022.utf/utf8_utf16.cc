#include"../../include/fast_io.h"

int main()
{
	auto u16_str{fast_io::concat<std::u16string>(fast_io::code_cvt("hello world\n"))};
	print_transaction(fast_io::out,[&](auto& out){
		for(auto const& e : u16_str)
		{
			println(out,e);
		}
	});
	print(fast_io::code_cvt(u"hello world\n"));
}
