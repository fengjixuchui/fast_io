#pragma once

namespace fast_io
{

template<typename T>
concept async_input_stream_impl = stream_char_type_requirement<T>&&requires(T& in,typename T::char_type* b)
{
	async_read(in,b,b);
};

template<typename T>
concept async_output_stream_impl = stream_char_type_requirement<T>&&requires(T& out,typename T::char_type const* b)
{
	async_write(out,b,b);
};

template<typename T>
concept async_input_stream = stream<T>&&details::async_input_stream_impl<T>;

template<typename T>
concept async_output_stream = stream<T>&&details::async_output_stream_impl<T>;

}