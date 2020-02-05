#pragma once

namespace fast_io
{

namespace details
{
template<output_stream outp,typename... Args>
requires (sizeof...(Args)!=0)&&(print_length_restricted<Args>&&...)
inline void print_reserve_impl(outp& out,Args&& ...args)
{
	constexpr std::size_t restricted_size(print_define_max_length(std::forward<Args>(args))+...);
	if constexpr(buffer_output_stream<outp>)
	{
		auto psp(out.pspan(out));
		if(psp.size()<restricted_size)[[likely]]
		{
			auto pp(psp.data());
			out.pbump(((pp=print_define_to_iterator(pp,std::forward<Args>(args))),...));
			return;
		}
	}
	else if constexpr(reserve_output_stream<outp>)//optimize for string like which space is dynamic allocated
	{
		if(ptest(out,restricted_size))
		{
			auto op(preserve(out,restricted_size));
			out.pbump(((op=print_define_to_iterator(op,std::forward<Args>(args))),...));
			return;
		}
/*		if constexpr(!buffer_output_stream<outp>)
		{
			if constexpr(print_length_precise<Args>&&...)
			{
				std::size_t const reserved_size(print_define_length(std::forward<Args>(args))+...);
				auto pp(preserve(out,reserved_size));
				((pp=print_define_to_iterator(pp,std::forward<Args>(args))),...);
			}
		}*/
	}
	std::array<typename outp::char_type,restricted_size> array;
	auto p(array.data());
	write(out,array.data(),((p=print_define_to_iterator(p,std::forward<Args>(args))),...));

}
}
}