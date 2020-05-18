//provide an API layer which fast_io requires for grisu_exact

namespace fast_io::details
{

namespace grisu_exact
{
template<typename T,std::random_access_iterator Iter>
inline constexpr Iter floating_to_chars(T f,Iter result)
{
	auto v(jkj::grisu_exact<false>(f));
/*	if(v.is_negative)
	{
		*result=u8'-';
		++result;
	}*/
	std::int32_t olength(static_cast<std::int32_t>(chars_len<10,true>(v.significand)));
	std::int32_t const real_exp(static_cast<std::int32_t>(v.exponent + olength - 1));
	std::uint32_t fixed_length(0),this_case(0);
	if(olength<=real_exp)
	{
		fixed_length=real_exp+1;
		this_case=1;
	}
	else if(0<=real_exp&&real_exp<olength)
	{
		fixed_length=olength+2;
		if(olength==real_exp+1)
			--fixed_length;
		this_case=2;
	}
	else
		fixed_length=static_cast<std::int32_t>(-real_exp)+olength+1;
	std::uint32_t scientific_length(olength==1?olength+3:olength+5);
	if(scientific_length<fixed_length)
	{
		result+=details::jiaendu::output_unsigned_point(v.significand,result);
		return details::ryu::output_exp<false>(static_cast<std::int32_t>(real_exp),result);
	}
	switch(this_case)
	{
	case 1:
		jiaendu::output_unsigned(v.significand,result);
		result+=olength;
		return my_fill_n(result,real_exp+1-olength,0x30);
	case 2:
	{
		auto a(v.significand);
		auto eposition(real_exp+1);
		if(olength==eposition)
		{
			jiaendu::output_unsigned(a,result);
			result+=olength;
		}
		else
		{
			jiaendu::output_unsigned(a,result+1);
			my_copy_n(result+1,eposition,result);
			result[eposition]=u8'.';
			result+=olength+1;
		}
		return result;
	}
	default:
		result=my_copy_n(u8"0.",2,result);
		result=my_fill_n(result,static_cast<std::int32_t>(-real_exp-1),0x30);
		jiaendu::output_unsigned(v.significand,result);
		result+=olength;
		return result;
	}
}
}

namespace floating_algorithms
{
template<std::floating_point T>
struct grisu_exact
{
	T& reference;
};
}

template<std::floating_point T>
inline constexpr floating_algorithms::grisu_exact<T const> grisu_exact(T const &f){return {f};}

template<output_stream output,std::floating_point T>
inline void print_define(output& out,floating_algorithms::grisu_exact<T const> a)
{
	std::size_t constexpr reserved_size(30);
	if constexpr(buffer_output_stream<output>)
	{

		auto reserved(oreserve(out,reserved_size));
		if constexpr(std::is_pointer_v<decltype(reserved)>)
		{
			if(reserved)
			{
				auto start(reserved-reserved_size);
				orelease(out,reserved-details::grisu_exact::floating_to_chars(static_cast<double>(a.reference),start));
				return;
			}
		}
		else
		{
			auto start(reserved-reserved_size);
			orelease(out,reserved-details::grisu_exact::floating_to_chars(static_cast<double>(a.reference),start));
			return;
		}
	}
	std::array<typename output::char_type,reserved_size> array;
	write(out,array.data(),details::grisu_exact::floating_to_chars(static_cast<double>(a.reference),array.data()));
}
}
