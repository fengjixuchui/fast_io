#pragma once

#include"before_cpp20_concept.h"

namespace fast_io
{

namespace details
{

template<typename T>
concept stream_char_type_requirement = requires(T&)
{
	typename T::char_type;
};

template<typename T>
concept input_stream_impl = stream_char_type_requirement<T>&&requires(T& in,typename T::char_type* b)
{
	read(in,b,b);
};

template<typename T>
concept output_stream_impl = stream_char_type_requirement<T>&&requires(T& out,typename T::char_type const* b)
{
	{write(out,b,b)};
	{flush(out)};
};

template<typename T>
concept mutex_stream_impl = requires(T& t)
{
	typename T::lock_guard_type;
	mutex(t);
	unlocked_handle(t);
};
/*
template<typename T>
concept character_input_stream_impl = requires(T& in)
{
	get(in);
};

template<typename T>
concept character_output_stream_impl = requires(T& out,typename T::char_type ch)
{
	put(out,ch);
};
*/
template<typename T>
concept random_access_stream_impl = requires(T& t)
{
	seek(t,5);
};

template<typename T>
concept buffer_input_stream_impl = std::ranges::contiguous_range<T>&&requires(T& in,std::size_t n)
{
	{iflush(in)}->std::same_as<bool>;
	in+=n;
	++in;
	iclear(in);
};

template<typename T>
concept reserve_output_stream_impl = requires(T& out,std::size_t n)
{
	{out.ptest(n)};
	{out.pbump(out.preserve(n))};
};

template<typename T>
concept buffer_output_stream_impl = reserve_output_stream_impl<T>&&requires(T& out)
{
	{out.pspan()};
	{out.pbase()};
}

template<typename T>
concept zero_copy_input_stream_impl = requires(T& in)
{
	zero_copy_in_handle(in);
};

template<typename T>
concept zero_copy_output_stream_impl = requires(T& out)
{
	zero_copy_out_handle(out);
};
}


template<typename T>
concept stream = std::movable<T>&&(details::input_stream_impl<T>||details::output_stream_impl<T>);

template<typename T>
concept input_stream = stream<T>&&details::input_stream_impl<T>;

template<typename T>
concept output_stream = stream<T>&&details::output_stream_impl<T>;

template<typename T>
concept mutex_stream = stream<T>&&details::mutex_stream_impl<T>;

template<typename T>
concept mutex_input_stream = mutex_stream<T>&&input_stream<T>;

template<typename T>
concept mutex_output_stream = mutex_stream<T>&&output_stream<T>;

template<typename T>
concept random_access_stream = stream<T>&&details::random_access_stream_impl<T>;

template<typename T>
concept io_stream = input_stream<T>&&output_stream<T>;
/*
template<typename T>
concept character_input_stream = input_stream<T>&&details::character_input_stream_impl<T>;
*/
template<typename T>
concept character_output_stream = output_stream<T>&&details::character_output_stream_impl<T>;
/*
template<typename T>
concept character_io_stream = character_input_stream<T>&&character_output_stream<T>;
*/
template<typename T>
concept mutex_io_stream = mutex_input_stream<T>&&mutex_output_stream<T>;

template<typename T>
concept buffer_input_stream = input_stream<T>&&details::buffer_input_stream_impl<T>;

template<typename T>
concept buffer_output_stream = output_stream<T>&&details::buffer_output_stream_impl<T>;

template<typename T>
concept buffer_io_stream = buffer_input_stream<T>&&buffer_output_stream<T>&&io_stream<T>;


template<typename T>
concept zero_copy_input_stream = input_stream<T>&&details::zero_copy_input_stream_impl<T>;

template<typename T>
concept zero_copy_output_stream = output_stream<T>&&details::zero_copy_output_stream_impl<T>;

template<typename T>
concept zero_copy_io_stream = zero_copy_input_stream<T>&&zero_copy_output_stream<T>;

template<typename input,typename T>
concept scanable=input_stream<input>&&requires(input& in,T&& t)
{
	scan_define(in,std::forward<T>(t));
};

template<typename input,typename T>
concept receiveable=input_stream<input>&&requires(input& in,T&& t)
{
	receive_define(in,std::forward<T>(t));
};

template<typename T>
concept print_length_restricted=requires(T&& t,char8_t* p)
{
	{print_define_max_length(t)}->std::convertible_to<std::size_t>;
	{print_define_to_iterator(t,p)}->std::same_as<char8_t*>;
};

template<typename T>
concept print_length_precise=print_length_restricted<T>&&requires(T&& t)
{
	{print_define_length(t)}->std::convertible_to<std::size_t>;
};

template<typename output,typename T>
concept printable=output_stream<output>&&(print_length_restricted<T>||requires(output& out,T&& t)
{
	print_define(out,std::forward<T>(t));
});

template<typename output,typename T>
concept printlnable=output_stream<output>&&requires(output& out,T&& t)
{
	println_define(out,std::forward<T>(t));
};

template<typename output,typename T>
concept sendable=output_stream<output>&&requires(output& out,T&& t)
{
	send_define(out,std::forward<T>(t));
};

}
