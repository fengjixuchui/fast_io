#pragma once
#include"util.h"
#include"manip.h"
#include"twodigits/shared_base_table.h"
#include"twodigits/base.h"
#include"optimize_size/impl.h"
#include"jiaendu/jiaendu.h"
#include"sto/sto.h"

namespace fast_io
{

template<std::integral int_type>
inline constexpr std::size_t print_reserve_size(print_reserve_type_t<int_type>)
{
	if constexpr(std::unsigned_integral<int_type>)
		return details::cal_max_uint_size<int_type>();
	else
		return details::cal_max_uint_size<std::make_unsigned_t<int_type>>()+1;
}

template<std::random_access_iterator caiter,std::integral int_type,typename U>
inline constexpr caiter print_reserve_define(print_reserve_type_t<int_type>,caiter iter,U i)
{
	if (std::is_constant_evaluated())
	{
		namespace algo_decision = fast_io::details::optimize_size;
		if constexpr(std::unsigned_integral<int_type>)
			return iter+algo_decision::output_unsigned(iter,i);
		else
		{
			if(i<0)
			{
				*iter=u8'-';
				++iter;
				return iter+algo_decision::output_unsigned(iter,-static_cast<std::make_unsigned_t<int_type>>(i));
			}
			else
				return iter+algo_decision::output_unsigned(iter,static_cast<std::make_unsigned_t<int_type>>(i));
		}
	}
	else
	{
		namespace algo_decision = 
#ifdef FAST_IO_OPTIMIZE_SIZE
			details::optimize_size
#else
			details::jiaendu
#endif
	;
		if constexpr(std::unsigned_integral<int_type>)
			return iter+algo_decision::output_unsigned(iter,i);
		else
		{
			if(i<0)
			{
				*iter=u8'-';
				++iter;
				return iter+algo_decision::output_unsigned(iter,-static_cast<std::make_unsigned_t<int_type>>(i));
			}
			else
				return iter+algo_decision::output_unsigned(iter,static_cast<std::make_unsigned_t<int_type>>(i));
		}
	}
}

template<char8_t base,bool uppercase,std::integral int_type>
inline constexpr std::size_t print_reserve_size(print_reserve_type_t<manip::base_t<base,uppercase,int_type>>)
{
	if constexpr(std::unsigned_integral<int_type>)
		return details::cal_max_uint_size<int_type,base>();
	else
		return details::cal_max_uint_size<std::make_unsigned_t<int_type>,base>()+1;
}

template<std::random_access_iterator caiter,char8_t base,bool uppercase,std::integral int_type,typename P>
inline constexpr caiter print_reserve_define(print_reserve_type_t<manip::base_t<base,uppercase,int_type>>,caiter iter,P ref)
{
	auto const i{ref.reference};
	if (std::is_constant_evaluated())
	{
		namespace algo_decision = fast_io::details::optimize_size;
		if constexpr(std::unsigned_integral<int_type>)
			return iter+algo_decision::output_unsigned<base>(iter,i);
		else
		{
			if(i<0)
			{
				*iter=u8'-';
				++iter;
				return iter+algo_decision::output_unsigned<base>(iter,-static_cast<std::make_unsigned_t<int_type>>(i));
			}
			else
				return iter+algo_decision::output_unsigned<base>(iter,static_cast<std::make_unsigned_t<int_type>>(i));
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
			if constexpr(std::unsigned_integral<int_type>)
				return iter+algo_decision::output_unsigned(iter,i);
			else
			{
				if(i<0)
				{
					*iter=u8'-';
					++iter;
					return iter+algo_decision::output_unsigned(iter,-static_cast<std::make_unsigned_t<int_type>>(i));
				}
				else
					return iter+algo_decision::output_unsigned(iter,static_cast<std::make_unsigned_t<int_type>>(i));
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
			if constexpr(std::unsigned_integral<int_type>)
				return iter+algo_decision::output_unsigned<base,uppercase>(iter,i);
			else
			{
				if(i<0)
				{
					*iter=u8'-';
					++iter;
					return iter+algo_decision::output_unsigned<base,uppercase>(iter,-static_cast<std::make_unsigned_t<int_type>>(i));
				}
				else
					return iter+algo_decision::output_unsigned<base,uppercase>(iter,static_cast<std::make_unsigned_t<int_type>>(i));
			}
		}
	}
}
}