#pragma once

#ifdef __x86_64__
//requires -maes -msse2
#include <immintrin.h>  // for intrinsics for sha1 function

namespace fast_io
{


namespace details::sha1
{
namespace
{
//from https://github.com/vog/sha1/blob/master/sha1.cpp
inline constexpr std::uint32_t blk(std::array<std::uint32_t,16> &block,std::size_t const i)
{
	return std::rotl(block[(i+13)&15] ^ block[(i+8)&15] ^ block[(i+2)&15] ^ block[i], 1);
}

inline constexpr void R0(std::array<std::uint32_t,16> &block, std::uint32_t const v, std::uint32_t &w, std::uint32_t const x, std::uint32_t const y, std::uint32_t &z, const size_t i)
{
	z += ((w&(x^y))^y) + block[i] + 0x5a827999 + std::rotl(v, 5);
	w = std::rotl(w, 30);
}


inline constexpr void R1(std::array<std::uint32_t,16> &block, std::uint32_t const v, std::uint32_t &w, std::uint32_t const x, std::uint32_t const y, std::uint32_t &z, const size_t i)
{
	block[i] = blk(block, i);
	z += ((w&(x^y))^y) + block[i] + 0x5a827999 + std::rotl(v, 5);
	w = std::rotl(w, 30);
}


inline constexpr void R2(std::array<std::uint32_t,16> &block, std::uint32_t const v, std::uint32_t &w, std::uint32_t const x, std::uint32_t const y, std::uint32_t &z, const size_t i)
{
	block[i] = blk(block, i);
	z += (w^x^y) + block[i] + 0x6ed9eba1 + std::rotl(v, 5);
	w = std::rotl(w, 30);
}


inline constexpr void R3(std::array<std::uint32_t,16> &block, std::uint32_t const v, std::uint32_t &w, std::uint32_t const x, std::uint32_t const y, std::uint32_t &z, const size_t i)
{
	block[i] = blk(block, i);
	z += (((w|x)&y)|(w&x)) + block[i] + 0x8f1bbcdc + std::rotl(v, 5);
	w = std::rotl(w, 30);
}


inline constexpr void R4(std::array<std::uint32_t,16> &block, std::uint32_t const v, std::uint32_t &w, std::uint32_t const x, std::uint32_t const y, std::uint32_t &z, const size_t i)
{
	block[i] = blk(block, i);
	z += (w^x^y) + block[i] + 0xca62c1d6 + std::rotl(v, 5);
	w = std::rotl(w, 30);
}


inline constexpr void transform(std::span<std::uint32_t,5> digest, std::array<std::uint32_t,16> &block)
{
	/* Copy digest[] to working vars */
	std::uint32_t a(digest.front());
	std::uint32_t b(digest[1]);
	std::uint32_t c(digest[2]);
	std::uint32_t d(digest[3]);
	std::uint32_t e(digest.back());

	/* 4 rounds of 20 operations each. Loop unrolled. */
	R0(block, a, b, c, d, e,  0);
	R0(block, e, a, b, c, d,  1);
	R0(block, d, e, a, b, c,  2);
	R0(block, c, d, e, a, b,  3);
	R0(block, b, c, d, e, a,  4);
	R0(block, a, b, c, d, e,  5);
	R0(block, e, a, b, c, d,  6);
	R0(block, d, e, a, b, c,  7);
	R0(block, c, d, e, a, b,  8);
	R0(block, b, c, d, e, a,  9);
	R0(block, a, b, c, d, e, 10);
	R0(block, e, a, b, c, d, 11);
	R0(block, d, e, a, b, c, 12);
	R0(block, c, d, e, a, b, 13);
	R0(block, b, c, d, e, a, 14);
	R0(block, a, b, c, d, e, 15);
	R1(block, e, a, b, c, d,  0);
	R1(block, d, e, a, b, c,  1);
	R1(block, c, d, e, a, b,  2);
	R1(block, b, c, d, e, a,  3);
	R2(block, a, b, c, d, e,  4);
	R2(block, e, a, b, c, d,  5);
	R2(block, d, e, a, b, c,  6);
	R2(block, c, d, e, a, b,  7);
	R2(block, b, c, d, e, a,  8);
	R2(block, a, b, c, d, e,  9);
	R2(block, e, a, b, c, d, 10);
	R2(block, d, e, a, b, c, 11);
	R2(block, c, d, e, a, b, 12);
	R2(block, b, c, d, e, a, 13);
	R2(block, a, b, c, d, e, 14);
	R2(block, e, a, b, c, d, 15);
	R2(block, d, e, a, b, c,  0);
	R2(block, c, d, e, a, b,  1);
	R2(block, b, c, d, e, a,  2);
	R2(block, a, b, c, d, e,  3);
	R2(block, e, a, b, c, d,  4);
	R2(block, d, e, a, b, c,  5);
	R2(block, c, d, e, a, b,  6);
	R2(block, b, c, d, e, a,  7);
	R3(block, a, b, c, d, e,  8);
	R3(block, e, a, b, c, d,  9);
	R3(block, d, e, a, b, c, 10);
	R3(block, c, d, e, a, b, 11);
	R3(block, b, c, d, e, a, 12);
	R3(block, a, b, c, d, e, 13);
	R3(block, e, a, b, c, d, 14);
	R3(block, d, e, a, b, c, 15);
	R3(block, c, d, e, a, b,  0);
	R3(block, b, c, d, e, a,  1);
	R3(block, a, b, c, d, e,  2);
	R3(block, e, a, b, c, d,  3);
	R3(block, d, e, a, b, c,  4);
	R3(block, c, d, e, a, b,  5);
	R3(block, b, c, d, e, a,  6);
	R3(block, a, b, c, d, e,  7);
	R3(block, e, a, b, c, d,  8);
	R3(block, d, e, a, b, c,  9);
	R3(block, c, d, e, a, b, 10);
	R3(block, b, c, d, e, a, 11);
	R4(block, a, b, c, d, e, 12);
	R4(block, e, a, b, c, d, 13);
	R4(block, d, e, a, b, c, 14);
	R4(block, c, d, e, a, b, 15);
	R4(block, b, c, d, e, a,  0);
	R4(block, a, b, c, d, e,  1);
	R4(block, e, a, b, c, d,  2);
	R4(block, d, e, a, b, c,  3);
	R4(block, c, d, e, a, b,  4);
	R4(block, b, c, d, e, a,  5);
	R4(block, a, b, c, d, e,  6);
	R4(block, e, a, b, c, d,  7);
	R4(block, d, e, a, b, c,  8);
	R4(block, c, d, e, a, b,  9);
	R4(block, b, c, d, e, a, 10);
	R4(block, a, b, c, d, e, 11);
	R4(block, e, a, b, c, d, 12);
	R4(block, d, e, a, b, c, 13);
	R4(block, c, d, e, a, b, 14);
	R4(block, b, c, d, e, a, 15);

	/* Add the working vars back into digest[] */
	digest[0] += a;
	digest[1] += b;
	digest[2] += c;
	digest[3] += d;
	digest[4] += e;
}

}
}


class sha1_function
{
public:
	using digest_type = std::array<std::uint32_t,5>;
	static inline constexpr digest_type digest_initial_value{0x67452301,0xefcdab89,0x98badcfe,0x10325476,0xc3d2e1f0};
	static inline constexpr std::size_t block_size{64};
	void operator()(std::span<std::uint32_t,5> state,std::span<std::byte const,64> blocks)
	{
#ifdef __SSE4_1__
//https://stackoverflow.com/questions/21107350/how-can-i-access-sha-intrinsic
		__m128i ABCD, ABCD_SAVE, E0, E0_SAVE, E1;
		__m128i MASK, MSG0, MSG1, MSG2, MSG3;
//Clearly it is a violation of strict aliasing rule.
//However, the library will mark them as mayalias. We can safely use them.

		// Load initial values
		ABCD = _mm_loadu_si128((__m128i*) state.data());
		E0 = _mm_set_epi32(state[4], 0, 0, 0);
		ABCD = _mm_shuffle_epi32(ABCD, 0x1B);
		MASK = _mm_set_epi64x(0x0001020304050607ULL, 0x08090a0b0c0d0e0fULL);

		// Save current hash
		ABCD_SAVE = ABCD;
		E0_SAVE = E0;

		// Rounds 0-3
		MSG0 = _mm_loadu_si128((__m128i*) blocks.data());
		MSG0 = _mm_shuffle_epi8(MSG0, MASK);
		E0 = _mm_add_epi32(E0, MSG0);
		E1 = ABCD;
		ABCD = _mm_sha1rnds4_epu32(ABCD, E0, 0);

		// Rounds 4-7
		MSG1 = _mm_loadu_si128((__m128i*) (blocks.data()+16));
		MSG1 = _mm_shuffle_epi8(MSG1, MASK);
		E1 = _mm_sha1nexte_epu32(E1, MSG1);
		E0 = ABCD;
		ABCD = _mm_sha1rnds4_epu32(ABCD, E1, 0);
		MSG0 = _mm_sha1msg1_epu32(MSG0, MSG1);

		// Rounds 8-11
		MSG2 = _mm_loadu_si128((__m128i*) (blocks.data()+32));
		MSG2 = _mm_shuffle_epi8(MSG2, MASK);
		E0 = _mm_sha1nexte_epu32(E0, MSG2);
		E1 = ABCD;
		ABCD = _mm_sha1rnds4_epu32(ABCD, E0, 0);
		MSG1 = _mm_sha1msg1_epu32(MSG1, MSG2);
		MSG0 = _mm_xor_si128(MSG0, MSG2);

		// Rounds 12-15
		MSG3 = _mm_loadu_si128((__m128i*) (blocks.data()+48));
		MSG3 = _mm_shuffle_epi8(MSG3, MASK);
		E1 = _mm_sha1nexte_epu32(E1, MSG3);
		E0 = ABCD;
		MSG0 = _mm_sha1msg2_epu32(MSG0, MSG3);
		ABCD = _mm_sha1rnds4_epu32(ABCD, E1, 0);
		MSG2 = _mm_sha1msg1_epu32(MSG2, MSG3);
		MSG1 = _mm_xor_si128(MSG1, MSG3);

		// Rounds 16-19
		E0 = _mm_sha1nexte_epu32(E0, MSG0);
		E1 = ABCD;
		MSG1 = _mm_sha1msg2_epu32(MSG1, MSG0);
		ABCD = _mm_sha1rnds4_epu32(ABCD, E0, 0);
		MSG3 = _mm_sha1msg1_epu32(MSG3, MSG0);
		MSG2 = _mm_xor_si128(MSG2, MSG0);

		// Rounds 20-23
		E1 = _mm_sha1nexte_epu32(E1, MSG1);
		E0 = ABCD;
		MSG2 = _mm_sha1msg2_epu32(MSG2, MSG1);
		ABCD = _mm_sha1rnds4_epu32(ABCD, E1, 1);
		MSG0 = _mm_sha1msg1_epu32(MSG0, MSG1);
		MSG3 = _mm_xor_si128(MSG3, MSG1);

		// Rounds 24-27
		E0 = _mm_sha1nexte_epu32(E0, MSG2);
		E1 = ABCD;
		MSG3 = _mm_sha1msg2_epu32(MSG3, MSG2);
		ABCD = _mm_sha1rnds4_epu32(ABCD, E0, 1);
		MSG1 = _mm_sha1msg1_epu32(MSG1, MSG2);
		MSG0 = _mm_xor_si128(MSG0, MSG2);

		// Rounds 28-31
		E1 = _mm_sha1nexte_epu32(E1, MSG3);
		E0 = ABCD;
		MSG0 = _mm_sha1msg2_epu32(MSG0, MSG3);
		ABCD = _mm_sha1rnds4_epu32(ABCD, E1, 1);
		MSG2 = _mm_sha1msg1_epu32(MSG2, MSG3);
		MSG1 = _mm_xor_si128(MSG1, MSG3);

		// Rounds 32-35
		E0 = _mm_sha1nexte_epu32(E0, MSG0);
		E1 = ABCD;
		MSG1 = _mm_sha1msg2_epu32(MSG1, MSG0);
		ABCD = _mm_sha1rnds4_epu32(ABCD, E0, 1);
		MSG3 = _mm_sha1msg1_epu32(MSG3, MSG0);
		MSG2 = _mm_xor_si128(MSG2, MSG0);

		// Rounds 36-39
		E1 = _mm_sha1nexte_epu32(E1, MSG1);
		E0 = ABCD;
		MSG2 = _mm_sha1msg2_epu32(MSG2, MSG1);
		ABCD = _mm_sha1rnds4_epu32(ABCD, E1, 1);
		MSG0 = _mm_sha1msg1_epu32(MSG0, MSG1);
		MSG3 = _mm_xor_si128(MSG3, MSG1);

		// Rounds 40-43
		E0 = _mm_sha1nexte_epu32(E0, MSG2);
		E1 = ABCD;
		MSG3 = _mm_sha1msg2_epu32(MSG3, MSG2);
		ABCD = _mm_sha1rnds4_epu32(ABCD, E0, 2);
		MSG1 = _mm_sha1msg1_epu32(MSG1, MSG2);
		MSG0 = _mm_xor_si128(MSG0, MSG2);

		// Rounds 44-47
		E1 = _mm_sha1nexte_epu32(E1, MSG3);
		E0 = ABCD;
		MSG0 = _mm_sha1msg2_epu32(MSG0, MSG3);
		ABCD = _mm_sha1rnds4_epu32(ABCD, E1, 2);
		MSG2 = _mm_sha1msg1_epu32(MSG2, MSG3);
		MSG1 = _mm_xor_si128(MSG1, MSG3);

		// Rounds 48-51
		E0 = _mm_sha1nexte_epu32(E0, MSG0);
		E1 = ABCD;
		MSG1 = _mm_sha1msg2_epu32(MSG1, MSG0);
		ABCD = _mm_sha1rnds4_epu32(ABCD, E0, 2);
		MSG3 = _mm_sha1msg1_epu32(MSG3, MSG0);
		MSG2 = _mm_xor_si128(MSG2, MSG0);

		// Rounds 52-55
		E1 = _mm_sha1nexte_epu32(E1, MSG1);
		E0 = ABCD;
		MSG2 = _mm_sha1msg2_epu32(MSG2, MSG1);
		ABCD = _mm_sha1rnds4_epu32(ABCD, E1, 2);
		MSG0 = _mm_sha1msg1_epu32(MSG0, MSG1);
		MSG3 = _mm_xor_si128(MSG3, MSG1);

		// Rounds 56-59
		E0 = _mm_sha1nexte_epu32(E0, MSG2);
		E1 = ABCD;
		MSG3 = _mm_sha1msg2_epu32(MSG3, MSG2);
		ABCD = _mm_sha1rnds4_epu32(ABCD, E0, 2);
		MSG1 = _mm_sha1msg1_epu32(MSG1, MSG2);
		MSG0 = _mm_xor_si128(MSG0, MSG2);

		// Rounds 60-63
		E1 = _mm_sha1nexte_epu32(E1, MSG3);
		E0 = ABCD;
		MSG0 = _mm_sha1msg2_epu32(MSG0, MSG3);
		ABCD = _mm_sha1rnds4_epu32(ABCD, E1, 3);
		MSG2 = _mm_sha1msg1_epu32(MSG2, MSG3);
		MSG1 = _mm_xor_si128(MSG1, MSG3);

		// Rounds 64-67
		E0 = _mm_sha1nexte_epu32(E0, MSG0);
		E1 = ABCD;
		MSG1 = _mm_sha1msg2_epu32(MSG1, MSG0);
		ABCD = _mm_sha1rnds4_epu32(ABCD, E0, 3);
		MSG3 = _mm_sha1msg1_epu32(MSG3, MSG0);
		MSG2 = _mm_xor_si128(MSG2, MSG0);

		// Rounds 68-71
		E1 = _mm_sha1nexte_epu32(E1, MSG1);
		E0 = ABCD;
		MSG2 = _mm_sha1msg2_epu32(MSG2, MSG1);
		ABCD = _mm_sha1rnds4_epu32(ABCD, E1, 3);
		MSG3 = _mm_xor_si128(MSG3, MSG1);

		// Rounds 72-75
		E0 = _mm_sha1nexte_epu32(E0, MSG2);
		E1 = ABCD;
		MSG3 = _mm_sha1msg2_epu32(MSG3, MSG2);
		ABCD = _mm_sha1rnds4_epu32(ABCD, E0, 3);

		// Rounds 76-79
		E1 = _mm_sha1nexte_epu32(E1, MSG3);
		E0 = ABCD;
		ABCD = _mm_sha1rnds4_epu32(ABCD, E1, 3);

		// Add values back to state
		E0 = _mm_sha1nexte_epu32(E0, E0_SAVE);
		ABCD = _mm_add_epi32(ABCD, ABCD_SAVE);

		// Save state
		ABCD = _mm_shuffle_epi32(ABCD, 0x1B);
		_mm_storeu_si128((__m128i*) state.data(), ABCD);
		state[4] = _mm_extract_epi32(E0, 3);
#else

		std::array<std::uint32_t,16> tblocks;
		memcpy(tblocks.data(),blocks.data(),block_size);
		for(auto& e : tblocks)
			e=details::byte_swap(e);
		details::sha1::transform(state,tblocks);
#endif
	}
};

}

#endif