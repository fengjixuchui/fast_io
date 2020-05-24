#pragma once
// Since the library is written before C++20. Will use standard libraries concepts after C++ 20 being official published. PLEASE Do not use these concepts!!!

namespace fast_io
{

//Since Currently No C++ Compilers have implemented this important stuff. We can only emulate it with memcpy.
//And unfortuntely, this is not what it should be. It is impossible to correctly implement this without compiler magic.
template<typename To,typename From>
requires (sizeof(To)==sizeof(From) && std::is_trivially_copyable_v<To> && std::is_trivial_v<From>)
inline To bit_cast(From const& src) noexcept
{
	To dst;
	std::memcpy(std::addressof(dst), std::addressof(src), sizeof(To));
	return dst;
}


namespace details
{


template<std::unsigned_integral U>
requires (std::same_as<U,std::uint16_t>||std::same_as<U,std::uint32_t>||std::same_as<U,std::uint64_t>)
inline U byte_swap(U a)
{
#ifdef _MSC_VER
	if constexpr(std::same_as<U,std::uint64_t>)
		return _byteswap_uint64(a);
	else if constexpr(std::same_as<U,std::uint32_t>)
		return _byteswap_ulong(a);
	else
		return _byteswap_ushort(a);
#elif (defined(__GNUG__) || defined(__clang__))
	if constexpr(std::same_as<U,std::uint64_t>)
		return __builtin_bswap64(a);
	else if constexpr(std::same_as<U,std::uint32_t>)
		return __builtin_bswap32(a);
	else
		return __builtin_bswap16(a);
#else
	std::array<std::byte,sizeof(U)> b;
	memcpy(b.data(),std::addressof(a),sizeof(U));
	std::reverse(b.begin(),b.end());
	memcpy(std::addressof(a),b.data(),sizeof(U));
	return a;
#endif
}

template<std::unsigned_integral U>
inline constexpr U big_endian(U u)
{
	if constexpr(std::endian::little==std::endian::native)
		return byte_swap(u);
	else
		return u;
}


// I think the standard libraries haven't applied these optimization

template<std::input_iterator input_iter,std::integral count_type,std::input_or_output_iterator output_iter>
inline constexpr output_iter my_copy_n(input_iter first,count_type count,output_iter result)
{
#if __cpp_lib_is_constant_evaluated>=201811L
	if (std::is_constant_evaluated())
		return std::copy_n(first,count,result);
	else
#endif
	{
	using input_value_type = typename std::iterator_traits<input_iter>::value_type;
	using output_value_type = typename std::iterator_traits<output_iter>::value_type;
	if constexpr
	(std::contiguous_iterator<input_iter>&&
	std::contiguous_iterator<output_iter>&&
	std::is_trivially_copyable_v<input_value_type>&&
	std::is_trivially_copyable_v<output_value_type>&&
	(std::same_as<input_value_type,output_value_type>||
	(std::integral<input_value_type>&&std::integral<output_value_type>&&
	sizeof(input_value_type)==sizeof(output_value_type))))
	{
		std::memmove(std::to_address(result),std::to_address(first),sizeof(typename std::iterator_traits<input_iter>::value_type)*count);
		return result+=count;
	}
	else
		return std::copy_n(first,count,result);
	}
}
template<std::input_iterator input_iter,std::input_or_output_iterator output_iter>
inline constexpr output_iter my_copy(input_iter first,input_iter second,output_iter result)
{
	using input_value_type = typename std::iterator_traits<input_iter>::value_type;
	using output_value_type = typename std::iterator_traits<output_iter>::value_type;
	if constexpr(std::contiguous_iterator<input_iter>&&std::contiguous_iterator<output_iter>&&std::is_trivially_copyable_v<input_value_type>&&
	std::is_trivially_copyable_v<output_value_type>&&
	(std::same_as<input_value_type,output_value_type>||(std::integral<input_value_type>&&std::integral<output_value_type>&&sizeof(std::is_trivially_copyable_v<input_value_type>)==sizeof(std::is_trivially_copyable_v<output_value_type>))))
	{
		my_copy_n(first,second-first,result);
		return result+(second-first);
	}
	else
		return std::copy(first,second,result);
}

template<std::input_or_output_iterator output_iter,std::integral count_type,typename T>
inline constexpr output_iter my_fill_n(output_iter first,count_type count,T const& value)
{
#if __cpp_lib_is_constant_evaluated>=201811L
	if (std::is_constant_evaluated())
		return std::fill_n(first,count,value);
	else
#endif
	{
	using output_value_type = typename std::iterator_traits<output_iter>::value_type;
	if constexpr(std::contiguous_iterator<output_iter>&&std::is_trivially_copyable_v<output_value_type>&&std::integral<output_value_type>&&sizeof(output_value_type)==1)
	{
		std::memset(std::to_address(first),static_cast<int>(value),count);
		return first+count;
	}
	else
		return std::fill_n(first,count,value);
	}
}

template<std::forward_iterator fwd_iter,typename T>
inline constexpr void my_fill(fwd_iter first,fwd_iter last,T const& value)
{
	using fwd_iter_value_type = typename std::iterator_traits<fwd_iter>::value_type;
	if constexpr(std::contiguous_iterator<fwd_iter>&&std::is_trivially_copyable_v<fwd_iter_value_type>&&std::integral<fwd_iter_value_type>&&sizeof(fwd_iter_value_type)==1)
		my_fill_n(first,last-first,value);
	else
		std::fill(first,last,value);
}

template<typename T>
using my_make_signed_t=
#ifdef __SIZEOF_INT128__
std::conditional_t<
std::same_as<std::remove_cv_t<T>,__int128_t>||std::same_as<std::remove_cv_t<T>,__uint128_t>,
std::conditional_t<std::same_as<std::remove_cv_t<T>,__int128_t>,T,
std::conditional_t<std::same_as<T,__uint128_t volatile const>,__int128_t volatile const,
std::conditional_t<std::same_as<T,__uint128_t const>,__int128_t const,
std::conditional_t<std::same_as<T,__uint128_t volatile>,__int128_t volatile,
__int128_t>>>>,
std::make_signed_t<std::conditional_t<std::same_as<std::remove_cv_t<T>,__int128_t>||std::same_as<std::remove_cv_t<T>,__uint128_t>,int,T>>>;
#else
std::make_signed_t<T>;
#endif
template<typename T>
using my_make_unsigned_t=
#ifdef __SIZEOF_INT128__
std::conditional_t<
std::same_as<std::remove_cv_t<T>,__int128_t>||std::same_as<std::remove_cv_t<T>,__uint128_t>,
std::conditional_t<std::same_as<std::remove_cv_t<T>,__uint128_t>,T,
std::conditional_t<std::same_as<T,__int128_t volatile const>,__uint128_t volatile const,
std::conditional_t<std::same_as<T,__int128_t const>,__uint128_t const,
std::conditional_t<std::same_as<T,__int128_t volatile>,__uint128_t volatile,
__uint128_t>>>>,
std::make_unsigned_t<std::conditional_t<std::same_as<std::remove_cv_t<T>,__int128_t>||std::same_as<std::remove_cv_t<T>,__uint128_t>,int,T>>>;
#else
std::make_unsigned_t<T>;
#endif

template<typename T>
concept my_integral = 
std::integral<T>
#ifdef __SIZEOF_INT128__
||std::same_as<std::remove_cv_t<T>,__uint128_t>||std::same_as<std::remove_cv_t<T>,__int128_t>
#endif
;

template<typename T>
concept my_signed_integral = 
std::signed_integral<T>
#ifdef __SIZEOF_INT128__
||std::same_as<std::remove_cv_t<T>,__int128_t>
#endif
;
template<typename T>
concept my_unsigned_integral = my_integral<T>&&!my_signed_integral<T>;

}

}