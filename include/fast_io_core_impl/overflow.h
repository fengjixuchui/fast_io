#pragma once

namespace fast_io
{


template<buffer_output_stream output,std::integral I>
inline constexpr auto oreserve(output& out,I n)->typename output::char_type*
{
	if(obuffer_end(out)<=obuffer_curr(out)+n)[[unlikely]]
		return nullptr;
	return obuffer_curr(out);
}

template<buffer_output_stream output>
inline constexpr void orelease(output& out,typename output::char_type* ptr)
{
	obuffer_set_curr(out,ptr);
}

template<buffer_output_stream output>
inline constexpr void put(output& out,typename output::char_type ch)
{
	auto ref{obuffer_curr(out)};
	if(ref==obuffer_end(out))[[unlikely]]
	{
		overflow(out,ch);
		return;
	}
	*ref=ch;
	obuffer_set_curr(out,ref+1);
//	++ref;
}
} // namespace fast_io
