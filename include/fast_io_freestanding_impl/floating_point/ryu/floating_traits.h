#pragma once

namespace fast_io::details::ryu
{

template<std::floating_point T>
struct floating_traits
{
};


template<>	
struct floating_traits<float>
{
	using mantissa_type = std::uint32_t;
	using exponent_type = std::uint32_t;
	static inline constexpr exponent_type exponent_bits = 8;
	static inline constexpr mantissa_type mantissa_bits = sizeof(float)*8-1-exponent_bits;
	static inline constexpr exponent_type exponent_max = (static_cast<exponent_type>(1)<<exponent_bits)-1;
	static inline constexpr exponent_type bias = (static_cast<exponent_type>(1)<<(exponent_bits - 1)) - 1;
//	static inline constexpr exponent_type pow5_inv_bitcount= 61;
	static inline constexpr exponent_type pow5_bitcount= 61;
	static inline constexpr exponent_type floor_log5 = 9;
	static inline constexpr exponent_type bound = 31;//ryu to do. use a tigher bound
	static inline constexpr exponent_type digits10=8;
	static inline constexpr mantissa_type carry10=0x989680;
};

template<>	
struct floating_traits<double>
{
	using mantissa_type = std::uint64_t;
	using exponent_type = std::uint32_t;
	static inline constexpr exponent_type exponent_bits = 11;
	static inline constexpr mantissa_type mantissa_bits = sizeof(double)*8-1-exponent_bits;
	static inline constexpr exponent_type exponent_max = (static_cast<exponent_type>(1)<<exponent_bits)-1;
	static inline constexpr exponent_type bias = (static_cast<exponent_type>(1)<<(exponent_bits - 1)) - 1;
//	static inline constexpr exponent_type pow5_inv_bitcount= 125;
	static inline constexpr exponent_type pow5_bitcount= 125;
	static inline constexpr exponent_type floor_log5 = 21;
	static inline constexpr exponent_type bound = 63;//ryu to do. use a tigher bound
	static inline constexpr exponent_type digits10=17;
	static inline constexpr mantissa_type carry10=0x2386F26FC10000;
	static inline constexpr int32_t minimum_exp=-323;
	static inline constexpr int32_t maximum_exp=309;
};

template<>	
struct floating_traits<long double>
{
	using mantissa_type = uint128_t;
	using exponent_type = std::uint32_t;
	static inline constexpr exponent_type exponent_bits = 17;
	static inline constexpr std::uint32_t mantissa_bits = sizeof(long double)*8-1-exponent_bits;
	static inline constexpr exponent_type exponent_max = (static_cast<exponent_type>(1)<<exponent_bits)-1;
	static inline constexpr exponent_type bias = (static_cast<exponent_type>(1)<<(exponent_bits - 1)) - 1;
//	static inline constexpr std::size_t pow5_inv_bitcount= 249;
	static inline constexpr std::size_t pow5_bitcount= 249;
	static inline constexpr exponent_type floor_log5 = 55;
	static inline constexpr exponent_type bound = 127;//ryu to do. use a tigher bound
	static inline constexpr exponent_type digits10=21;
//	static inline constexpr mantissa_type carry10=10000000000000000ull;
};

}