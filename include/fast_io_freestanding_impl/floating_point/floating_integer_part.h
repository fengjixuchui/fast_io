#pragma once

namespace fast_io
{
namespace details
{

template<bool control,typename T,char8_t value>
struct compile_time_floating_value;

template<char8_t decimal_point>
struct compile_time_floating_value<false,char8_t,decimal_point>
{};

template<char8_t decm>
inline constexpr compile_time_floating_value<false,char8_t,decm> compile_time_floating_v{};

template<std::integral ch_type>
struct compile_time_floating_value<true,ch_type,0>		//if you see ~ which means it is a bug.
{
	ch_type decimal_point{};
};

template<std::contiguous_iterator Iter,my_unsigned_integral U>
inline constexpr std::size_t fp_output_unsigned(Iter iter,U i)
{
	if(std::is_constant_evaluated())
	{
		return optimize_size::output_unsigned(iter,static_cast<std::remove_cvref_t<U>>(i));
	}
	else
	{

		namespace algo_decision = 
#ifdef FAST_IO_OPTIMIZE_SIZE
			optimize_size;
#else
			jiaendu::fp;
#endif
		return algo_decision::output_unsigned(iter,static_cast<std::remove_cvref_t<U>>(i));
	}
}

template<bool control,typename T,char8_t static_decimal_point,my_unsigned_integral U,std::contiguous_iterator Iter>
inline constexpr std::size_t fp_output_unsigned_point([[maybe_unused]]compile_time_floating_value<control,T,static_decimal_point> decm,U value,Iter str)
{
	if(value >= 10)[[likely]]
	{
		if(std::is_constant_evaluated())
		{
			std::size_t ret(optimize_size::output_unsigned(std::to_address(str)+1,value));
			*str=str[1];
			if constexpr(control)
				str[1]=decm.decimal_point;
			else
				str[1]=static_decimal_point;
			return ret+1;
		}
		else
		{

			namespace algo_decision = 
#ifdef FAST_IO_OPTIMIZE_SIZE
				optimize_size;
#else
				jiaendu::fp;
#endif
			std::size_t ret(algo_decision::output_unsigned(std::to_address(str)+1,value));
			*str=str[1];
			if constexpr(control)
				str[1]=decm.decimal_point;
			else
				str[1]=static_decimal_point;
			return ret+1;
		}
	}
	else
	{
		*str = static_cast<char8_t>(value)+u8'0';
		return 1;
	}
}
}

}