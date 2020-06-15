#include"../../include/fast_io.h"
#include"impl.h"

int main()
{
	std::string str;
	fast_io::obasic_string_ref<char> basr{str};
	print(basr,fast_io::code_cvt(u"我是猪头250"));
	for(std::size_t i{};i!=28;++i)
	str.push_back('d');
	println(str,"\nsize:",str.size()," capacity:",str.capacity());
}