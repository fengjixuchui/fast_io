#pragma once

namespace fast_io::details::jiaendu::fp
{

//this is only use for integer
template<std::contiguous_iterator Iter,std::unsigned_integral U>
requires (sizeof(U)==4||sizeof(U)==8)
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
			*str=static_cast<char8_t>(v4)+u8'0';		
			memcpy(str + 1,static_tables<ch_type>::table4[remains3].data(),bytes4);
			memcpy(str + 5,static_tables<ch_type>::table4[remains2].data(),bytes4);
			memcpy(str + 9,static_tables<ch_type>::table4[remains1].data(),bytes4);
			memcpy(str + 13,static_tables<ch_type>::table4[remains0].data(),bytes4);
			return 17;
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
	else
	{
		if (value >= 100000000)
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
			*str = static_cast<char8_t>(v2)+u8'0';
			memcpy(str + 1,static_tables<ch_type>::table4[remains1].data(),bytes4);
			memcpy(str + 5,static_tables<ch_type>::table4[remains0].data(),bytes4);
			return 9;
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
	
}

}