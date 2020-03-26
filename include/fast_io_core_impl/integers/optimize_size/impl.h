#pragma once

namespace fast_io::details::optimize_size
{

template<char8_t base=10,bool uppercase=false,std::random_access_iterator Iter,std::unsigned_integral U>
inline constexpr std::size_t output_unsigned(Iter str,U value)
{
	using char_type = std::iter_value_t<Iter>;
	std::size_t const len{chars_len<base>(value)};
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
	return len;
}

}