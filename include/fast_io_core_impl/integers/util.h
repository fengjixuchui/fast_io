#pragma once

namespace fast_io::details
{

template<std::uint32_t base,bool ryu_mode=false,typename U>
requires (!std::signed_integral<U>)
inline constexpr std::size_t chars_len(U value) noexcept
{
	if constexpr(base==10&&sizeof(U)<9)
	{
		if constexpr(7<sizeof(U))
		{
			if constexpr(!ryu_mode)
			{
				if(10000000000000000000ULL<=value)
					return 20;
				if(1000000000000000000ULL<=value)
					return 19;
				if(100000000000000000ULL<=value)
					return 18;
			}
			if(10000000000000000ULL<=value)
				return 17;
			if(1000000000000000ULL<=value)
				return 16;
			if(100000000000000ULL<=value)
				return 15;
			if(10000000000000ULL<=value)
				return 14;
			if(1000000000000ULL<=value)
				return 13;
			if(100000000000ULL<=value)
				return 12;
			if(10000000000ULL<=value)
				return 11;
		}
		if constexpr(3<sizeof(U))
		{
			if constexpr(4<sizeof(U)||!ryu_mode)
			{
				if(1000000000U<=value)
					return 10;
			}
			if(100000000U<=value)
				return 9;
			if(10000000U<=value)
				return 8;
			if(1000000U<=value)
				return 7;
			if(100000U<=value)
				return 6;
		}
		if constexpr(1<sizeof(U))
		{
			if(10000U<=value)
				return 5;
			if(1000U<=value)
				return 4;
		}
		if(100U<=value)
			return 3;
		if(10U<=value)
			return 2;
		return 1;
	}
	else
	{
		constexpr std::uint32_t base2(base  * base);
		constexpr std::uint32_t base3(base2 * base);
		constexpr std::uint32_t base4(base3 * base);
		for (std::size_t n(1);;n+=4)
		{
			if (value < base)
				return n;
			if (value < base2)
				return n + 1;
			if (value < base3)
				return n + 2;
			if (value < base4)
				return n + 3;
			value /= base4;
		}
	}
}

template<std::unsigned_integral T,char8_t base = 10>
requires(sizeof(T)<=8)
inline constexpr std::size_t cal_max_uint_size()
{
/*
	if constexpr(8==sizeof(T))
		return 20;
	else if constexpr(4==sizeof(T))
		return 10;
	else if constexpr(2==sizeof(T))
		return 5;
	else if constexpr(1==sizeof(T))
		return 3;*/
	std::size_t i{};
	auto n{std::numeric_limits<T>::max()};
	for(;n;++i)
		n/=base;
	return i;
}

static_assert(cal_max_uint_size<std::uint64_t,10>()==20);
static_assert(cal_max_uint_size<std::uint32_t,10>()==10);
}