#pragma once

namespace fast_io
{

template<std::integral CharT,typename Traits = std::char_traits<CharT>,typename Allocator = std::allocator<CharT>>
class obasic_string_ref
{
public:
	using char_type = CharT;
	using allocator_type = Allocator;
	using string_type = std::basic_string<CharT,Traits,Allocator>;
	string_type& reference;
};

template<std::integral char_type,typename traits_type,typename allocator_type>
[[nodiscard]] constexpr auto obuffer_begin(obasic_string_ref<char_type,traits_type,allocator_type> ob)
{
	return std::to_address(ob.reference.data());
}

template<std::integral char_type,typename traits_type,typename allocator_type>
[[nodiscard]] constexpr auto obuffer_curr(obasic_string_ref<char_type,traits_type,allocator_type> ob)
{
	return std::to_address(ob.reference.data()+ob.reference.size());
}

template<std::integral char_type,typename traits_type,typename allocator_type>
[[nodiscard]] constexpr auto obuffer_end(obasic_string_ref<char_type,traits_type,allocator_type> ob)
{
	return std::to_address(ob.reference.data()+ob.reference.capacity());
}

template<std::integral char_type,typename traits_type,typename allocator_type>
inline constexpr void obuffer_set_curr(obasic_string_ref<char_type,traits_type,allocator_type> ob,char_type* ptr)
{
	details::string_hack::set_end_ptr(ob.reference,ptr);
}

template<std::integral char_type,typename traits_type,typename allocator_type>
inline constexpr void otakeover(obasic_string_ref<char_type,traits_type,allocator_type> ob,char_type* beg_ptr,char_type* end_ptr,char_type* cap_ptr)
{
	traits_type::assign(*end_ptr, char_type());
	details::string_hack::set_begin_ptr(ob.reference,beg_ptr);
	details::string_hack::set_end_ptr(ob.reference,end_ptr);
	details::string_hack::set_cap_ptr(ob.reference,cap_ptr-1);
}

template<std::integral char_type,typename traits_type,typename allocator_type>
inline constexpr bool ocan_takeover(obasic_string_ref<char_type,traits_type,allocator_type> ob)
{
	return details::string_hack::is_local_and_null(ob.reference);
}

template<std::integral char_type,typename traits_type,typename allocator_type>
inline constexpr void ogrow(obasic_string_ref<char_type,traits_type,allocator_type> ob,std::size_t newsz)
{
	ob.reference.reserve(newsz);
}

template<std::integral char_type,typename traits_type,typename allocator_type>
inline constexpr void overflow(obasic_string_ref<char_type,traits_type,allocator_type> ob,char_type ch)
{
	ob.reference.push_back(ch);
}

template<std::integral char_type,typename traits_type,typename allocator_type,std::contiguous_iterator Iter>
requires (std::same_as<char_type,char>||
	std::same_as<char_type,typename std::iterator_traits<Iter>::value_type>)
inline constexpr void write(obasic_string_ref<char_type,traits_type,allocator_type> ob,Iter begin,Iter end)
{
	if constexpr(std::same_as<char_type,std::iter_value_t<Iter>>)
		ob.reference.insert(ob.reference.cend(),begin,end);
	else
		ob.reference.insert(ob.reference.cend(),reinterpret_cast<char const*>(std::to_address(begin)),reinterpret_cast<char const*>(std::to_address(end)));
}

template<std::integral char_type,typename traits_type,typename allocator_type>
inline constexpr void flush(obasic_string_ref<char_type,traits_type,allocator_type>){}

static_assert(dynamic_buffer_output_stream<obasic_string_ref<char>>);

}