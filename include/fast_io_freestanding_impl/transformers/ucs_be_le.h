#pragma once

namespace fast_io
{

class ucs_be_le
{
public:
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
	inline static constexpr auto write_proxy(output& out,Iter begin,Iter end)
	{
		if constexpr (buffer_output_stream<output>)
		{
			auto p(oreserve(end-begin));
			if constexpr(std::is_pointer_v<std::remove_cvref_t<decltype(p)>>)
			{
				if(p)
				{
					for(Iter iter(begin);iter!=end;++iter)
					{
						*p=endian_reverse(*iter);
						++p;
					}
					return end;
				}
			}
			else
			{
				for(Iter iter(begin);iter!=end;++iter)
				{
					*p=endian_reverse(*iter);
					++p;
				}
				return end;
			}
		}
		for(Iter iter(begin);iter!=end;++iter)
			*iter=endian_reverse(*iter);
		return write(out,begin,end);
	}
	template<input_stream input,std::contiguous_iterator Iter>
	requires (sizeof(typename std::iterator_traits<Iter>::value_type)==sizeof(typename input::char_type))&&
		requires(Iter it)
		{
			*it=endian_reverse(*it);
		}
	inline static constexpr auto read_proxy(input& inp,Iter begin,Iter end)
	{
		auto v(read(inp,begin,end));
		for(Iter it(begin);it!=v;++it)
			*it=endian_reverse(*it);
		return v;
	}
};

}