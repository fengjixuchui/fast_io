#pragma once

namespace fast_io::details::optimize_size
{

template<std::size_t len,char8_t base=10,bool uppercase=false,std::random_access_iterator Iter,my_unsigned_integral U>
inline constexpr void output_unsigned_dummy(Iter str,U value)
{
	using char_type = std::iter_value_t<Iter>;
	str+=len-1;
	for(std::size_t i{};i!=len;++i)
	{
		U const temp(value/base);
		char_type const res(value%base);
		if constexpr(base<=10)
			*str=u8'0'+res;
		else
		{
			if(res<10)
				*str=u8'0'+res;
			else
			{
				if constexpr(uppercase)
					*str=(u8'A'-10)+res;
				else
					*str=(u8'a'-10)+res;
			}
		}
		--str;
		value = temp;
	}
}

namespace with_length
{
template<char8_t base=10,bool uppercase=false,std::random_access_iterator Iter,my_unsigned_integral U>
inline constexpr void output_unsigned(Iter str,U value,std::size_t const len)
{
	using char_type = std::iter_value_t<Iter>;
	str+=len;
	for(std::size_t i{};i!=len;++i)
	{
		U const temp(value/base);
		char_type const res(value%base);
		if constexpr(base<=10)
			*--str=u8'0'+res;
		else
		{
			--str;
			if(res<10)
				*str=u8'0'+res;
			else
			{
				if constexpr(uppercase)
					*str=(u8'A'-10)+res;
				else
					*str=(u8'a'-10)+res;
			}
		}
		value = temp;
	}
}
}

template<char8_t base=10,bool uppercase=false,std::random_access_iterator Iter,my_unsigned_integral U>
inline constexpr std::size_t output_unsigned(Iter str,U value)
{
	std::size_t const len{chars_len<base>(value)};
	with_length::output_unsigned(str,value,len);
	return len;
}

}