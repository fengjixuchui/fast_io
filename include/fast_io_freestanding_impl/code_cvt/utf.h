#pragma once

#include"utf_util_table.h"

#ifdef __SSE__
#include <emmintrin.h>
#include <immintrin.h>
#include <xmmintrin.h>
#endif
/*
CppCon 2018: Bob Steagall “Fast Conversion From UTF-8 with C++, DFAs, and SSE Intrinsics”

https://www.youtube.com/watch?v=5FQ87-Ecb-A
https://github.com/BobSteagall/utf_utils/blob/master/src/utf_utils.cpp

*/

namespace fast_io
{

namespace details::utf
{
#ifdef __SSE__
template<std::integral T,std::integral U>
requires (sizeof(T)==1)&&(sizeof(U)==2||sizeof(U)==4)
inline void convert_ascii_with_sse(T*& pSrc, U*& pDst) noexcept
{
	uint16_t mask;
	if constexpr(sizeof(U)==2)
	{
    	__m128i     chunk, half;

		chunk = _mm_loadu_si128((__m128i const*) pSrc);     //- Load the register with 8-bit bytes
		mask  = _mm_movemask_epi8(chunk);                   //- Determine which octets have high bit set

		half = _mm_unpacklo_epi8(chunk, _mm_set1_epi8(0));  //- Unpack lower half into 16-bit words
		_mm_storeu_si128((__m128i*) pDst, half);            //- Write to memory

		half = _mm_unpackhi_epi8(chunk, _mm_set1_epi8(0));  //- Unpack upper half into 16-bit words
		_mm_storeu_si128((__m128i*) (pDst + 8), half);      //- Write to memory

	}
	else
	{
		__m128i     chunk, half, qrtr, zero;

		zero  = _mm_set1_epi8(0);                           //- Zero out the interleave register
		chunk = _mm_loadu_si128((__m128i const*) pSrc);     //- Load a register with 8-bit bytes
		mask  = _mm_movemask_epi8(chunk);                   //- Determine which octets have high bit set

		half = _mm_unpacklo_epi8(chunk, zero);              //- Unpack bytes 0-7 into 16-bit words
		qrtr = _mm_unpacklo_epi16(half, zero);              //- Unpack words 0-3 into 32-bit dwords
		_mm_storeu_si128((__m128i*) pDst, qrtr);            //- Write to memory
		qrtr = _mm_unpackhi_epi16(half, zero);              //- Unpack words 4-7 into 32-bit dwords
		_mm_storeu_si128((__m128i*) (pDst + 4), qrtr);      //- Write to memory

		half = _mm_unpackhi_epi8(chunk, zero);              //- Unpack bytes 8-15 into 16-bit words
		qrtr = _mm_unpacklo_epi16(half, zero);              //- Unpack words 8-11 into 32-bit dwords
		_mm_storeu_si128((__m128i*) (pDst + 8), qrtr);      //- Write to memory
		qrtr = _mm_unpackhi_epi16(half, zero);              //- Unpack words 12-15 into 32-bit dwords
		_mm_storeu_si128((__m128i*) (pDst + 12), qrtr);     //- Write to memory
	}
	auto const incr{std::countr_zero(mask)};
	pSrc += incr;
	pDst += incr;
}
#endif

template<std::integral T>
requires (sizeof(T)==2||sizeof(T)==1)
inline constexpr std::uint32_t get_code_units(char32_t cdpt, T*& pDst) noexcept
{
	if constexpr(sizeof(T)==2)
	{
		if (cdpt < 0x10000)
		{
			*pDst = static_cast<T>(cdpt);
			++pDst;
			return 1;
		}
		else
		{
			*pDst = static_cast<T>(0xD7C0 + (cdpt >> 10));
			*++pDst = static_cast<T>(0xDC00 + (cdpt & 0x3FF));
			++pDst;
			return 2;
		}
	}
	else
	{
		    if (cdpt <= 0x7F)
			{
				*pDst = static_cast<T>(cdpt);
				++pDst;
				return 1;
			}
			else if (cdpt <= 0x7FF)
			{
				*pDst = static_cast<T>(0xC0 | ((cdpt >> 6) & 0x1F));
				++pDst;
				*pDst = static_cast<T>(0x80 | (cdpt        & 0x3F));
				++pDst;
				return 2;
			}
			else if (cdpt <= 0xFFFF)
			{
				*pDst = static_cast<T>(0xE0 | ((cdpt >> 12) & 0x0F));
				++pDst;
				*pDst = static_cast<T>(0x80 | ((cdpt >> 6)  & 0x3F));
				++pDst;
				*pDst= static_cast<T>(0x80 | (cdpt         & 0x3F));
				++pDst;
				return 3;
			}
			else if (cdpt <= 0x10FFFF)
			{
				*pDst= static_cast<T>(0xF0 | ((cdpt >> 18) & 0x07));
				++pDst;
				*pDst = static_cast<T>(0x80 | ((cdpt >> 12) & 0x3F));
				++pDst;
				*pDst = static_cast<T>(0x80 | ((cdpt >> 6)  & 0x3F));
				++pDst;
				*pDst = static_cast<T>(0x80 | (cdpt         & 0x3F));
				++pDst;
				return 4;
			}
			return 0;

	}

}


template<std::input_iterator input>
constexpr inline uint32_t advance_with_big_table(input& pSrc, input pSrcEnd, char32_t& cdpt) noexcept
{
    std::array<char8_t,2> const info{utf_util_table<>::first_unit_info[*pSrc]};
    cdpt = info.front();                                //- From it, get the initial code point value
    std::int32_t curr{info.back()};                                 //- From it, get the second state
    for(++pSrc;12<curr;)
    {
	if (pSrc < pSrcEnd)[[likely]]
	{
	    auto const unit{*pSrc};
	    ++pSrc;                                 //- Cache the current code unit
	    cdpt = (cdpt << 6) | (unit & 0x3F);             //- Adjust code point with continuation bits
	    curr = utf_util_table<>::transitions[curr + utf_util_table<>::octet_category[unit]];
		//- Look up the next state
	}
	else
	    return 12;
    }
    return curr;
}






}

/*

Todo in the future, detect EBCDIC compiler for code_cvt

Assume little endian first until I create a good interface
*/

template<std::contiguous_iterator from_iter,std::contiguous_iterator to_iter>
requires (std::integral<std::iter_value_t<from_iter>>&&sizeof(std::iter_value_t<from_iter>)==1&&
sizeof(std::iter_value_t<to_iter>)==2&&std::unsigned_integral<std::iter_value_t<to_iter>>)
inline constexpr to_iter code_cvt_from_utf8_to_utf16(from_iter p_src_iter,from_iter p_src_end,to_iter p_dst)
{
	auto pSrc(std::to_address(p_src_iter));
	auto pSrcEnd(std::to_address(p_src_end));
	auto pDst(std::to_address(p_dst));
    char32_t cdpt;
#ifdef __SSE__
#if __cpp_lib_is_constant_evaluated>=201811L
	if (!std::is_constant_evaluated())
	{
		while (pSrc + sizeof(__m128i)< pSrcEnd)
		{
		if (*pSrc < 0x80)
			details::utf::convert_ascii_with_sse(pSrc, pDst);
		else
		{
			if (details::utf::advance_with_big_table(pSrc, pSrcEnd, cdpt) != 12)[[likely]]
				details::utf::get_code_units(cdpt, pDst);
			else
				throw std::range_error("illegal utf8");
		}
		}
	}
#endif
#endif
    while (pSrc < pSrcEnd)
    {
	if (*pSrc < 0x80)
	{
	    *pDst = *pSrc;
		++pDst;
		++pSrc;
	}
	else
	{
	    if (details::utf::advance_with_big_table(pSrc, pSrcEnd, cdpt) != 12)[[likely]]
			details::utf::get_code_units(cdpt, pDst);
	    else
			throw std::range_error("illegal utf8");
	}
    }
    return (pDst-std::to_address(p_dst))+p_dst;
}
template<output_stream output,std::integral ch_type>
requires ((std::same_as<typename output::char_type,char16_t>||
std::same_as<typename output::char_type,wchar_t>||
std::same_as<typename output::char_type,char32_t>)&&
(std::same_as<ch_type,char8_t>||
std::same_as<ch_type,char>))
inline constexpr void print_define(output& out,manip::code_cvt<std::basic_string_view<ch_type> const> view)
{
	if constexpr(buffer_output_stream<output>)
	{
		auto eptr{oreserve(out,view.reference.size())};
		if constexpr(std::is_pointer_v<std::remove_reference_t<decltype(eptr)>>)
		{
			if(eptr)[[likely]]
			{
				orelease(out,eptr-code_cvt_from_utf8_to_utf16(view.reference.data(),
					view.reference.data()+view.reference.size(),eptr-view.reference.size()));
				return;
			}
		}
		else
		{
			orelease(out,eptr-code_cvt_from_utf8_to_utf16(view.reference.data(),
				view.reference.data()+view.reference.size(),eptr-view.reference.size()));
			return;
		}
	}
	if(view.reference.size()<=512)[[likely]]
	{
		std::array<typename output::char_type,512> buffer;
		write(out,buffer.data(),code_cvt_from_utf8_to_utf16(view.reference.data(),view.reference.data()+view.reference.size(),buffer.data()));
	}
	else
	{
		fast_io::details::temp_unique_arr_ptr<typename output::char_type> bf(view.reference.size());
		write(out,bf.ptr,code_cvt_from_utf8_to_utf16(view.reference.data(),view.reference.data()+view.reference.size(),bf.ptr));
	}
}

}
