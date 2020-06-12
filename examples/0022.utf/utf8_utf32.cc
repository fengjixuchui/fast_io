#include"../../include/fast_io.h"

int main()
{
	auto u32_str{fast_io::concat<std::u32string>(fast_io::code_cvt("hello world\n"))};
	print_transaction(fast_io::out,[&](auto& out){
		for(auto const& e : u32_str)
		{
			println(out,e);
		}
	});
}