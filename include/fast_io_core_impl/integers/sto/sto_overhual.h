#pragma once

namespace fast_io
{

namespace details
{

template<::fast_io::freestanding::random_access_iterator Iter>
inline constexpr Iter skip_zero(Iter begin, Iter end) noexcept
{
	using char_type = ::fast_io::freestanding::iter_value_t<Iter>;
	if constexpr(std::same_as<char_type,char>)
		for (; begin != end && *begin=='0'; ++begin);
	else if constexpr(std::same_as<char_type,wchar_t>)
		for (; begin != end && *begin==L'0'; ++begin);
	else
		for (; begin != end && *begin==u8'0'; ++begin);
	return begin;
}

template<char8_t base,std::integral char_type>
requires (2<=base&&base<=36)
inline constexpr bool char_digit_to_literal(my_make_unsigned_t<char_type>& ch) noexcept
{
	using unsigned_char_type = my_make_unsigned_t<char_type>;
	constexpr bool ebcdic{exec_charset_is_ebcdic<char_type>()};
	constexpr unsigned_char_type base_char_type(base);
	if constexpr(base<=10)
	{
		if constexpr(ebcdic)
			ch-=static_cast<unsigned_char_type>(240);
		else
			ch-=static_cast<unsigned_char_type>(u8'0');
		return base_char_type<=ch;
	}
	else
	{
		if constexpr(ebcdic)
		{

			if constexpr(base<=19)
			{
				constexpr unsigned_char_type mns{base-10};
				unsigned_char_type ch2(ch);
				ch2-=0xC1;
				unsigned_char_type ch3(ch);
				ch3-=0x81;
				ch-=0xF0;
				if(ch2<mns)
					ch=ch2+static_cast<unsigned_char_type>(10);
				else if(ch3<mns)
					ch=ch3+static_cast<unsigned_char_type>(10);
				else if(10<=ch)
					return true;
				return false;
			}
			else if constexpr(base<=28)
			{
				constexpr unsigned_char_type mns{base-19};
				unsigned_char_type ch2(ch);
				ch2-=0xC1;
				unsigned_char_type ch3(ch);
				ch3-=0x81;
				unsigned_char_type ch4(ch);
				ch2-=0xD1;
				unsigned_char_type ch5(ch);
				ch3-=0x91;
				ch-=0xF0;
				if(ch4<mns)
					ch=ch4+static_cast<unsigned_char_type>(19);
				else if(ch5<mns)
					ch=ch5+static_cast<unsigned_char_type>(19);
				else if(ch2<9)
					ch=ch2+static_cast<unsigned_char_type>(10);
				else if(ch3<9)
					ch=ch3+static_cast<unsigned_char_type>(10);
				else if(10<=ch)
					return true;
				return false;
			}
			else
			{
				constexpr unsigned_char_type mns{base-27};
				unsigned_char_type ch2(ch);
				ch2-=0xC1;
				unsigned_char_type ch3(ch);
				ch3-=0x81;
				unsigned_char_type ch4(ch);
				ch4-=0xD1;
				unsigned_char_type ch5(ch);
				ch5-=0x91;
				unsigned_char_type ch6(ch);
				ch6-=0xE2;
				unsigned_char_type ch7(ch);
				ch7-=0xA2;
				ch-=0xF0;
				if(ch6<mns)
					ch=ch6+static_cast<unsigned_char_type>(27);
				else if(ch7<mns)
					ch=ch7+static_cast<unsigned_char_type>(27);
				else if(ch4<9)
					ch=ch4+static_cast<unsigned_char_type>(19);
				else if(ch5<9)
					ch=ch5+static_cast<unsigned_char_type>(19);
				else if(ch2<9)
					ch=ch2+static_cast<unsigned_char_type>(10);
				else if(ch3<9)
					ch=ch3+static_cast<unsigned_char_type>(10);
				else if(10<=ch)
					return true;
				return false;
			}
		}
		else
		{
			constexpr unsigned_char_type mns{base-10};
			unsigned_char_type ch2(ch);
			ch2-=u8'A';
			unsigned_char_type ch3(ch);
			ch3-=u8'a';
			ch-=u8'0';
			if(ch2<mns)
				ch=ch2+static_cast<unsigned_char_type>(10);
			else if(ch3<mns)
				ch=ch3+static_cast<unsigned_char_type>(10);
			else if(10<=ch)
				return true;
			return false;
		}
	}
}

template<char8_t base,std::integral char_type>
requires (2<=base&&base<=36)
inline constexpr bool char_digit_probe_overflow(my_make_unsigned_t<char_type> ch) noexcept
{
	using unsigned_char_type = my_make_unsigned_t<char_type>;
	constexpr bool ebcdic{exec_charset_is_ebcdic<char_type>()};
	constexpr unsigned_char_type base_char_type(base);
	if constexpr(base<=10)
	{
		if constexpr(ebcdic)
			ch-=static_cast<unsigned_char_type>(240);
		else
			ch-=static_cast<unsigned_char_type>(u8'0');
		return ch<base_char_type;
	}
	else
	{
		if constexpr(ebcdic)
		{
			if constexpr(base<=19)
			{
				constexpr unsigned_char_type mns{base-10};
				unsigned_char_type ch2(ch);
				ch2-=0xC1;
				unsigned_char_type ch3(ch);
				ch3-=0x81;
				ch-=0xF0;
				return (ch2<mns)|(ch3<mns)|(ch<10u);
			}
			else if constexpr(base<=28)
			{
				constexpr unsigned_char_type mns{base-19};
				unsigned_char_type ch2(ch);
				ch2-=0xC1;
				unsigned_char_type ch3(ch);
				ch3-=0x81;
				unsigned_char_type ch4(ch);
				ch2-=0xD1;
				unsigned_char_type ch5(ch);
				ch3-=0x91;
				ch-=0xF0;
				return (ch4<mns)|(ch5<mns)|(ch2<mns)|(ch3<9)|(ch<10u);
			}
			else
			{
				constexpr unsigned_char_type mns{base-27};
				unsigned_char_type ch2(ch);
				ch2-=0xC1;
				unsigned_char_type ch3(ch);
				ch3-=0x81;
				unsigned_char_type ch4(ch);
				ch4-=0xD1;
				unsigned_char_type ch5(ch);
				ch5-=0x91;
				unsigned_char_type ch6(ch);
				ch6-=0xE2;
				unsigned_char_type ch7(ch);
				ch7-=0xA2;
				ch-=0xF0;
				return (ch6<mns)|(ch7<mns)|(ch4<9u)|(ch5<9u)|(ch2<9u)|(ch3<9u)|(ch<10u);
			}
		}
		else
		{
			constexpr unsigned_char_type mns{base-10};
			unsigned_char_type ch2(ch);
			ch2-=u8'A';
			unsigned_char_type ch3(ch);
			ch3-=u8'a';
			ch-=u8'0';
			return (ch2<mns)|(ch3<mns)|(ch<10u);
		}
	}
}

template<char8_t base,::fast_io::freestanding::random_access_iterator Iter,my_unsigned_integral muint>
inline constexpr void from_chars_main(Iter& b,Iter e,muint& res) noexcept
{
	using char_type = ::fast_io::freestanding::iter_value_t<Iter>;
	using unsigned_char_type = my_make_unsigned_t<char_type>;
	constexpr unsigned_char_type base_char_type(base);
	for(;b!=e;++b)
	{
		unsigned_char_type result(*b);
		if(char_digit_to_literal<base,char_type>(result))[[unlikely]]
			break;
		res*=base_char_type;
		res+=result;
	}
}

template<char8_t base,::fast_io::freestanding::random_access_iterator Iter>
inline constexpr Iter skip_digits(Iter b,Iter e) noexcept
{
	using char_type = ::fast_io::freestanding::iter_value_t<Iter>;
	using unsigned_char_type = my_make_unsigned_t<char_type>;
	for(;b!=e;++b)
	{
		unsigned_char_type result(*b);
		if(char_digit_to_literal<base,char_type>(result))
			break;
	}
	return b;
}

template<char8_t base,bool larger_than_native = false,::fast_io::freestanding::random_access_iterator Iter,my_unsigned_integral muint>
inline constexpr bool probe_overflow(Iter& b,Iter e,muint& res,std::size_t& sz) noexcept
{
	using char_type = ::fast_io::freestanding::iter_value_t<Iter>;
	using unsigned_char_type = my_make_unsigned_t<char_type>;
	if(b==e)
		return false;
	unsigned_char_type result(*b);
	if(char_digit_to_literal<base,char_type>(result))[[unlikely]]
		return false;
	constexpr muint risky_uint_max{static_cast<muint>(-1)};
	constexpr muint risky_value{risky_uint_max/base};
	constexpr unsigned_char_type risky_digit(risky_uint_max%base);
	constexpr std::size_t npos(static_cast<std::size_t>(-1));
	if((risky_value<res)||(risky_value==res&&risky_digit<result))
	{
		if constexpr (!larger_than_native)
			sz=npos;
		return true;
	}
	res*=base;
	res+=result;
	++b;
	if constexpr(larger_than_native)
		++sz;
	if(b==e)
		return false;
	if constexpr (!larger_than_native)
	{
		unsigned_char_type result1(static_cast<unsigned_char_type>(*b));
		if(!char_digit_probe_overflow<base,char_type>(result1))
			return false;
		sz=npos;
		++b;
		b=skip_digits<base>(b,e);
		return true;
	}
	else
	{
		unsigned_char_type result(static_cast<unsigned_char_type>(*b));
		return char_digit_probe_overflow<base,char_type>(result);
	}
}

template<char8_t base,bool larger_than_native = false, bool skip_zeros = true, bool ignore=false, ::fast_io::freestanding::random_access_iterator Iter,my_unsigned_integral muint>
#if __has_cpp_attribute(msvc::forceinline) && !defined(__clang__)
[[msvc::forceinline]]
#endif
inline constexpr bool from_chars(Iter& b,Iter e,muint& res,std::size_t& sz) noexcept
{
	constexpr std::size_t max_size{cal_max_int_size<muint,base>()-1};
	if constexpr(ignore)
	{
		if constexpr(skip_zeros)
			b=skip_zero(b,e);
		std::size_t iter_diff(e-b);
		if(max_size<iter_diff)[[likely]]
		{
			iter_diff=max_size;
			auto from_chars_ed{b+max_size};
			auto start{b};
			from_chars_main<base>(b,from_chars_ed,res);
			sz=b-start;
			if(b==from_chars_ed)[[unlikely]]
			{
				return probe_overflow<base, larger_than_native>(b,e,res,sz);
			}
		}
		else
		{
			auto start{b};
			from_chars_main<base>(b,e,res);
			sz=b-start;
		}
	}
	else
	{
		constexpr std::size_t npos(static_cast<std::size_t>(-1));
		if(sz==npos)
		{
			b=skip_digits<base>(b,e);
			return true;
		}
		if constexpr(skip_zeros)
		{
			if(!res)
				b=skip_zero(b,e);
		}
		std::size_t iter_diff(static_cast<std::size_t>(e-b));
		std::size_t max_size_msz(max_size-sz);
		if(max_size_msz<iter_diff)[[likely]]
		{
			iter_diff=max_size_msz;
			auto from_chars_ed{b+max_size_msz};
			auto start{b};
			from_chars_main<base>(b,from_chars_ed,res);
			sz+=b-start;
			if(b==from_chars_ed)[[unlikely]]
				return probe_overflow<base, larger_than_native>(b,e,res,sz);
		}
		else
		{
			auto start{b};
			from_chars_main<base>(b,e,res);
			sz+=b-start;
		}
	}
	return false;
}


template<char8_t base, details::my_integral T>
inline constexpr auto powmul_array() noexcept
{
	constexpr std::size_t charlen{chars_len<base>(cal_int_max<T>())};
	::fast_io::freestanding::array<T, charlen> arr{1};
	for(std::size_t i{1};i!=charlen;++i)
		arr[i] = arr[i-1] * base;
	return arr;
}

template<char8_t base, details::my_integral T>
inline constexpr auto powmul_table{powmul_array<base, T>()};

template<char8_t base, details::my_integral T>
inline constexpr T powmul(T v, std::size_t sz) noexcept
{
	// powmul(v,sz)=v*(base^sz)
	// make a table
#ifdef __OPTIMIZE_SIZE__
	for (std::size_t i{};i!=sz;++i)
		v *= base;
#else
	return v * powmul_table<base, T>[sz];
#endif
}

} // end details

template<details::my_integral T, ::fast_io::freestanding::random_access_iterator Iter>
inline constexpr Iter scan_skip_define(scan_skip_type_t<parameter<T&>>, Iter beg, Iter ed) noexcept
{
	return scan_skip_space(beg, ed);
}

namespace details::ctx_scan_integer
{
template<char8_t base, bool contiguous_only, ::fast_io::freestanding::random_access_iterator Iter,typename P, details::my_integral T>
struct voldmort
{
	Iter iter;
	parse_code code{};

#if __has_cpp_attribute(no_unique_address)
[[no_unique_address]]
#endif
	std::conditional_t<contiguous_only, details::empty,my_make_unsigned_t<T>> value{};
#if __has_cpp_attribute(no_unique_address)
[[no_unique_address]]
#endif
	std::conditional_t<contiguous_only, details::empty,std::size_t> size{};
#if __has_cpp_attribute(no_unique_address)
[[no_unique_address]]
#endif
	std::conditional_t<!contiguous_only&&details::my_signed_integral<T>, bool, empty> minus{};

