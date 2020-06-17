#pragma once

namespace fast_io
{

template<output_stream output,std::integral array_value_type,std::size_t n>
requires (std::same_as<typename output::char_type,std::remove_cvref_t<array_value_type>>&&n!=0)	//array cannot be zero size. but we do the check too
constexpr void print_define(output& out,array_value_type (&s)[n])
{
	if constexpr(1<n)
	{
		if constexpr(n==2&&character_output_stream<output>)
			put(out,*s);
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

template<std::contiguous_iterator Iter>
inline constexpr std::size_t print_reserve_size(print_reserve_type_t<Iter>)
{
	constexpr std::size_t sz{sizeof(std::uintptr_t)*2+4};
	return sz;
}

template<std::contiguous_iterator Iter,std::contiguous_iterator caiter,typename U>
inline caiter print_reserve_define(print_reserve_type_t<Iter>,caiter iter,U&& v)
{
	constexpr std::size_t uisz{sizeof(std::uintptr_t)*2+2};
	constexpr std::size_t uisz1{uisz+2};
	details::my_copy_n(u8"0x",2,iter);
	details::optimize_size::output_unsigned_dummy<uisz,16>(iter+2,bit_cast<std::uintptr_t>(std::to_address(v)));
	return iter+uisz1;
}


}