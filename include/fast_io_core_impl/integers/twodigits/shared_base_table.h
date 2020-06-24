#pragma once

namespace fast_io::details
{

template<std::integral char_type,std::size_t base,bool upper>
inline constexpr auto cal_content()
{
	constexpr std::size_t chars{2};
	constexpr std::size_t pw{base*base};
	std::array<std::array<char_type,chars>,pw> vals{};
	for(std::size_t i(1);i<pw;++i)
	{
		auto& val(vals[i]);
		val=vals[i-1];
		std::size_t j(chars);
		for(;j--;)
		{
			if(val[j]==base-1)
				val[j]=0;
			else
				break;
		}
		++val[j];
	}
	for(auto &e : vals)
		for(auto &e1 : e)
			if constexpr(10<base)
			{
				if(e1<10)
					e1+=0x30;
				else
				{
					if constexpr(upper)
						e1+=0x41-10;
					else
						e1+=0x61-10;
				}
			}
			else
				e1+=0x30;
	return vals;
}

template<std::integral char_type,std::size_t base,bool upper>
struct shared_static_base_table
{
	inline static constexpr auto table=cal_content<char_type,base,upper>();
};
}