	inline constexpr bool test_eof(P t) noexcept requires(!contiguous_only)
	{
		constexpr std::size_t npos(static_cast<std::size_t>(-1));
		if(size==npos)
		{
			code=parse_code::overflow;
			return true;
		}
		code={};
		// check minus overflow
		if constexpr(!std::unsigned_integral<T>)
		{
			if(value>static_cast<my_make_unsigned_t<T>>(std::numeric_limits<T>::max())+minus)
			{
				code=parse_code::overflow;
				return true;
			}
		}
		if constexpr(my_signed_integral<T>)
		{
			if(minus)
				t.reference=static_cast<std::uint64_t>(0)-value;
			else
				t.reference=value;
		}
		else
			t.reference=value;
		return true;
	}
	inline constexpr void operator()(Iter begin, Iter end,P t) noexcept requires(!contiguous_only)
	{
		constexpr bool larger_than_native = sizeof(T) > sizeof(std::size_t);
		constexpr std::size_t npos(static_cast<std::size_t>(-1));
		iter=begin;
		if constexpr(larger_than_native)
		{
			std::conditional_t<sizeof(std::size_t)<=sizeof(std::uint32_t), std::uint32_t, std::uint64_t> value_native{};
			for (;size!=npos;) {
				std::size_t sz_tmp{};
				if (details::from_chars<base, larger_than_native, false>(iter,end,value_native,sz_tmp))
				{
					// native value overflow
					value = details::powmul<base>(value, sz_tmp);
					value += static_cast<T>(value_native);
					size += sz_tmp;
					probe_overflow<base, larger_than_native>(iter,end,value,size);
				}
				else
				{
					value = details::powmul<base>(value, sz_tmp);
					value += static_cast<T>(value_native);
					size += sz_tmp;
					break;
				}
			}
		} else {
			details::from_chars<base, larger_than_native, false>(iter,end,value,size);
		}
		code = {};
		if(iter==end)
		{
			code = parse_code::partial;
			return;
		}
		if(size==npos)
		{
			code=parse_code::overflow;
			return;
		}
		// check minus overflow
		if constexpr(!std::unsigned_integral<T>)
		{
			if(value>static_cast<my_make_unsigned_t<T>>(std::numeric_limits<T>::max())+minus)
			{
				code=parse_code::overflow;
				return;
			}
		}
		if constexpr(my_signed_integral<T>)
		{
			if(minus)
				t.reference=static_cast<T>(0)-static_cast<T>(value);
			else
				t.reference=value;
		}
		else
			t.reference=value;
	}
	inline constexpr voldmort(Iter begin, Iter end, T& t) noexcept
	{
		constexpr bool larger_than_native = sizeof(T) > sizeof(std::size_t);
		constexpr std::size_t npos(static_cast<std::size_t>(-1));
		iter = begin;
		if constexpr (contiguous_only)
		{
			
			bool minus{};
			using char_type = ::fast_io::freestanding::iter_value_t<Iter>;
			/*Dealing with EBCDIC exec-charset */
			if constexpr(my_signed_integral<T>)
			{
				if constexpr(std::same_as<char_type,char>)
					minus=(*iter == '-');
				else if constexpr(std::same_as<char_type,wchar_t>)
					minus=(*iter == L'-');
				else
					minus=(*iter == u8'-');
				if constexpr(::fast_io::freestanding::contiguous_iterator<Iter>)
					iter+=minus;
				else
				{
					if(minus)
						++iter;
				}
			}
			my_make_unsigned_t<T> temp{};
			std::size_t size{};
			if constexpr(larger_than_native)
			{
				std::conditional_t<sizeof(std::size_t)<=sizeof(std::uint32_t), std::uint32_t, std::uint64_t> value_native{};
				if (details::from_chars<base, larger_than_native>(iter,end,value_native,size)) [[unlikely]]
				{
					// native value overflow
					temp = static_cast<T>(value_native);
					for (;size!=npos;) {
						std::size_t sz_tmp{};
						value_native = 0;
						if (details::from_chars<base, larger_than_native, false>(iter,end,value_native,sz_tmp)) [[unlikely]]
						{
							// native value overflow
							temp = details::powmul<base>(temp, sz_tmp);
							temp += static_cast<T>(value_native);
							size += sz_tmp;
							if (probe_overflow<base, larger_than_native>(iter,end,temp,size))
							{
								// value overflow
								code=parse_code::overflow;
								return;
							}
						}
						else
						{
							temp = details::powmul<base>(temp, sz_tmp);
							size += sz_tmp;
							temp += static_cast<T>(value_native);
							break;
						}
					}
				}
				else
				{
					temp = static_cast<T>(value_native);
				}
			} else {
				if(details::from_chars<base>(iter,end,temp,size))
				{
					code=parse_code::overflow;
					return;
				}
			}
			if(begin==iter)
			{
				code=parse_code::invalid;
				return;
			}
			if(size==npos)
			{
				code=parse_code::overflow;
				return;
			}
			// check minus overflow
			if constexpr(!my_unsigned_integral<T>)
			{
				constexpr my_make_unsigned_t<T> int_type_max(static_cast<my_make_unsigned_t<T>>(-1)>>1);
				if(temp>int_type_max+minus)
				{
					code=parse_code::overflow;
					return;
				}
			}
			if constexpr(my_signed_integral<T>)
			{
				if(minus)
					t=static_cast<T>(0)-static_cast<T>(temp);
				else
					t=temp;
			}
			else
				t=temp;
		}
		else
		{
			// not contiguous
			using char_type = ::fast_io::freestanding::iter_value_t<Iter>;
			/*Dealing with EBCDIC exec-charset */
			if constexpr(my_signed_integral<T>)
			{
				if constexpr(std::same_as<char_type,char>)
					minus=(*iter == '-');
				else if constexpr(std::same_as<char_type,wchar_t>)
					minus=(*iter == L'-');
				else
					minus=(*iter == u8'-');
				if constexpr(::fast_io::freestanding::contiguous_iterator<Iter>)
					iter+=minus;
				else
				{
					if(minus)
						++iter;
				}
			}

			if constexpr(larger_than_native)
			{
				std::conditional_t<sizeof(std::size_t)<=sizeof(std::uint32_t), std::uint32_t, std::uint64_t> value_native{};
				if (details::from_chars<base, larger_than_native>(iter,end,value_native,size)) [[unlikely]]
				{
					// native value overflow
					value = static_cast<T>(value_native);
					for (;size != npos;) {
						std::size_t sz_tmp{};
						value_native = 0;
						if (details::from_chars<base, larger_than_native, false>(iter,end,value_native,sz_tmp)) [[unlikely]]
						{
							// native value overflow
							value = details::powmul<base>(value, sz_tmp);
							value += static_cast<T>(value_native);
							size += sz_tmp;
							if (probe_overflow<base, larger_than_native>(iter,end,value,size))
							{
								// value overflow
								code=parse_code::overflow;
								return;
							}
						}
						else
						{
							value = details::powmul<base>(value, sz_tmp);
							size += sz_tmp;
							value += static_cast<T>(value_native);
							break;
						}
					}
				}
				else
				{
					value = static_cast<T>(value_native);
				}
			} else {
				details::from_chars<base,larger_than_native,true>(iter,end,value,size);
			}

			if(begin==iter)
			{
				code=parse_code::invalid;
				return;
			}
			if(iter==end)
			{
				code=parse_code::partial;
				return;
			}
			if(size==npos)
			{
				code=parse_code::overflow;
				return;
			}
			// check minus overflow
			if constexpr(!my_unsigned_integral<T>)
			{
				if(value>static_cast<my_make_unsigned_t<T>>(std::numeric_limits<T>::max())+minus)
				{
					code=parse_code::overflow;
					return;
				}
			}
			if constexpr(my_signed_integral<T>)
			{
				if(minus)
					t=static_cast<T>(0)-static_cast<T>(value);
				else
					t=value;
			}
			else
				t=value;
		}
	}
};
}

template<bool contiguous_only, ::fast_io::freestanding::random_access_iterator Iter, details::my_integral T>
inline constexpr auto scan_context_define(scan_context_t<contiguous_only>, Iter begin, Iter end, parameter<T&> t) noexcept
{
	return details::ctx_scan_integer::voldmort<10, contiguous_only, Iter, parameter<T&>, T>(begin, end, t.reference);
}


template<std::size_t base,bool cs, details::my_integral T, ::fast_io::freestanding::random_access_iterator Iter>
inline constexpr Iter scan_skip_define(scan_skip_type_t<manipulators::base_t<base,cs,T&>>, Iter beg, Iter ed) noexcept
{
	return scan_skip_space(beg, ed);
}

template<bool contiguous_only, ::fast_io::freestanding::random_access_iterator Iter,std::size_t base,bool cs,details::my_integral T>
inline constexpr auto scan_context_define(scan_context_t<contiguous_only>, Iter begin, Iter end, manipulators::base_t<base,cs,T&> t) noexcept
{
	return details::ctx_scan_integer::voldmort<base, contiguous_only, Iter, manipulators::base_t<base,false,T&>, T>(begin, end, t.reference);
}

}
