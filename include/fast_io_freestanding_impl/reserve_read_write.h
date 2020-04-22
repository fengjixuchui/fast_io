#pragma once

namespace fast_io
{


namespace details
{
template<output_stream output,typename Func>
constexpr void reserve_write_cold_path(output& out,std::size_t required_size,Func& func)
{
	if(required_size<=1024)[[likely]]
	{
		std::array<typename output::char_type,1024> temp_buffer;
		write_all(out,temp_buffer.data(),func(temp_buffer.data()));
	}
	else
	{
		details::temp_unique_arr_ptr<typename output::char_type> temp_buffer(required_size);
		write_all(out,temp_buffer.data(),func(temp_buffer.data()));
	}
}

template<input_stream input,typename Func>
constexpr void reserve_read_cold_path(input& in,std::size_t required_size,Func& func)
{
	if(required_size<=1024)[[likely]]
	{
		std::array<typename input::char_type,1024> temp_buffer;
		func(temp_buffer.data(),read(in,temp_buffer.data(),temp_buffer.data()+required_size));
	}
	else
	{
		details::temp_unique_arr_ptr<typename input::char_type> temp_buffer(required_size);
		func(temp_buffer.data(),read(in,temp_buffer.data(),temp_buffer.data()+required_size));
	}
}
}

template<output_stream output,typename Func>
requires std::invocable<Func,typename output::char_type*>
inline constexpr void reserve_write(output& out,std::size_t required_size,Func func)
{
	if constexpr(reserve_output_stream<output>)
	{
		auto iter{oreserve(out,required_size)};
		if constexpr(std::is_pointer_v<std::remove_cvref_t<decltype(iter)>>)
		{
			if(iter==nullptr)[[unlikely]]
				details::reserve_write_cold_path(out,required_size,func);
			else
				orelease(out,func(iter));
			
		}
		else if constexpr(std::contiguous_iterator<std::remove_cvref_t<decltype(iter)>>)
			orelease(out,func(std::to_address(iter))-std::to_address(iter)+iter);
		else
			orelease(out,func(iter));
	}
	else
		details::reserve_write_cold_path(out,required_size,func);
}

template<input_stream input,typename Func>
requires std::invocable<Func,typename input::char_type*>
inline constexpr void reserve_read(input& in,std::size_t required_size,Func func)
{
	if constexpr(buffer_input_stream<input>)
	{
		auto curr{ibuffer_curr(in)};
		std::size_t const cap(ibuffer_end(in)-curr);
		if(required_size<=cap)[[likely]]
		{
			auto ed{curr+required_size};
			func(curr,ed);
			ibuffer_set_curr(in,ed);
		}
		else
			details::reserve_read_cold_path(in,required_size,func);
	}
	else if constexpr(contiguous_input_stream<input>)
	{
		auto curr{ibuffer_curr(in)};
		std::size_t cap{isize(in)};
		if(required_size<cap)
			cap=required_size;
		func(curr,curr+cap);
		iremove_prefix(in,cap);
	}
	else
		details::reserve_read_cold_path(in,required_size,func);
}

}