#pragma once
#include"util.h"
#include"manip.h"
#include"twodigits/shared_base_table.h"
#include"twodigits/base.h"
#include"optimize_size/impl.h"
#include"jiaendu/jiaendu.h"
#include"sto/sto.h"
#include"append_nine_digits.h"

namespace fast_io
{

namespace details
{
template<char8_t base,bool uppercase,bool ignore_sign=false,std::contiguous_iterator Iter,my_integral int_type>
inline constexpr Iter process_integer_output(Iter iter,int_type i)
{
	if (std::is_constant_evaluated())
	{
		namespace algo_decision = fast_io::details::optimize_size;
		if constexpr(my_unsigned_integral<int_type>)
			return iter+algo_decision::output_unsigned<base>(iter,static_cast<std::remove_cvref_t<int_type>>(i));
		else
		{
			if(i<0)
			{
				if constexpr(!ignore_sign)
				{
					*iter=u8'-';
					++iter;
				}
				return iter+algo_decision::output_unsigned<base>(iter,static_cast<my_make_unsigned_t<std::remove_cvref_t<int_type>>>(-static_cast<my_make_unsigned_t<std::remove_cvref_t<int_type>>>(i)));
			}
			else
				return iter+algo_decision::output_unsigned<base>(iter,static_cast<my_make_unsigned_t<std::remove_cvref_t<int_type>>>(i));
		}
	}
	else
	{
		if constexpr(base==10)
		{
			namespace algo_decision = 
#ifdef FAST_IO_OPTIMIZE_SIZE
				details::optimize_size;
#else
				details::jiaendu;
#endif
			if constexpr(my_unsigned_integral<int_type>)
				return iter+algo_decision::output_unsigned(iter,static_cast<std::remove_cvref_t<int_type>>(i));
			else
			{
				if(i<0)
				{
					if constexpr(!ignore_sign)
					{
						*iter=u8'-';
						++iter;
					}
					return iter+algo_decision::output_unsigned(iter,
					static_cast<my_make_unsigned_t<std::remove_cvref_t<int_type>>>(-static_cast<my_make_unsigned_t<std::remove_cvref_t<int_type>>>(i)));
				}
				else
					return iter+algo_decision::output_unsigned(iter,static_cast<my_make_unsigned_t<std::remove_cvref_t<int_type>>>(i));
			}
		}
		else
		{
			namespace algo_decision = 
#ifdef FAST_IO_OPTIMIZE_SIZE
				details::optimize_size;
#else
				details::twodigits;
#endif
			if constexpr(my_unsigned_integral<int_type>)
				return iter+algo_decision::output_unsigned<base,uppercase>(iter,static_cast<std::remove_cvref_t<int_type>>(i));
			else
			{
				if(i<0)
				{
					if constexpr(!ignore_sign)
					{
						*iter=u8'-';
						++iter;
					}
					return iter+algo_decision::output_unsigned<base,uppercase>(iter,static_cast<my_make_unsigned_t<std::remove_cvref_t<int_type>>>(-static_cast<my_make_unsigned_t<std::remove_cvref_t<int_type>>>(i)));
				}
				else
					return iter+algo_decision::output_unsigned<base,uppercase>(iter,static_cast<my_make_unsigned_t<std::remove_cvref_t<int_type>>>(i));
			}
		}
	}
}
}

template<details::my_integral int_type>
inline constexpr std::size_t print_reserve_size(print_reserve_type_t<int_type>)
{
	if constexpr(details::my_unsigned_integral<int_type>)
		return details::cal_max_int_size<int_type>();
	else
		return details::cal_max_int_size<details::my_make_unsigned_t<int_type>>()+1;
}

template<std::random_access_iterator caiter,details::my_integral int_type,typename U>
inline constexpr caiter print_reserve_define(print_reserve_type_t<int_type>,caiter iter,U i)
{
	return details::process_integer_output<10,false>(iter,i);
}

template<char8_t base,bool uppercase,details::my_integral int_type>
inline constexpr std::size_t print_reserve_size(print_reserve_type_t<manip::base_t<base,uppercase,int_type>>)
{
	if constexpr(details::my_unsigned_integral<int_type>)
		return details::cal_max_int_size<int_type,base>();
	else
		return details::cal_max_int_size<details::my_make_unsigned_t<int_type>,base>()+1;
}

template<std::random_access_iterator caiter,char8_t base,bool uppercase,details::my_integral int_type,typename P>
inline constexpr caiter print_reserve_define(print_reserve_type_t<manip::base_t<base,uppercase,int_type>>,caiter iter,P ref)
{
	return details::process_integer_output<base,uppercase>(iter,ref.reference);
}

}

#include"pointer.h"