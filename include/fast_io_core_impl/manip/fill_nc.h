#pragma once

namespace fast_io
{

namespace manip
{

template<std::integral char_type>
struct fill_nc
{
	using manip_tag = manip_tag_t;
	std::size_t count;
	char_type character;
};

template<std::integral char_type>
struct fill_ns
{
	using manip_tag = manip_tag_t;
	std::size_t count;
	std::basic_string_view<char_type> strvw;
};

}

template<std::integral ch_type>
inline constexpr manip::fill_nc<ch_type> fill_nc(std::size_t count,ch_type ch)
{
	return {count,ch};
}

namespace details
{
template<dynamic_buffer_output_stream output,std::integral ch_type>
constexpr void fill_nc_bad_path(output& out,manip::fill_nc<ch_type> ref)
{
//	if constexpr(dynamic_buffer_output_stream<output>)
//	{
		auto beg_ptr(obuffer_begin(out));
		std::size_t new_capacity((obuffer_end(out)-beg_ptr)<<1);
		std::size_t to_write_chars(obuffer_curr(out)-beg_ptr+ref.count);
		if(new_capacity<to_write_chars)
			new_capacity=to_write_chars;
		ogrow(out,new_capacity);
		auto curr{obuffer_curr(out)};
		my_fill_n(curr,ref.count,ref.character);
		obuffer_set_curr(out,curr+ref.count);
/*	}
	else
	{
		auto curr{obuffer_curr(out)};
		auto ed{obuffer_end(out)};
		auto b{obuffer_begin(out)};
		std::size_t remain(ref.count-(ed-curr));
		my_fill(curr,ed,ref.character);
		obuffer_set_curr(out,ed);
		overflow(out,ref.character);

		b=obuffer_begin(out);
		ed=obuffer_end(out);
		std::size_t buffer_size(ed-b);

		if(buffer_size<remain)[[unlikely]]
		{
			if(buffer_size==0)[[unlikely]]
				buffer_size=1;

			details::my_fill(obuffer_begin(out),obuffer_end(out),ref.character);
			std::size_t times(remain/buffer_size);
			buffer_size = remain%buffer_size;
			for(std::size_t i{};i!=times;++i)
			{
				obuffer_set_curr(out,ed);
				overflow(out,ref.character);
			}
			obuffer_set_curr(out,obuffer_begin(out)+buffer_size);
		}
		else
		{
			auto b{obuffer_begin(out)};
			details::my_fill_n(b,remain,ref.character);
			obuffer_set_curr(out,b+remain);
		}
	}*/
}
}

template<output_stream output,std::integral ch_type>
requires (dynamic_buffer_output_stream<output>||fill_nc_output_stream<output>)
inline constexpr void print_define(output& out,manip::fill_nc<ch_type> ref)
{
	if constexpr(fill_nc_output_stream<output>)
		fill_nc_define(out,ref.count,ref.character);
	else
	{
		auto curr(obuffer_curr(out));
		auto ed(obuffer_end(out));
		if(ed-curr<ref.count)[[unlikely]]
		{
			details::fill_nc_bad_path(out,ref);
			return;
		}
		details::my_fill_n(curr,ref.count,ref.character);
		obuffer_set_curr(out,curr+ref.count);
	}
}

}