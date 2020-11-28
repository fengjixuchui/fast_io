#pragma once

namespace fast_io
{


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

template<std::integral char_type>
inline constexpr std::size_t print_reserve_size(io_reserve_type_t<char_type,void const*>) noexcept
{
	constexpr std::size_t sz{sizeof(std::uintptr_t)*2+4};
	return sz;
}

template<std::integral char_type,std::contiguous_iterator caiter>
inline constexpr caiter print_reserve_define(io_reserve_type_t<char_type,void const*>,caiter iter,void const* v) noexcept
{
	constexpr std::size_t uisz{sizeof(std::uintptr_t)*2+2};
	constexpr std::size_t uisz1{uisz+2};
	details::copy_string_literal(u8"0x",iter);
	details::optimize_size::output_unsigned_dummy<uisz,16>(iter+2,bit_cast<std::uintptr_t>(v));	
	return iter+uisz1;
}
template<std::integral char_type>
inline constexpr std::size_t print_reserve_size(io_reserve_type_t<char_type,std::nullptr_t>) noexcept
{
	constexpr std::size_t sz{9};
	return sz;
}

template<std::integral char_type,std::contiguous_iterator caiter>
inline constexpr caiter print_reserve_define(io_reserve_type_t<char_type,std::nullptr_t>,caiter iter,std::nullptr_t) noexcept
{
	details::copy_string_literal(u8"(nullptr)",iter);
	return iter+9;
}

template<output_stream output,std::integral char_type>
requires (std::same_as<typename output::char_type,char_type>)
inline constexpr void print_define(output out,basic_io_scatter_t<char_type> iosc) noexcept
{
	write(out,iosc.base,iosc.base+iosc.len);
}


template<std::integral char_type>
inline constexpr basic_io_scatter_t<char_type> print_scatter_define(print_scatter_type_t<char_type>,basic_io_scatter_t<char_type> iosc) noexcept
{
	return iosc;
}

template<std::integral char_type,std::size_t n>
inline constexpr auto print_alias_define(io_alias_t,char_type const(&s)[n]) noexcept
{
	if constexpr(n==2)
		return manip::chvw<char_type>(*s);
	else
		return basic_io_scatter_t<char_type>{s,n-1};
}

template<std::integral char_type>
inline constexpr basic_io_scatter_t<char_type> print_alias_define(io_alias_t,std::basic_string_view<char_type> svw) noexcept
{
	return {svw.data(),svw.size()};
}

template<std::integral T>
inline constexpr auto print_alias_define(io_alias_t,manip::chvw<T const*> svw)
{
	std::basic_string_view<T> bsv{svw.reference};
	return basic_io_scatter_t<T>{bsv.data(),bsv.size()};
}

template<typename Iter>
requires (std::contiguous_iterator<Iter>||std::is_pointer_v<Iter>)
inline constexpr void const* print_alias_define(io_alias_t,Iter it) noexcept
{
	if constexpr(std::is_pointer_v<std::remove_cvref_t<Iter>>)
		return it;
	else
		return std::to_address(it);
}

template<std::integral char_type,std::integral pchar_type>
inline constexpr std::size_t print_reserve_size(io_reserve_type_t<char_type,manip::chvw<pchar_type>>) noexcept
{
	return 1;
}

template<std::integral char_type,std::integral pchar_type,std::contiguous_iterator caiter,typename T>
inline constexpr caiter print_reserve_define(io_reserve_type_t<char_type,manip::chvw<pchar_type>>,caiter iter,T ch) noexcept
{
	*iter=static_cast<pchar_type>(ch.reference);
	return ++iter;
}

}
