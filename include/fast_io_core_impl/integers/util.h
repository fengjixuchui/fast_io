#pragma once

namespace fast_io::details
{

template<my_integral T>
inline constexpr T compile_time_pow(T base,std::size_t pow)
{
	T t=1;
	for(std::size_t i{};i!=pow;++i)
		t*=base;
	return t;
}

template<my_integral T,std::size_t pow>
inline constexpr auto compile_pow10()
{
	constexpr auto value{compile_time_pow(std::remove_cvref_t<T>(10),pow)};
	return value;
}

template<my_integral T,std::size_t pow>
inline constexpr auto compile_pow5()
{
	constexpr auto value{compile_time_pow(std::remove_cvref_t<T>(5),pow)};
	return value;
}

template<std::unsigned_integral uint_type>
inline constexpr auto power10_table_generator()
{
	constexpr std::size_t digits10(std::numeric_limits<uint_type>::digits10+1);
	std::array<uint_type,digits10> array{};
	uint_type v{1};
	for(std::size_t i{1};i!=digits10;++i)
		array[i]=(v*=static_cast<uint_type>(10));
	return array;
}

template<std::unsigned_integral uint_type>
inline constexpr auto power10table{power10_table_generator<uint_type>()};

template<std::uint32_t base,bool ryu_mode=false,my_unsigned_integral U>
inline constexpr std::uint32_t chars_len(U value) noexcept
{
/*
	if constexpr(base==10&&sizeof(U)<=8)
	{
		std::uint32_t t{static_cast<std::uint32_t>(std::bit_width(static_cast<std::remove_cvref_t<U>>(value|1)))*1233 >> 12};
		return t-(value<power10table<std::remove_cvref_t<U>>[t]) + 1;
	}
	else
*/
	if constexpr(base==10&&sizeof(U)<=16)
	{
		if constexpr(15<sizeof(U))
		{
			using M = std::remove_cvref_t<U>;
			if constexpr(16<sizeof(M)||!ryu_mode)
			{
			if(compile_pow10<M,38>()<=value)
				return 39;
			if(compile_pow10<M,37>()<=value)
				return 38;
			if(compile_pow10<M,36>()<=value)
				return 37;
			}
			if(compile_pow10<M,35>()<=value)
				return 36;
			if(compile_pow10<M,34>()<=value)
				return 35;
			if(compile_pow10<M,33>()<=value)
				return 34;
			if(compile_pow10<M,32>()<=value)
				return 33;
			if(compile_pow10<M,31>()<=value)
				return 32;
			if(compile_pow10<M,30>()<=value)
				return 31;
			if(compile_pow10<M,29>()<=value)
				return 30;
			if(compile_pow10<M,28>()<=value)
				return 29;
			if(compile_pow10<M,27>()<=value)
				return 28;
			if(compile_pow10<M,26>()<=value)
				return 27;
			if(compile_pow10<M,25>()<=value)
				return 26;
			if(compile_pow10<M,24>()<=value)
				return 25;
			if(compile_pow10<M,23>()<=value)
				return 24;
			if(compile_pow10<M,22>()<=value)
				return 23;
			if(compile_pow10<M,21>()<=value)
				return 22;
			if(compile_pow10<M,20>()<=value)
				return 21;
		}
		if constexpr(7<sizeof(U))
		{
			if constexpr(8<sizeof(U)||!ryu_mode)
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

template<my_integral T>
inline constexpr my_make_unsigned_t<T> cal_int_max()
{
	my_make_unsigned_t<T> n{};
	--n;
	if constexpr(my_signed_integral<T>)
		n>>=1;
	return n;
}
template<my_integral T>
inline constexpr T get_int_max()
{
	constexpr T v{static_cast<T>(cal_int_max<T>())};
	return v;
}
template<my_integral T>
inline constexpr auto get_int_max_unsigned()
{
	constexpr my_make_unsigned_t<std::remove_cvref_t<T>> v{cal_int_max<std::remove_cvref_t<T>>()};
	return v;
}
template<my_integral T,char8_t base = 10>
inline constexpr std::size_t cal_max_int_size()
{
	std::size_t i{};
	auto n(get_int_max_unsigned<T>());
	for(;n;++i)
		n/=base;
	return i;
}

static_assert(cal_max_int_size<std::uint64_t,10>()==20);
static_assert(cal_max_int_size<std::uint32_t,10>()==10);
}