#include"../../include/fast_io.h"
#include"../../include/fast_io_device.h"
#include"../../include/fast_io_in.h"

int main()
{
	std::string str("18446744073709551615");
	constexpr std::string_view grouping("\0\0\4\4\4\4\4\4\4\4\4");
	auto gp_cendm1{grouping.cend()-1};
	constexpr char8_t seperator{u8','};
	auto str_iter(str.data()+str.size());
	std::array<char,1024> buffer;
	auto buffer_iter(buffer.data()+buffer.size());
	for(auto iter(grouping.cbegin());;)
	{
		char8_t gp{static_cast<char8_t>(*iter)};
		if(gp)[[likely]]
		{
			if(str_iter-gp<str.data())[[unlikely]]
				break;
			if(std::is_constant_evaluated())
				std::copy_n(str_iter-=gp,gp,buffer_iter-=gp);
			else
				memcpy(buffer_iter-=gp,str_iter-=gp,gp);
			*--buffer_iter=seperator;
		}
		if(iter!=gp_cendm1)[[likely]]
			++iter;
	}
	if(std::size_t const sz(str_iter-str.data());sz)
	{
		if(std::is_constant_evaluated())
			std::copy_n(str_iter-=sz,sz,buffer_iter-=sz);
		else
			memcpy(buffer_iter-=sz,str.data(),sz);
	}
	else
		++buffer_iter;
	write(fast_io::out,buffer_iter,buffer.data()+buffer.size());
}