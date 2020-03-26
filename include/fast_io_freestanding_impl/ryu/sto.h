#pragma once

namespace fast_io::details::ryu
{

template<char32_t decimal_point,std::floating_point F,typename It_First,typename It_Second>
inline constexpr F input_floating(It_First iter,It_Second ed)
{
	using char_type = std::remove_cvref_t<decltype(*iter)>;
	using floating_trait = floating_traits<F>;
	using mantissa_type = typename floating_trait::mantissa_type;
	using exponent_type = typename floating_trait::exponent_type;
	using unsigned_char_type = std::make_unsigned_t<char_type>;
	using signed_exponent_type = std::make_signed_t<exponent_type>;
	constexpr unsigned_char_type decimal_point_value_after_minus_zero{static_cast<unsigned_char_type>(static_cast<unsigned_char_type>(decimal_point)-u8'0')}; 
	//.(46)-48: static_cast<unsigned_char_type>(-2)
	//-(45)-48: static_cast<unsigned_char_type>(-3)
	//'E'(69)-48: 21
	//'e'(101)-48: 53
	//We do not support EBCDIC
	bool negative{};
	if(*iter==u8'-')
	{
		negative=true;
		if(++iter==ed)
			return bit_cast<F>(static_cast<mantissa_type>(static_cast<mantissa_type>(negative) << ((sizeof(F)<<3)-1)));
	}
	else if(*iter==u8'+')[[unlikely]]
	{
		if(++iter==ed)
			return {};
	}
	
	for(;iter!=ed&&*iter==u8'0';++iter);
	exponent_type m10digits{};
	mantissa_type m10{};
	signed_exponent_type dot_index{-1};
	exponent_type index{};
	for(;iter!=ed&&m10digits!=floating_trait::digits10;++iter)
	{
		unsigned_char_type const ch(*iter-u8'0');
		if(0x9<ch)[[unlikely]]
		{
			if(ch==decimal_point_value_after_minus_zero)
			{
				if(dot_index!=-1)
					throw std::runtime_error("malformed input");
				dot_index=index;
				++index;
				continue;
			}
			else
				break;

		}
		m10*=10;
		if(m10+=ch)[[likely]]
			++m10digits;
		++index;
	}
	std::size_t extra_e10{};
	if(m10digits==floating_trait::digits10)[[unlikely]]
	{
		if(dot_index==-1)
		{
			for(;iter!=ed&&*iter==u8'0';++iter)
				++extra_e10;
			if(iter!=ed&&*iter==decimal_point)
				++iter;
		}
		for(;iter!=ed&&*iter==u8'0';++iter);
		if(iter!=ed&&static_cast<unsigned_char_type>(*iter-u8'1')<9)[[unlikely]]
		{
#ifdef __cpp_exceptions
			throw std::runtime_error("out of precision of ryu algorithm. To do with multiprecision");
#else
			fast_terminate();
#endif
		}
	}
	signed_exponent_type e_index{-1};
	bool exp_negative{};
	exponent_type ue10{};
	std::size_t ue10digits{};
	if(iter!=ed&&((*iter==u8'e')||(*iter==u8'E')))
	{
		e_index=index;
		if(++iter==ed)[[unlikely]]
			throw std::runtime_error("malformed input");
		++index;
		if((*iter==u8'+')||(*iter==u8'-'))[[likely]]
		{
			exp_negative=(*iter==u8'-');
			if(++iter==ed)[[unlikely]]
				throw std::runtime_error("malformed input");
			++index;
		}
		for(;iter!=ed&&*iter==u8'0';++iter)
			++index;
		for(;iter!=ed;++iter)
		{
			unsigned_char_type const ch(*iter-u8'0');
			if(0x9<ch)[[unlikely]]
				break;
			ue10*=10;
			ue10+=ch;
			++ue10digits;
			++index;
		}
	}
	detect_overflow<10>(ue10,ue10digits);
	if((ue10+=extra_e10)<extra_e10)[[unlikely]]
		throw std::runtime_error("exp part integer overflow");
	signed_exponent_type e10(static_cast<signed_exponent_type>(ue10));
	if(exp_negative)
		e10=-e10;
	if(e_index==-1)
		e_index=index;
	if(dot_index==-1)
		dot_index=index;
	e10-=dot_index<e_index?e_index-dot_index-1:0;
	if((static_cast<signed_exponent_type>(m10digits+e10)<floating_trait::minimum_exp)||(!m10))
		return (static_cast<mantissa_type>(negative)<<(floating_trait::exponent_bits+floating_trait::mantissa_bits));
	if(floating_trait::maximum_exp<static_cast<signed_exponent_type>(m10digits+e10))
		return bit_cast<F>((static_cast<mantissa_type>(static_cast<mantissa_type>(negative) << ((sizeof(F)<<3)-1)))
				|static_cast<mantissa_type>(static_cast<mantissa_type>(0x7ffull) << floating_trait::mantissa_bits));
	bool trailing_zeros{};
	signed_exponent_type e2(static_cast<signed_exponent_type>(std::bit_width(m10))+e10-(2+floating_trait::mantissa_bits));
	mantissa_type m2{};
	if(e10<0)
	{
		auto const p5bme10(pow5bits(-e10));
		e2-=p5bme10;
		m2=mul_shift(m10,pow5<F,true>::inv_split[-e10],e2-e10+p5bme10-1+floating_trait::pow5_bitcount);
		trailing_zeros=multiple_of_power_of_5(m10,-e10);
	}
	else
	{
		e2+=log2pow5(e10);
		m2=mul_shift(m10,pow5<F,true>::split[e10],e2-e10-pow5bits(e10)+floating_trait::pow5_bitcount);
		trailing_zeros = e2 < e10 || multiple_of_power_of_2(m10, e2 - e10);
	}
	signed_exponent_type ieee_e2(e2 + (floating_trait::bias-1) + std::bit_width(m2));
	if(ieee_e2<0)
		ieee_e2=0;
	if(0x7fe<ieee_e2)[[unlikely]]
		return bit_cast<F>((static_cast<mantissa_type>(static_cast<mantissa_type>(negative) << ((sizeof(F)<<3)-1)))
				|static_cast<mantissa_type>(static_cast<mantissa_type>(0x7ffull) << floating_trait::mantissa_bits));
	signed_exponent_type shift((!ieee_e2?1:ieee_e2)-e2-(floating_trait::bias+floating_trait::mantissa_bits));
	trailing_zeros &= !(m2 & ((1L << (shift - 1)) - 1));
	bool last_removed_bit((m2>>(shift-1))&1);
	bool round_up((last_removed_bit) && (!trailing_zeros || ((m2 >> shift) & 1)));
	mantissa_type ieee_m2((m2 >> shift) + round_up);
	if(ieee_m2 == (static_cast<mantissa_type>(1) << (floating_trait::mantissa_bits + 1)))
		++ieee_e2;
	ieee_m2&=((static_cast<mantissa_type>(1) << floating_trait::mantissa_bits) - 1);
	return bit_cast<F>(((((static_cast<mantissa_type>(negative)) << floating_trait::exponent_bits) | static_cast<mantissa_type>(ieee_e2)) << 
	floating_trait::mantissa_bits)|(((m2 >> shift) + round_up) & ((static_cast<mantissa_type>(1) << floating_trait::mantissa_bits) - 1)));
}

}
