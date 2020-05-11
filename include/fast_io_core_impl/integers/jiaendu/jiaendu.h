#pragma once
#include"table_gen.h"
/*
Although it is still called jiaendu algorithm. The 64 bits are created by myself + I modified the table of jiaendu. It is no longer real jiaendu any more.
*/

namespace fast_io
{
namespace details::jiaendu
{

template<std::contiguous_iterator Iter,std::unsigned_integral U>
inline std::size_t output_unsigned(Iter str,U value)
{
	using ch_type = std::remove_cvref_t<decltype(*str)>;
	constexpr std::size_t bytes4{4*sizeof(ch_type)};
	if constexpr(sizeof(U)==8)
	{
		if (value>=10000000000000000ULL)
		{
			std::uint64_t v4{value/10000000000000000ULL};
			std::uint64_t remains3{value-v4*10000000000000000ULL};
			std::uint64_t temp3(remains3/1000000000000ULL);
			std::uint64_t remains2
			{remains3-temp3*1000000000000ULL};
			remains3=temp3;
			std::uint64_t temp2{remains2};
			std::uint64_t remains0{remains2/10000};
			std::uint64_t remains1{remains2/100000000};
			remains2 = remains1;
			remains1 = remains0 - remains1*10000;
			remains0 = temp2 - remains0*10000;
			if (v4 >= 1000)
			{
				memcpy(str,static_tables<ch_type>::table4[v4].data(),bytes4);
				memcpy(str += 4,static_tables<ch_type>::table4[remains3].data(),bytes4);
				memcpy(str += 4,static_tables<ch_type>::table4[remains2].data(),bytes4);
				memcpy(str += 4,static_tables<ch_type>::table4[remains1].data(),bytes4);
				memcpy(str += 4,static_tables<ch_type>::table4[remains0].data(),bytes4);
				return 20;
			}
			else
			{
				auto wstr(str);
				memcpy(wstr,static_tables<ch_type>::table5[v4].data(),bytes4);
				wstr += static_offset<>::offset[v4];
				memcpy(wstr,static_tables<ch_type>::table4[remains3].data(),bytes4);
				memcpy(wstr += 4,static_tables<ch_type>::table4[remains2].data(),bytes4);
				memcpy(wstr += 4,static_tables<ch_type>::table4[remains1].data(),bytes4);
				memcpy(wstr += 4,static_tables<ch_type>::table4[remains0].data(),bytes4);
				wstr += 4;
				return static_cast<std::size_t>(wstr-str);
			}
		}
		else if (value>=1000000000000ULL)
		{
			std::uint64_t v3{value/1000000000000ULL};
			std::uint64_t remains2
			{value-v3*1000000000000ULL};
			std::uint64_t temp2{remains2};
			std::uint64_t remains0{remains2/10000};
			std::uint64_t remains1{remains2/100000000};
			remains2 = remains1;
			remains1 = remains0 - remains1*10000;
			remains0 = temp2 - remains0*10000;
			if (v3 >= 1000)
			{
				memcpy(str,static_tables<ch_type>::table4[v3].data(),bytes4);
				memcpy(str += 4,static_tables<ch_type>::table4[remains2].data(),bytes4);
				memcpy(str += 4,static_tables<ch_type>::table4[remains1].data(),bytes4);
				memcpy(str += 4,static_tables<ch_type>::table4[remains0].data(),bytes4);
				return 16;
			}
			else
			{
				auto wstr(str);
				memcpy(wstr,static_tables<ch_type>::table5[v3].data(),bytes4);
				wstr += static_offset<>::offset[v3];
				memcpy(wstr,static_tables<ch_type>::table4[remains2].data(),bytes4);
				memcpy(wstr += 4,static_tables<ch_type>::table4[remains1].data(),bytes4);
				memcpy(wstr += 4,static_tables<ch_type>::table4[remains0].data(),bytes4);
				wstr += 4;
				return static_cast<std::size_t>(wstr-str);
			}
		}
		else if (value >= 100000000)
		{
			std::uint64_t remains0{value/10000};// value/1,0000
			std::uint64_t remains1{value/100000000};// value/1,0000,0000
			auto v2(remains1);
			remains1 = remains0 - remains1*10000;
			remains0 = value - remains0*10000;
			if (v2 >= 1000)
			{
				memcpy(str,static_tables<ch_type>::table4[v2].data(),bytes4);
				memcpy(str += 4,static_tables<ch_type>::table4[remains1].data(),bytes4);
				memcpy(str += 4,static_tables<ch_type>::table4[remains0].data(),bytes4);
				return 12;
			}
			else
			{
				auto wstr(str);
				memcpy(wstr,static_tables<ch_type>::table5[v2].data(),bytes4);
				wstr += static_offset<>::offset[v2];
				memcpy(wstr,static_tables<ch_type>::table4[remains1].data(),bytes4);
				memcpy(wstr += 4,static_tables<ch_type>::table4[remains0].data(),bytes4);
				wstr += 4;
				return static_cast<std::size_t>(wstr-str);
			}
		}
		else if (value >= 10000)
		{
			std::uint64_t const v2{
				(static_cast<std::uint64_t>(value) *
				static_cast<std::uint64_t>(3518437209)) >> 45};
			std::uint64_t const remains0{value - v2 * 10000};
			if (v2 >= 1000)
			{
				memcpy(str,static_tables<ch_type>::table4[v2].data(),bytes4);
				str += 4;
				memcpy(str,static_tables<ch_type>::table4[remains0].data(),bytes4);
				return 8;
			}
			else
			{
				auto wstr(str);
				memcpy(wstr,static_tables<ch_type>::table5[v2].data(),bytes4);
				wstr += static_offset<>::offset[v2];
				memcpy(wstr,static_tables<ch_type>::table4[remains0].data(),bytes4);
				wstr += 4;
				return static_cast<std::size_t>(wstr - str);
			}
		}
		else
		{
			if (value >= 1000)
			{
				memcpy(str,static_tables<ch_type>::table4[value].data(),bytes4);
				return 4;
			}
			else if (value >= 100)
			{
				memcpy(str,static_tables<ch_type>::table3[value].data(),3*sizeof(ch_type));
				return 3;
			}
			else if (value >= 10)
			{
				memcpy(str,static_tables<ch_type>::table2[value].data(),2*sizeof(ch_type));
				return 2;
			}
			else
			{
				*str = static_cast<ch_type>(static_cast<char8_t>(value)+u8'0');
				return 1;
			}
		}
	}
	else if constexpr(sizeof(U)==4)
	{
		if (value >= 100000000)[[unlikely]]
		{
#if (_WIN64 || __x86_64__ || __ppc64__)
			std::uint64_t remains0{(static_cast<std::uint64_t>(value) *
			static_cast<std::uint64_t>(3518437209)) >> 45};
			std::uint64_t remains1{static_cast<std::uint64_t>(value) * 
			static_cast<std::uint64_t>((2882303762)) >> 58};
#else
			std::uint32_t remains0{value/10000};
			std::uint32_t remains1{value/100000000};
#endif
			auto v2(remains1);
			remains1 = remains0 - remains1*10000;
			remains0 = value - remains0*10000;
			if (v2 >= 10)
			{
				memcpy(str,static_tables<ch_type>::table5[v2].data(),2*sizeof(ch_type));
				memcpy(str += 2,static_tables<ch_type>::table4[remains1].data(),bytes4);
				memcpy(str += 4,static_tables<ch_type>::table4[remains0].data(),bytes4);
				return 10;
			}
			else
			{
				*str = static_cast<char8_t>(v2)+u8'0';
				memcpy(++str,static_tables<ch_type>::table4[remains1].data(),bytes4);
				memcpy(str += 4,static_tables<ch_type>::table4[remains0].data(),bytes4);
				return 9;
			}
		}
		else if (value >= 10000)
		{
#if (_WIN64 || __x86_64__ || __ppc64__)
			std::uint64_t const v2{
				(static_cast<std::uint64_t>(value) *
				static_cast<std::uint64_t>(3518437209)) >> 45};
			std::uint64_t const remains0{value - v2 * 10000};
#else
			std::uint32_t const v2{value/10000};
			std::uint32_t const remains0{value - v2 * 10000};
#endif
			if (v2 >= 1000)
			{
				memcpy(str,static_tables<ch_type>::table4[v2].data(),bytes4);
				str += 4;
				memcpy(str,static_tables<ch_type>::table4[remains0].data(),bytes4);
				return 8;
			}
			else
			{
				auto wstr(str);
				memcpy(wstr,static_tables<ch_type>::table5[v2].data(),bytes4);
				wstr += static_offset<>::offset[v2];
				memcpy(wstr,static_tables<ch_type>::table4[remains0].data(),bytes4);
				wstr += 4;
				return static_cast<std::size_t>(wstr - str);
			}
		}
		else
		{
			if (value >= 1000)
			{
				memcpy(str,static_tables<ch_type>::table4[value].data(),bytes4);
				return 4;
			}
			else if (value >= 100)
			{
				memcpy(str,static_tables<ch_type>::table3[value].data(),3*sizeof(ch_type));
				return 3;
			}
			else if (value >= 10)
			{
				memcpy(str,static_tables<ch_type>::table2[value].data(),2*sizeof(ch_type));
				return 2;
			}
			else
			{
				*str = static_cast<char8_t>(value)+u8'0';
				return 1;
			}
		}
	}
	else if constexpr(sizeof(U)==2)
	{
		if (value >= 10000)
		{
#if (_WIN64 || __x86_64__ || __ppc64__)
			std::uint64_t const v2{
				(static_cast<std::uint64_t>(value) *
				static_cast<std::uint64_t>(3518437209)) >> 45};
			std::uint64_t const remains0{value - v2 * 10000};
#else
			std::uint32_t const v2{value/10000};
			std::uint32_t const remains0{value - v2 * 10000};
#endif
			if (v2 >= 1000)
			{
				memcpy(str,static_tables<ch_type>::table4[v2].data(),bytes4);
				str += 4;
				memcpy(str,static_tables<ch_type>::table4[remains0].data(),bytes4);
				return 8;
			}
			else
			{
				auto wstr(str);
				memcpy(wstr,static_tables<ch_type>::table5[v2].data(),bytes4);
				wstr += static_offset<>::offset[v2];
				memcpy(wstr,static_tables<ch_type>::table4[remains0].data(),bytes4);
				wstr += 4;
				return static_cast<std::size_t>(wstr - str);
			}
		}
		else
		{
			if (value >= 1000)
			{
				memcpy(str,static_tables<ch_type>::table4[value].data(),bytes4);
				return 4;
			}
			else if (value >= 100)
			{
				memcpy(str,static_tables<ch_type>::table3[value].data(),3*sizeof(ch_type));
				return 3;
			}
			else if (value >= 10)
			{
				memcpy(str,static_tables<ch_type>::table2[value].data(),2*sizeof(ch_type));
				return 2;
			}
			else
			{
				*str = static_cast<ch_type>(static_cast<char8_t>(value)+u8'0');
				return 1;
			}
		}
	}
	else if constexpr(sizeof(U)==1)
	{
		if (value >= 100)
		{
			memcpy(str,static_tables<ch_type>::table3[value].data(),3*sizeof(ch_type));
			return 3;
		}
		else if (value >= 10)
		{
			memcpy(str,static_tables<ch_type>::table2[value].data(),2*sizeof(ch_type));
			return 2;
		}
		else
		{
			*str = static_cast<char8_t>(value)+u8'0';
			return 1;
		}
	}
}
template<char32_t decimal_point,std::unsigned_integral U,std::contiguous_iterator Iter>
inline std::size_t output_unsigned_point(U value,Iter str)
{
	if(value >= 10)[[likely]]
	{
		std::size_t ret(output_unsigned(std::to_address(str)+1,value));
		*str=str[1];
		str[1]=decimal_point;
		return ret+1;
	}
	else
	{
		*str = static_cast<char8_t>(value)+u8'0';
		return 1;
	}
}


}

}
