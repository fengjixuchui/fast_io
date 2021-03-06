#pragma once

namespace fast_io
{

namespace details
{

template<char8_t ch,std::integral char_type>
constexpr char_type get_char_with_type() noexcept
{
	if constexpr(ch==u8'+')
	{
		if constexpr(std::same_as<std::remove_cvref_t<char_type>,char>)
			return '+';
		else if constexpr(std::same_as<std::remove_cvref_t<char_type>,wchar_t>)
			return L'+';
		else
			return u8'+';
	}
	else if constexpr(ch==u8'-')
	{
		if constexpr(std::same_as<std::remove_cvref_t<char_type>,char>)
			return '-';
		else if constexpr(std::same_as<std::remove_cvref_t<char_type>,wchar_t>)
			return L'-';
		else
			return u8'-';
	}
	else if constexpr(ch==u8'0')
	{
		if constexpr(std::same_as<std::remove_cvref_t<char_type>,char>)
			return '0';
		else if constexpr(std::same_as<std::remove_cvref_t<char_type>,wchar_t>)
			return L'0';
		else
			return u8'0';
	}
}


struct simd_parse_result
{
	std::size_t digits;
	fast_io::parse_code code;
};

#if defined(__SSE4_1__) && defined(__x86_64__)

template<bool char_execharset>
inline std::uint32_t detect_length(char unsigned const* buffer) noexcept
{
	constexpr char8_t zero_constant{char_execharset?static_cast<char8_t>('0'):u8'0'};
	constexpr char8_t v176_constant{zero_constant+128};
#if (defined(__GNUC__) || defined(__clang__)) && !defined(__INTEL_COMPILER)
	using namespace fast_io::intrinsics;
	x86_64_v16qu chunk;
	__builtin_memcpy(__builtin_addressof(chunk),buffer,16);
	x86_64_v16qu const v176{v176_constant,v176_constant,v176_constant,v176_constant,v176_constant,v176_constant,v176_constant,v176_constant,
				v176_constant,v176_constant,v176_constant,v176_constant,v176_constant,v176_constant,v176_constant,v176_constant};
	x86_64_v16qu const t0{chunk-v176};
	x86_64_v16qs const minus118{-118, -118, -118, -118, -118, -118, -118, -118, -118, -118, -118, -118, -118, -118, -118, -118};
	x86_64_v16qs const mask{(x86_64_v16qs)t0<minus118};
	std::uint16_t v{static_cast<std::uint16_t>(__builtin_ia32_pmovmskb128((x86_64_v16qi)mask))};
#else
	__m128i chunk = _mm_loadu_si128(reinterpret_cast<__m128i const*>(buffer));
	__m128i const t0 = _mm_sub_epi8(chunk, _mm_set1_epi8(v176_constant));
	__m128i const mask = _mm_cmplt_epi8(t0, _mm_set1_epi8(-118));
	std::uint16_t v{static_cast<std::uint16_t>(_mm_movemask_epi8(mask))};
#endif
	return std::countr_one(v);
}

template<bool char_execharset>
#if __has_cpp_attribute(gnu::cold)
[[gnu::cold]]
#endif
inline std::size_t sse_skip_long_overflow_digits(char unsigned const* buffer,char unsigned const* buffer_end) noexcept
{
	auto it{buffer+16};
	for(;16<=buffer_end-it;it+=16)
	{
		auto new_length{detect_length<char_execharset>(it)};
		if(new_length!=16)
			return static_cast<std::size_t>(it-buffer+new_length);
	};
	if(buffer_end==it)
		return static_cast<std::size_t>(it-buffer);
	return static_cast<std::size_t>(buffer_end-buffer+detect_length<char_execharset>(buffer_end-16));
}


inline constexpr char unsigned sse_shift_table[32]{0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};

template<bool char_execharset,bool less_than_64_bits>
#if __has_cpp_attribute(gnu::hot)
[[gnu::hot]]
#endif
inline simd_parse_result sse_parse(char unsigned const* buffer,char unsigned const* buffer_end,std::uint64_t &res,bool has_zero) noexcept
{
	constexpr char8_t zero_constant{char_execharset?static_cast<char8_t>('0'):u8'0'};
	constexpr char8_t v176_constant{zero_constant+128};
	using fast_io::parse_code;
#if (defined(__GNUC__) || defined(__clang__)) && !defined(__INTEL_COMPILER)
	using namespace fast_io::intrinsics;
	x86_64_v16qu chunk;
	__builtin_memcpy(__builtin_addressof(chunk),buffer,16);
	x86_64_v16qu const v176{v176_constant,v176_constant,v176_constant,v176_constant,v176_constant,v176_constant,v176_constant,v176_constant,
				v176_constant,v176_constant,v176_constant,v176_constant,v176_constant,v176_constant,v176_constant,v176_constant};
	x86_64_v16qu const t0{chunk-v176};
	x86_64_v16qs const minus118{-118, -118, -118, -118, -118, -118, -118, -118, -118, -118, -118, -118, -118, -118, -118, -118};
	x86_64_v16qs const mask{(x86_64_v16qs)t0<minus118};
	std::uint16_t v{static_cast<std::uint16_t>(__builtin_ia32_pmovmskb128((x86_64_v16qi)mask))};
	std::uint32_t digits{static_cast<std::uint32_t>(std::countr_one(v))};
	if(digits==0)
		return {0,has_zero?(parse_code::ok):(parse_code::invalid)};
	x86_64_v16qu const zeros{zero_constant,zero_constant,zero_constant,zero_constant,zero_constant,zero_constant,zero_constant,zero_constant,
		zero_constant,zero_constant,zero_constant,zero_constant,zero_constant,zero_constant,zero_constant,zero_constant};
	chunk-=zeros;
	x86_64_v16qi shuffle_mask;
	__builtin_memcpy(__builtin_addressof(shuffle_mask),sse_shift_table+digits,sizeof(x86_64_v16qi));
	chunk=(x86_64_v16qu)__builtin_ia32_pshufb128((x86_64_v16qi)chunk,shuffle_mask);
	chunk=(x86_64_v16qu)__builtin_ia32_pmaddubsw128((x86_64_v16qi)chunk,x86_64_v16qi{10,1,10,1,10,1,10,1,10,1,10,1,10,1,10,1});
	chunk=(x86_64_v16qu)__builtin_ia32_pmaddwd128((x86_64_v8hi)chunk,x86_64_v8hi{100,1,100,1,100,1,100,1});
	chunk=(x86_64_v16qu)__builtin_ia32_packusdw128((x86_64_v4si)chunk,(x86_64_v4si)chunk);
	chunk=(x86_64_v16qu)__builtin_ia32_pmaddwd128((x86_64_v8hi)chunk,x86_64_v8hi{10000,1,10000,1,0,0,0,0});
	std::uint64_t chunk0;
	__builtin_memcpy(__builtin_addressof(chunk0),__builtin_addressof(chunk),sizeof(chunk0));
#else
	__m128i chunk = _mm_loadu_si128(reinterpret_cast<__m128i const*>(buffer));
	__m128i const t0 = _mm_sub_epi8(chunk, _mm_set1_epi8(v176_constant));
	__m128i const mask = _mm_cmplt_epi8(t0, _mm_set1_epi8(-118));
	std::uint16_t v{static_cast<std::uint16_t>(_mm_movemask_epi8(mask))};
	std::uint32_t digits{static_cast<std::uint32_t>(std::countr_one(v))};
	if(digits==0)
		return {0,has_zero?(parse_code::ok):(parse_code::invalid)};
	chunk = _mm_sub_epi8(chunk, _mm_set1_epi8(zero_constant));
	chunk = _mm_shuffle_epi8(chunk,_mm_loadu_si128(reinterpret_cast<__m128i const*>(sse_shift_table+digits)));
	chunk = _mm_maddubs_epi16(chunk, _mm_set_epi8(1,10,1,10,1,10,1,10,1,10,1,10,1,10,1,10));
	chunk = _mm_madd_epi16(chunk, _mm_set_epi16(1,100,1,100,1,100,1,100));
	chunk = _mm_packus_epi32(chunk, chunk);
	chunk = _mm_madd_epi16(chunk,_mm_set_epi16(0,0,0,0,1,10000,1,10000));
	std::uint64_t chunk0;
	std::memcpy(__builtin_addressof(chunk0),__builtin_addressof(chunk),sizeof(chunk0));
#endif
	std::uint64_t result{static_cast<std::uint64_t>(((chunk0 & 0xffffffff) * 100000000ULL) + (chunk0 >> 32))};
	if(digits==16)[[unlikely]]
	{
		if constexpr(less_than_64_bits)
		{
			//std::uint32_t can never have 16 digits
			return {sse_skip_long_overflow_digits<char_execharset>(buffer+16,buffer_end)+16,parse_code::overflow};
		}
		else
		{
			std::size_t digits1{detect_length<char_execharset>(buffer+16)};
//18446744073709551615 20 digits
			switch(digits1)
			{
			case 3:
			{
				res=result*1000ULL+static_cast<std::uint64_t>(buffer[16]-zero_constant)*100ULL+static_cast<std::uint64_t>(buffer[17]-zero_constant)*10ULL
				+static_cast<std::uint64_t>(buffer[18]-zero_constant);
				return {19,parse_code::ok};
			}
			case 2:
			{
				res=result*100+static_cast<std::uint64_t>(buffer[16]-zero_constant)*10ULL+static_cast<std::uint64_t>(buffer[17]-zero_constant);
				return {18,parse_code::ok};
			}
			case 1:
			{
				res=result*10+static_cast<std::uint64_t>(buffer[16]-zero_constant);
				return {17,parse_code::ok};
			}
			case 0:
			{
				res=result;
				return {16,parse_code::ok};
			}
			case 4:
			{
				constexpr std::uint64_t risky_value{UINT64_MAX/10000ULL};
				constexpr std::uint64_t risky_mod{UINT64_MAX%10000ULL};
				if(result>risky_value)
					return {20,parse_code::overflow};
				std::uint64_t partial{static_cast<std::uint64_t>(buffer[16]-zero_constant)*1000ULL+static_cast<std::uint64_t>(buffer[17]-zero_constant)*100ULL
				+static_cast<std::uint64_t>(buffer[18]-zero_constant)*10ULL+static_cast<std::uint64_t>(buffer[19]-zero_constant)};
				if(result==risky_value&&risky_mod<partial)
					return {20,parse_code::overflow};
				res=result*10000ULL+partial;
				return {20,parse_code::ok};
			}
			case 16:
			{
				digits1=sse_skip_long_overflow_digits<char_execharset>(buffer+16,buffer_end);
				[[fallthrough]];
			}
			default:
			{
				return {digits1+16,parse_code::overflow};
			}
			}
		}
	}
	res=result;
	return {digits,parse_code::ok};
}

#endif

template<char8_t base,::fast_io::freestanding::random_access_iterator Iter,my_unsigned_integral T>
#if defined(__SSE4_1__) && __has_cpp_attribute(gnu::cold) && defined(__x86_64__)
[[gnu::cold]]
#endif
inline constexpr parse_result<Iter> scan_int_contiguous_none_simd_space_part_define_impl(Iter first,Iter last,T& res,bool has_zero) noexcept
{
	using char_type = ::fast_io::freestanding::iter_value_t<Iter>;
	using unsigned_char_type = std::make_unsigned_t<char_type>;
	using unsigned_type = my_make_unsigned_t<std::remove_cvref_t<T>>;
	constexpr unsigned_char_type base_char_type{base};
	constexpr std::size_t max_size{details::cal_max_int_size<unsigned_type,base>()-1};
	std::size_t const diff{static_cast<std::size_t>(last-first)};
	std::size_t mn_val{max_size};
	if(diff<mn_val)
		mn_val=diff;
	auto first_phase_last{first+mn_val};
	for(;first!=first_phase_last;++first)
	{
		unsigned_char_type ch{static_cast<unsigned_char_type>(*first)};
		if(char_digit_to_literal<base,char_type>(ch))[[unlikely]]
			break;
		res*=base_char_type;
		res+=ch;
	}
	bool overflow{};
	if(first!=last)[[likely]]
	{
		unsigned_char_type ch{static_cast<unsigned_char_type>(*first)};
		if(!char_digit_to_literal<base,char_type>(ch))[[unlikely]]
		{
			constexpr unsigned_type risky_uint_max{static_cast<unsigned_type>(-1)};
			constexpr unsigned_type risky_value{risky_uint_max/base};
			constexpr unsigned_char_type risky_digit(risky_uint_max%base);
			overflow=res>risky_value||(risky_value==0&&ch>risky_digit);
			if(!overflow)
			{
				res*=base_char_type;
				res+=ch;
			}
			for(++first;first!=last&&char_digit_probe_overflow<base,char_type>(*first);++first)
				overflow=true;
		}
	}
	if(res==0&&!has_zero)
		return {first,parse_code::invalid};
	return {first,overflow?parse_code::overflow:parse_code::ok};
}

template<char8_t base,::fast_io::freestanding::random_access_iterator Iter,my_integral T>
inline constexpr parse_result<Iter> scan_int_contiguous_none_space_part_define_impl(Iter first,Iter last,T& t) noexcept
{
	using char_type = ::fast_io::freestanding::iter_value_t<Iter>;
	[[maybe_unused]] bool sign{};
	if constexpr(my_signed_integral<T>)
	{
		if(first==last)
			return {first,parse_code::invalid};
		constexpr auto plus_sign{get_char_with_type<u8'+',char_type>()};
		constexpr auto minus_sign{get_char_with_type<u8'-',char_type>()};
		if((sign=(minus_sign==*first))|(plus_sign==*first))
			++first;
	}
	bool has_zero{};
	constexpr auto zero{get_char_with_type<u8'0',char_type>()};
	for(;first!=last&&(has_zero|=(*first==zero))!=false;++first);
	using unsigned_type = my_make_unsigned_t<std::remove_cvref_t<T>>;
	unsigned_type res{};
	Iter it;
#if defined(__SSE4_1__) && defined(__x86_64__)
	if constexpr(base==10&&sizeof(char_type)==1&&sizeof(unsigned_type)<=sizeof(std::uint64_t))
	{
		if(!std::is_constant_evaluated()&&last-first>=32)[[likely]]
		{
			constexpr bool smaller_than_uint64{sizeof(unsigned_type)<sizeof(std::uint64_t)};
			std::uint64_t temp{};
			auto [digits,ec]=sse_parse<is_ebcdic<char_type>,smaller_than_uint64>(reinterpret_cast<char unsigned const*>(first),reinterpret_cast<char unsigned const*>(last),temp,has_zero);
			it=first+digits;
			if(ec!=parse_code::ok)[[unlikely]]
				return {it,ec};
			if constexpr(smaller_than_uint64)
			{
				constexpr unsigned_type umax{static_cast<unsigned_type>(-1)};
				if(temp>umax)
					return {it,parse_code::overflow};
				res=static_cast<unsigned_type>(temp);
			}
			else
			{
				res=temp;
			}
		}
		else[[unlikely]]
		{
			auto [it2,ec]=scan_int_contiguous_none_simd_space_part_define_impl<base>(first,last,res,has_zero);
			if(ec!=parse_code::ok)
				return {it2,ec};
			it=it2;
		}
	}
	else
#endif
	{
		auto [it2,ec]=scan_int_contiguous_none_simd_space_part_define_impl<base>(first,last,res,has_zero);
		if(ec!=parse_code::ok)
			return {it2,ec};
		it=it2;
	}
	if constexpr(my_signed_integral<T>)
	{
		constexpr unsigned_type umax{static_cast<unsigned_type>(-1)};
		constexpr unsigned_type imax{umax>>1};
		if(res>(static_cast<my_make_unsigned_t<T>>(imax)+sign))
			return {it,parse_code::overflow};
		if(sign)
			t=static_cast<T>(static_cast<unsigned_type>(0)-res);
		else
			t=static_cast<T>(res);
	}
	else
		t=res;
	return {it,parse_code::ok};
}

template<char8_t base,::fast_io::freestanding::random_access_iterator Iter,details::my_integral T>
inline constexpr parse_result<Iter> scan_int_contiguous_define_impl(Iter first,Iter last,T& t) noexcept
{
	for(;first!=last&&::fast_io::char_category::is_c_space(*first);++first);
	if(first==last)
		return {first,parse_code::invalid};
	return scan_int_contiguous_none_space_part_define_impl<base>(first,last,t);
}
}

template<::fast_io::freestanding::random_access_iterator Iter,details::my_integral T>
inline constexpr parse_result<Iter> scan_contiguous_define(io_reserve_type_t<::fast_io::freestanding::iter_value_t<Iter>,parameter<T&>>,Iter begin,Iter end,parameter<T&> t) noexcept
{
	if constexpr(::fast_io::freestanding::contiguous_iterator<Iter>&&!std::is_pointer_v<Iter>)
	{
		auto [it,ec] = details::scan_int_contiguous_define_impl<10>(::fast_io::freestanding::to_address(begin),::fast_io::freestanding::to_address(end),t.reference);
		return {it-::fast_io::freestanding::to_address(begin)+begin,ec};
	}
	else
		return details::scan_int_contiguous_define_impl<10>(begin,end,t.reference);
}

enum class scan_integral_context_phase:char8_t
{
space,
sign,
zero,
digit,
overflow
};

namespace details
{
template<char8_t base,std::integral char_type,details::my_integral T>
inline constexpr auto scan_context_type_impl_int(io_reserve_type_t<char_type,parameter<T&>>) noexcept
{
	using unsigned_type = details::my_make_unsigned_t<std::remove_cvref_t<T>>;
	constexpr std::size_t max_size{details::cal_max_int_size<unsigned_type,base>()+2};
	struct scan_integer_context
	{
		::fast_io::freestanding::array<char_type,max_size> buffer;
		char8_t size{};
		scan_integral_context_phase integer_phase{};
		bool has_zero{};
		inline constexpr void reset() noexcept
		{
			size=0;
			integer_phase=scan_integral_context_phase::space;
		}
	};
	return io_type_t<scan_integer_context>{};
}
}

template<std::integral char_type,details::my_integral T>
inline constexpr auto scan_context_type(io_reserve_type_t<char_type,parameter<T&>>) noexcept
{
	return details::scan_context_type_impl_int<10>(io_reserve_type<char_type,parameter<T&>>);
}

namespace details
{


template<char8_t base,::fast_io::freestanding::input_iterator Iter>
inline constexpr Iter scan_skip_all_digits_impl(Iter first,Iter last)
{
	using char_type = ::fast_io::freestanding::iter_value_t<Iter>;
	for(;first!=last&&char_digit_probe_overflow<base,char_type>(*first);++first);
	return first;
}

template<char8_t base,typename State,::fast_io::freestanding::input_iterator Iter,my_integral T>
inline constexpr parse_result<Iter> scan_context_define_parse_impl(State& st,Iter first_start,Iter last,T& t) noexcept
{
	using char_type = ::fast_io::freestanding::iter_value_t<Iter>;
	auto first{first_start};
	auto phase{st.integer_phase};
	switch(phase)
	{
	case scan_integral_context_phase::space:
	{
		for(;first!=last&&::fast_io::char_category::is_c_space(*first);++first);
		[[fallthrough]];
	}
	case scan_integral_context_phase::sign:
	{
		if constexpr(my_signed_integral<T>)
		{
			constexpr auto plus{get_char_with_type<u8'+',char_type>()};
			constexpr auto minus{get_char_with_type<u8'-',char_type>()};
			if(first==last)
			{
				st.integer_phase=scan_integral_context_phase::space;
				return {first,parse_code::partial};
			}
			if((*first==plus)|(*first==minus))
			{
				*st.buffer.data()=*first;
				st.size=1;
				++first;
			}
		}
		[[fallthrough]];
	}
	case scan_integral_context_phase::zero:
	{
		constexpr auto zero{get_char_with_type<u8'0',char_type>()};
		auto first_b{first};
		for(;first!=last&&*first==zero;++first);
		if(first_b==first)
		{
			if(first==last)
			{
				st.integer_phase=scan_integral_context_phase::zero;
				return {first,parse_code::partial};
			}
			else if(!char_digit_probe_overflow<base,char_type>(*first))
			{
				return {first,parse_code::invalid};
			}
		}
		else
			st.has_zero=true;
		[[fallthrough]];
	}
	case scan_integral_context_phase::digit:
	{
		auto it{scan_skip_all_digits_impl<base>(first,last)};
		std::size_t const diff{st.buffer.size()-static_cast<std::size_t>(st.size)};
		std::size_t const first_it_diff{static_cast<std::size_t>(it-first)};
		if(first_it_diff<diff)
		{
			auto start{st.buffer.data()+st.size};
			auto e{non_overlapped_copy_n(first,first_it_diff,start)};
			st.size+=static_cast<char8_t>(first_it_diff);
			if(it==last)
			{
				st.integer_phase=scan_integral_context_phase::digit;
				return {it,parse_code::partial};
			}
			if(st.size==0&&st.has_zero)
			{
				t=0;
				return {it,parse_code::ok};
			}
			auto [p,ec]=scan_int_contiguous_none_space_part_define_impl<base>(st.buffer.data(),e,t);
			return {p-start+first,ec};
		}
		else
		{
			if(it==last)
			{
				st.integer_phase=scan_integral_context_phase::overflow;
				return {it,parse_code::partial};
			}
			else
			{
				return {it,parse_code::overflow};
			}
		}
	}
	default:
	{
		first=scan_skip_all_digits_impl<base>(first,last);
		return {first,(first==last)?parse_code::partial:parse_code::invalid};
	}
	}
}

template<char8_t base,typename State,my_integral T>
#if __has_cpp_attribute(gnu::cold)
[[gnu::cold]]
#endif
inline constexpr parse_code scan_context_eof_define_parse_impl(State& st,T& t) noexcept
{
	switch(st.integer_phase)
	{
	case scan_integral_context_phase::digit:
		return scan_int_contiguous_none_space_part_define_impl<base>(st.buffer.data(),st.buffer.data()+st.size,t).code;
	case scan_integral_context_phase::overflow:
		return parse_code::overflow;
	default:
		return parse_code::invalid;
	}
}

}

template<::fast_io::freestanding::input_iterator Iter,typename State,details::my_integral T>
inline constexpr parse_result<Iter> scan_context_define2(io_reserve_type_t<::fast_io::freestanding::iter_value_t<Iter>,parameter<T&>>,State& state,Iter begin,Iter end,parameter<T&> t) noexcept
{
	return details::scan_context_define_parse_impl<10>(state,begin,end,t.reference);
}

template<std::integral char_type,typename State,details::my_integral T>
inline constexpr parse_code scan_context_eof_define(io_reserve_type_t<char_type,parameter<T&>>,State& state,parameter<T&> t) noexcept
{
	return details::scan_context_eof_define_parse_impl<10>(state,t.reference);
}

}