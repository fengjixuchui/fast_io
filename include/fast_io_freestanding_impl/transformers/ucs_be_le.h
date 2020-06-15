#pragma once

namespace fast_io
{

struct ucs_be_le
{
	template<std::unsigned_integral ch_type>
	requires (sizeof(ch_type)==2||sizeof(ch_type)==4)
	inline static constexpr ch_type endian_reverse(ch_type ch)
	{
		if constexpr(sizeof(ch_type)==2)
		{
			return static_cast<ch_type>(ch >> static_cast<ch_type>(8)) |
				static_cast<ch_type>(ch << static_cast<ch_type>(8)); 
		}
		else if constexpr(sizeof(ch_type)==4)
		{
			return static_cast<ch_type>((ch & static_cast<ch_type>(0xff)) << static_cast<ch_type>(24))
				| static_cast<ch_type>(ch & static_cast<ch_type>(0xff00)) << static_cast<ch_type>(8) 
				| static_cast<ch_type>(ch & static_cast<ch_type>(0xff0000)) >> static_cast<ch_type>(8) 
				| static_cast<ch_type>((ch >> static_cast<ch_type>(24)) & static_cast<ch_type>(0xff));
		}
	}
	template<output_stream output,std::contiguous_iterator Iter>
	requires (sizeof(typename std::iterator_traits<Iter>::value_type)==sizeof(typename output::char_type))&&
		requires(Iter it)
		{
			*it=endian_reverse(*it);
		}
	inline constexpr void operator()(output& out,Iter begin,Iter end)
	{
		reserve_write(out,end-begin,[&](auto ptr)
		{
			for(;begin!=end;++begin)
			{
				*ptr=endian_reverse(*begin);
				++ptr;
			}
			return ptr;
		});
	}
};

}