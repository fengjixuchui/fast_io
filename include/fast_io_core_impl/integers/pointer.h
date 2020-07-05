#pragma once

namespace fast_io
{

template<output_stream output,std::integral array_value_type,std::size_t n>
requires (std::same_as<typename output::char_type,std::remove_cvref_t<array_value_type>>||
(std::same_as<typename output::char_type,char>&&std::same_as<std::remove_cvref_t<array_value_type>,char8_t>)
&&n!=0)	//array cannot be zero size. but we do the check too
constexpr void print_define(output& out,array_value_type (&s)[n])
{
	if constexpr(1<n)
	{
		if constexpr(n==2&&character_output_stream<output>)
			put(out,static_cast<typename output::char_type>(*s));
		else
			write(out,s,s+(n-1));
	}
}

/*
we do not accept char const* since we never know whether it has null terminator.
This avoids security vulneralbilities for
	char * str = 0;
	print(str);
Instead, we print out its pointer value

We extend print pointers to print contiguous_iterator. No we can write things like

std::vector<std::size_t> vec(100,2);
println("vec.begin():",vec.begin()," vec.end()",vec.end());
*/

template<typename Iter>
requires (std::contiguous_iterator<Iter>||std::same_as<std::remove_cvref_t<Iter>,void*>)
inline constexpr std::size_t print_reserve_size(print_reserve_type_t<Iter>)
{
	constexpr std::size_t sz{sizeof(std::uintptr_t)*2+4};
	return sz;
}

template<typename Iter,std::contiguous_iterator caiter,typename U>
requires (std::contiguous_iterator<Iter>||std::same_as<std::remove_cvref_t<Iter>,void*>)
inline caiter print_reserve_define(print_reserve_type_t<Iter>,caiter iter,U&& v)
{
	constexpr std::size_t uisz{sizeof(std::uintptr_t)*2+2};
	constexpr std::size_t uisz1{uisz+2};
	details::my_copy_n(u8"0x",2,iter);
	details::optimize_size::output_unsigned_dummy<uisz,16>(iter+2,bit_cast<std::uintptr_t>(std::to_address(v)));
	return iter+uisz1;
}


template<std::integral char_type,std::integral array_value_type,std::size_t n>
requires (std::same_as<char_type,std::remove_cvref_t<array_value_type>>||
(std::same_as<char_type,char>&&std::same_as<std::remove_cvref_t<array_value_type>,char8_t>)
&&n!=0)	//array cannot be zero size. but we do the check too
constexpr io_scatter_t print_scatter_define(array_value_type (&s)[n])
{
	return io_scatter(s,s+(n-1));
}

template<std::integral char_type,std::integral T>
requires (std::same_as<char_type,std::remove_cvref_t<T>>||
(std::same_as<char_type,char>&&std::same_as<std::remove_cvref_t<T>,char8_t>))
constexpr io_scatter_t print_scatter_define(manip::chvw<T*> a)
{
	std::basic_string_view<std::remove_cvref_t<T>> bsv(a.reference);
	return io_scatter(a.reference,a.reference+bsv.size());
}


template<std::integral char_type,typename T>
requires (!std::is_pointer_v<std::remove_cvref_t<T>>&&!std::is_array_v<std::remove_cvref_t<T>>&&
(std::convertible_to<T,std::basic_string_view<char_type>>||(std::same_as<char_type,char>&&std::convertible_to<T,std::basic_string_view<char8_t>>)))
constexpr io_scatter_t print_scatter_define(T&& convt_str)
{
	std::basic_string_view<std::conditional_t<std::convertible_to<T,std::basic_string_view<char_type>>,char_type,char>> str(std::forward<T>(convt_str));
	return io_scatter(str.data(),str.data()+str.size());
}

template<output_stream output>
inline constexpr void print_define(output& out,std::basic_string_view<typename output::char_type> str)
{
	write(out,str.data(),str.data()+str.size());
}


}