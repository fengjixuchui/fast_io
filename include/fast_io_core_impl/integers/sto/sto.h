#pragma once

namespace fast_io
{
namespace details
{
template<std::integral intg,char8_t base>
requires (2<=base&&base<=36)
inline constexpr std::size_t get_max_size()
{
	std::size_t i{};
	for(auto v(std::numeric_limits<intg>::max());v;++i)
		v/=base;
	return i;
}

template<char8_t base,std::unsigned_integral T>
inline constexpr void detect_overflow(T const& t,std::size_t length)
{
	constexpr std::size_t max_size{get_max_size<T,base>()};
	if(max_size<=length)[[unlikely]]
	{
		if((max_size<length)|(t<=base))[[unlikely]]
#ifdef __cpp_exceptions
			throw std::overflow_error("unsigned overflow");
#else
			fast_terminate();
#endif
	}
}

template<char8_t base,std::unsigned_integral T>
inline constexpr void detect_signed_overflow(T const& t,std::size_t length,bool sign)
{
	constexpr std::size_t max_size{get_max_size<T,base>()};
	if(max_size<=length)[[unlikely]]
	{
		if((max_size<length)|(t<=base))[[unlikely]]
#ifdef __cpp_exceptions
			throw std::overflow_error("signed overflow");
#else
			fast_terminate();
#endif
		if(static_cast<T>(static_cast<T>(std::numeric_limits<std::make_signed_t<T>>::max())+sign)<t)
#ifdef __cpp_exceptions
			throw std::overflow_error("signed overflow");
#else
			fast_terminate();
#endif
	}
}


template<std::integral T,char8_t base,bool no_dec=false,character_input_stream input>
inline constexpr T input_base_number(input& in)
{
	using unsigned_char_type = std::make_unsigned_t<typename input::char_type>;
	using unsigned_t = std::make_unsigned_t<std::remove_cvref_t<T>>;
	if constexpr(std::unsigned_integral<T>)
	{
		unsigned_t t{};
		std::size_t length{};
		for(unsigned_char_type ch : igenerator(in))
		{
			if constexpr(base<=10)
			{
				unsigned_char_type const e(static_cast<unsigned_char_type>(ch)-u8'0');
				if(base<=e)[[unlikely]]
					break;
				t*=base;
				t+=e;
			}
			else
			{
				unsigned_char_type e(static_cast<unsigned_char_type>(ch)-u8'0');
				constexpr char8_t bm10{base-10};
				if(e<=10)
				{
					t*=base;
					t+=e;
				}
				else if(static_cast<unsigned_char_type>(e-=17)<bm10||static_cast<unsigned_char_type>(e-=32)<bm10)
				{
					t*=base;
					t+=e+10;
				}
				else[[unlikely]]
					break;
			}
			++length;
		}
		if(!length)[[unlikely]]
			throw std::runtime_error("malformed input");
		detect_overflow<base>(t,length);
		return t;
	}
	else
	{
		unsigned_t t{};
		std::size_t length{};
		auto ig{igenerator(in)};
		auto it{begin(ig)};
		auto ed{end(ig)};
		if(it==ed)
			throw fast_io::eof();
		auto const sign{*it=='-'};
		if(sign)
			++it;
		for(;it!=ed;++it)
		{
			if constexpr(base<=10)
			{
				unsigned_char_type const e(static_cast<unsigned_char_type>(*it)-u8'0');
				if(base<=e)[[unlikely]]
					break;
				t*=base;
				t+=e;
			}
			else
			{
				unsigned_char_type e(static_cast<unsigned_char_type>(*it)-u8'0');
				constexpr char8_t bm10{base-10};
				if(e<=10)
				{
					t*=base;
					t+=e;
				}
				else if(static_cast<unsigned_char_type>(e-=17)<bm10||static_cast<unsigned_char_type>(e-=32)<bm10)
				{
					t*=base;
					t+=e+10;
				}
				else[[unlikely]]
					break;
			}
			++length;
		}
		detect_signed_overflow<base>(t,length,sign);
		if(sign)
			return -static_cast<T>(t);
		else if(!length)[[unlikely]]
			throw std::runtime_error("malformed input");
		return static_cast<T>(t);
	}
}
}

template<char8_t base,bool uppercase,character_input_stream input,std::integral T>
inline constexpr bool scan_define(input& in,manip::base_t<base,uppercase,T> v)
{
	if(!skip_space(in))
		return false;
	v.reference=details::input_base_number<std::remove_cvref_t<T>,base>(in);
	return true;
}

template<character_input_stream input,std::integral T>
inline constexpr void scan_define(input& in,manip::no_decoration<T> v)
{
	v.reference=details::input_base_number<std::remove_cvref_t<T>,10>(in);
}

template<char8_t base,bool uppercase,character_input_stream input,std::integral T>
inline constexpr void scan_define(input& in,manip::no_decoration<manip::base_t<base,uppercase,T>> v)
{
	v.reference.reference=details::input_base_number<std::remove_cvref_t<T>,base>(in);
}

template<character_input_stream input,std::integral T>
inline constexpr bool scan_define(input& in,T& a)
{
	if(!skip_space(in))
		return false;
	a=details::input_base_number<std::remove_cvref_t<T>,10>(in);
	return true;
}

template<char8_t base,bool uppercase,character_input_stream input,typename T>
requires std::same_as<std::byte,std::remove_cvref_t<T>>
inline constexpr bool scan_define(input& in,manip::base_t<base,uppercase,T> v)
{
	if(!skip_space(in))
		return false;
	v.reference=static_cast<std::byte>(details::input_base_number<char8_t,base>(in));
	return true;
}

template<char8_t base,bool uppercase,character_input_stream input,typename T>
requires std::same_as<std::byte,std::remove_cvref_t<T>>
inline constexpr void scan_define(input& in,manip::no_decoration<manip::base_t<base,uppercase,T>> v)
{
	v.reference.reference=static_cast<std::byte>(details::input_base_number<char8_t,base>(in));
}

}
