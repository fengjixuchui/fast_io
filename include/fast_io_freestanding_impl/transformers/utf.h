#pragma once

namespace fast_io
{

namespace transforms
{

struct utf
{
	template<output_stream output,std::contiguous_iterator Iter>
	constexpr auto operator()(output& out,Iter begin,Iter end)
	{
		constexpr std::size_t coff{sizeof(typename output::char_type)<sizeof(*begin)?2:0};
		reserve_write(out,static_cast<std::size_t>(end-begin)<<coff,[&](auto ptr)
		{
			return fast_io::details::utf::utf_code_convert_details<true>(begin,end,ptr);
		});
		return begin;
	}
};

}

}