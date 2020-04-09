#pragma once

namespace fast_io
{

template<output_stream output,input_stream input>
inline constexpr std::size_t transmit_once(output& outp,input& inp)
{
	if constexpr(mutex_input_stream<input>)
	{
		typename input::lock_guard_type lg{mutex(inp)};
		decltype(auto) uh{unlocked_handle(inp)};
		return transmit_once(outp,uh);
	}
	else if constexpr(buffer_input_stream<input>)
	{
		std::size_t bytes{};
		if(ibuffer_curr(inp)!=ibuffer_end(inp))[[unlikely]]
		{
			write(outp,ibuffer_curr(inp),ibuffer_end(inp));
			bytes += ibuffer_end(inp)-ibuffer_curr(inp);
		}
		if(!underflow(inp))[[unlikely]]
			return bytes;
		write(outp,ibuffer_curr(inp),ibuffer_end(inp));
		bytes += ibuffer_end(inp)-ibuffer_curr(inp);
		ibuffer_set_curr(inp,ibuffer_end(inp));
		return bytes;
	}
	else
	{
		using char_type = typename input::char_type;
		std::array<char_type,65536> buffer;
		auto it{read(inp,buffer.data(),buffer.data()+buffer.size())};
		write(outp,buffer.data(),it);
		return it-buffer.data();
	}
}

}