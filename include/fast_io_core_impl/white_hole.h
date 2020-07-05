#pragma once
#ifdef __RDSEED__
#include <immintrin.h>
#endif

namespace fast_io
{

/*
white hole is hardware random number generater. If your CPU does not support hardware random number, it will not be usable.
*/


template<std::integral ch_type=char>
class white_hole
{
public:
	using char_type = ch_type;
};

namespace details::white_hole
{
#ifdef __RDSEED__
template<std::contiguous_iterator Iter>
inline Iter read_impl(Iter begin,Iter end)
{
	if constexpr(std::same_as<char,std::remove_cvref_t<std::iter_value_t<Iter>>>)
	{
		std::byte* begin_ptr(reinterpret_cast<std::byte*>(std::to_address(begin)));
		std::byte* end_ptr(reinterpret_cast<std::byte*>(std::to_address(end)));
		std::byte* i_ptr(begin_ptr);
		for(;i_ptr+8<=end_ptr;i_ptr+=8)
		{
			std::uint64_t u64;
			if(!_rdseed64_step(std::addressof(u64)))//reinterpret_cast<std::uint64_t*>(i_ptr)))
				goto ret;
			memcpy(i_ptr,std::addressof(u64),8);
		}
		switch(end_ptr-i_ptr)
		{
		case 7:
		{
			std::uint64_t value{};
			if(!_rdseed64_step(std::addressof(value)))
				goto ret;
			memcpy(i_ptr,std::addressof(value),7);
			i_ptr+=7;
		}
		break;
		case 6:
		{
			if(!_rdseed32_step(reinterpret_cast<std::uint32_t*>(i_ptr)))
				goto ret;
			if(!_rdseed16_step(reinterpret_cast<std::uint16_t*>(i_ptr+=4)))
				goto ret;
			i_ptr+=2;
		}
		break;
		case 5:
		{
			if(!_rdseed32_step(reinterpret_cast<std::uint32_t*>(i_ptr)))
				goto ret;
			i_ptr+=4;
			std::uint16_t value1;
			if(!_rdseed16_step(std::addressof(value1)))
				goto ret;
			memcpy(i_ptr,std::addressof(value1),1);
			++i_ptr;
		}
		break;
		case 4:
		{
			if(!_rdseed32_step(reinterpret_cast<std::uint32_t*>(i_ptr)))
				goto ret;
			i_ptr+=4;
		}
		break;
		case 3:
		{
			std::uint32_t value;
			if(!_rdseed32_step(std::addressof(value)))
				goto ret;
			memcpy(i_ptr,std::addressof(value),3);
			i_ptr+=3;
		}
		break;
		case 2:
		{
			if(!_rdseed16_step(reinterpret_cast<std::uint16_t*>(i_ptr)))
				goto ret;
			i_ptr+=2;
		}
		break;
		case 1:
		{
			std::uint16_t val;
			if(!_rdseed16_step(std::addressof(val)))
				goto ret;
			memcpy(i_ptr,std::addressof(val),1);
			++i_ptr;
		}
		}
		ret: return begin+(i_ptr-begin_ptr)/sizeof(*begin);
	}
	else
	{
		return begin + (read_impl(reinterpret_cast<char*>(std::to_address(begin)),
			reinterpret_cast<char*>(std::to_address(end)))-reinterpret_cast<char*>(std::to_address(begin)))/sizeof(*begin);
	}
} 
#endif
}

template<std::integral ch_type,std::contiguous_iterator Iter>
requires (std::same_as<ch_type,std::remove_cvref_t<std::iter_value_t<Iter>>>||std::same_as<ch_type,char>)
inline constexpr Iter read(white_hole<ch_type>,Iter begin,Iter end)
{
	if(std::is_constant_evaluated())
		return begin;
	else
#ifdef __RDSEED__
		return details::white_hole::read_impl(begin,end);
#else
#ifdef __cpp_exceptions
		throw posix_error(EIO);
#else
		fast_terminate();
#endif
#endif
}

}