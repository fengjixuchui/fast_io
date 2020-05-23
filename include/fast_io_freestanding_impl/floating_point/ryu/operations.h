#pragma once

namespace fast_io::details::ryu
{

// It seems to be slightly faster to avoid uint128_t here, although the
// generated code for uint128_t looks slightly nicer.
constexpr inline std::uint32_t mul_shift_32(std::uint32_t const m, std::uint64_t const factor, std::int32_t const shift)
{
  // The casts here help MSVC to avoid calls to the __allmul library
  // function.
	std::uint32_t const factor_low{static_cast<std::uint32_t>(factor)};
	std::uint32_t const factor_high{static_cast<std::uint32_t>(factor >> 32)};
	std::uint64_t const bits0{static_cast<std::uint64_t>(m) * factor_low};
	std::uint64_t const bits1{static_cast<std::uint64_t>(m) * factor_high};

	if constexpr(sizeof(std::uintptr_t)<8)
	{
		// On 32-bit platforms we can avoid a 64-bit shift-right since we only
		// need the upper 32 bits of the result and the shift value is > 32.
		std::uint32_t const bits0_high(static_cast<std::uint32_t>(bits0 >> 32));
		std::uint32_t bits1_low(static_cast<std::uint32_t>(bits1));
		std::uint32_t bits1_high(static_cast<std::uint32_t>(bits1 >> 32));
		bits1_low += bits0_high;
		bits1_high += (bits1_low < bits0_high);
		std::int32_t const s(shift - 32);
		return (bits1_high << (32 - s)) | (bits1_low >> s);
 	}
	else
	{
		std::uint64_t const sum((bits0 >> 32) + bits1);
		std::uint64_t const shifted_sum(sum >> (shift - 32));
		return static_cast<std::uint32_t>(shifted_sum);
	}
}

constexpr inline std::uint32_t mul_pow5_inv_div_pow2(std::uint32_t const m, std::uint32_t const q, std::int32_t const j)
{
	return mul_shift_32(m, pow5<float,true>::inv_split[q], j);
}

constexpr inline std::uint32_t mul_pow5_div_pow2(std::uint32_t const m, std::uint32_t const i, std::int32_t const j)
{
	return mul_shift_32(m, pow5<float,true>::split[i], j);
}
}