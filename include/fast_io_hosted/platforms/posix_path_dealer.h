#pragma once

namespace fast_io::details
{

struct posix_path_dealer
{
	using char_type = char;
	std::size_t capacity;
	char_type* buffer_data;
	template<std::integral from_char_type>
	requires (sizeof(from_char_type)!=1)
#if __cpp_constexpr >=201907L && __cpp_constexpr_dynamic_alloc >= 201907L && __cpp_lib_is_constant_evaluated >=201811L
	constexpr
#endif
	posix_path_dealer(from_char_type const* p,std::size_t sz) noexcept:
		capacity(::fast_io::details::intrinsics::add_or_overflow_die(
			::fast_io::details::cal_decorated_reserve_size<sizeof(from_char_type),sizeof(char_type)>(sz),1)),
		buffer_data(allocate_iobuf_space<char_type>(capacity))
	{
#if __cpp_lib_is_constant_evaluated >=201811L
		if(std::is_constant_evaluated())
		{
			*codecvt::general_code_cvt_full<encoding_scheme::execution_charset,encoding_scheme::utf>(p,p+sz,buffer_data)=0;
		}
		else
#endif
		{

			using char8_may_alias_ptr
#if __has_cpp_attribute(gnu::may_alias)
			[[gnu::may_alias]]
#endif
			= char8_t*;
			*codecvt::general_code_cvt_full(p,p+sz,
			reinterpret_cast<char8_may_alias_ptr>(buffer_data))=0;			
		}
	}
	inline constexpr char_type const* c_str() noexcept
	{
		return buffer_data;
	}
	posix_path_dealer(posix_path_dealer const&)=delete;
	posix_path_dealer& operator=(posix_path_dealer const&)=delete;
#if __cpp_constexpr >=201907L && __cpp_constexpr_dynamic_alloc >= 201907L && __cpp_lib_is_constant_evaluated >=201811L
	constexpr
#endif
	~posix_path_dealer()
	{
		deallocate_iobuf_space<false>(buffer_data,capacity);
	}
};

using path_dealer = posix_path_dealer;

}