#pragma once

//fast_io_concept.h allows you define your device and type without compilation time penalty

#include<concepts>
#include<cstddef>
#include<type_traits>
#include<memory>

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
//	{flush(out)};
};

template<typename T>
concept mutex_stream_impl = requires(T& t)
{
	typename T::lock_guard_type;
	mutex(t);
	unlocked_handle(t);
};

template<typename T>
concept character_input_stream_impl = requires(T& in)
{
	igenerator(in);
};

template<typename T>
concept character_output_stream_impl = requires(T& out,typename T::char_type ch)
{
	put(out,ch);
};

template<typename T>
concept random_access_stream_impl = requires(T& t)
{
	seek(t,5);
};

template<typename T>
concept buffer_input_stream_impl = requires(T& in)
{
	{ibuffer_begin(in)}->std::convertible_to<typename T::char_type*>;
	ibuffer_set_curr(in,ibuffer_curr(in));
	{ibuffer_end(in)}->std::convertible_to<typename T::char_type*>;
	{underflow(in)}->std::convertible_to<bool>;
};

template<typename T>
concept contiguous_input_stream_impl = requires(T& in)
{
	iremove_prefix(in,static_cast<std::size_t>(0));
	std::to_address(idata(in));
	{isize(in)}->std::convertible_to<std::size_t>;
	ifront(in);
	iclear(in);
	{iempty(in)}->std::convertible_to<bool>;
};


template<typename T>
concept reserve_output_stream_impl = requires(T& out,std::size_t n)
{
	orelease(out,oreserve(out,n));
};

template<typename T>
concept buffer_output_stream_impl = requires(T& out,typename T::char_type ch)
{
	{obuffer_begin(out)}->std::convertible_to<typename T::char_type*>;
	{obuffer_end(out)}->std::convertible_to<typename T::char_type*>;
	obuffer_set_curr(out,obuffer_curr(out));
	overflow(out,ch);
};

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

template<typename T>
concept redirect_stream_impl = requires(T& h)
{
	redirect_handle(h);
};

template<typename T>
concept memory_map_input_stream_impl = requires(T& in)
{
	memory_map_in_handle(in);
};

template<typename T>
concept memory_map_output_stream_impl = requires(T& out)
{
	memory_map_out_handle(out);
};

/*

template<typename T>
concept status_stream = requires(T stm)
{
	{typename T::status_type};
}*/
}


template<typename T>
concept stream = details::input_stream_impl<T>||details::output_stream_impl<T>;

template<typename T>
concept redirect_stream = stream<T>&&details::redirect_stream_impl<T>;

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

template<typename T>
concept character_input_stream = input_stream<T>&&details::character_input_stream_impl<T>;

template<typename T>
concept character_output_stream = output_stream<T>&&details::character_output_stream_impl<T>;

template<typename T>
concept character_io_stream = character_input_stream<T>&&character_output_stream<T>;
/*
template<typename T>
concept undo_input_stream = character_input_stream<T>&&details::undo_input_stream_impl<T>;

template<typename T>
concept undo_output_stream = character_output_stream<T>&&details::undo_output_stream_impl<T>;

template<typename T>
concept undo_io_stream = undo_input_stream<T>&&undo_output_stream<T>;
*/
template<typename T>
concept mutex_io_stream = mutex_input_stream<T>&&mutex_output_stream<T>;

template<typename T>
concept reserve_output_stream = output_stream<T>&&details::reserve_output_stream_impl<T>;

template<typename T>
concept buffer_input_stream = input_stream<T>&&details::buffer_input_stream_impl<T>;

template<typename T>
concept contiguous_input_stream = input_stream<T>&&details::contiguous_input_stream_impl<T>;

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

template<typename T>
concept memory_map_input_stream = input_stream<T>&&details::memory_map_input_stream_impl<T>;

template<typename T>
concept memory_map_output_stream = output_stream<T>&&details::memory_map_output_stream_impl<T>;

template<typename T>
concept memory_map_io_stream = memory_map_input_stream<T>&&memory_map_output_stream<T>;

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


template<typename output,typename T>
concept sendable=output_stream<output>&&requires(output& out,T&& t)
{
	send_define(out,std::forward<T>(t));
};

template<typename T>
struct print_reserve_type_t
{
	explicit constexpr print_reserve_type_t() = default;
};
template<typename T>
inline constexpr print_reserve_type_t<T> print_reserve_type{};

template<typename T>
concept reserve_printable=requires(T&& t,char8_t* ptr)
{
	{print_reserve_size(print_reserve_type<std::remove_cvref_t<T>>)}->std::convertible_to<std::size_t>;
	{print_reserve_define(print_reserve_type<std::remove_cvref_t<T>>,ptr,t)}->std::same_as<char8_t*>;
};

template<typename output,typename T>
concept printable=output_stream<output>&&requires(output& out,T&& t)
{
	print_define(out,std::forward<T>(t));
};

template<typename output,typename T>
concept general_printable=reserve_printable<T>||printable<output,T>;

}
