#pragma once

namespace fast_io
{
namespace manip
{
template<typename T>
struct char_view
{
	T& reference;
};

template<std::integral T>
struct unsigned_view
{
	T& reference;
};

template<std::integral T>
struct signed_view
{
	T& reference;
};

template<std::size_t w,bool left,char8_t char_type,typename T>
struct width
{
	T& reference;
};

template<std::size_t precision,typename T>
struct fixed
{
	T& reference;
};

template<std::size_t precision,bool uppercase_e,typename T>
struct scientific
{
	T& reference;
};

template<typename T>
struct fixed_shortest
{
	T& reference;
};

template<bool uppercase_e,typename T>
struct scientific_shortest
{
	T& reference;
};

template<std::size_t precision,bool uppercase_e,typename T>
struct shortest
{
	T& reference;
};

template<bool uppercase_e,typename T>
struct shortest_shortest
{
	T& reference;
};
//learn from rust
struct from_utf8_unchecked
{
	std::string_view str_view;
};

template<typename T>
struct int_hint
{
	T& reference;
};

template<typename T>
struct unix
{
	T& reference;
};
template<typename T>
struct local
{
	T& reference;
};
template<typename T>
struct utc
{
	T& reference;
};
template<typename T>
struct chinese
{
	T& reference;
};
template<typename T>
struct utc_chinese
{
	T& reference;
};
template<typename T>
struct local_chinese
{
	T& reference;
};

template<typename T>
struct whole
{
	T& reference;
};

template<typename T>
struct line
{
	T& reference;
};

template<typename T>
struct no_decoration
{
	T& reference;
};

template<typename T,std::integral size_type>
struct transmission
{
	size_type& transmitted;
	T& reference;
};

template<typename T,std::integral size_type>
struct transmission_with_size
{
	size_type& transmitted;
	T& reference;
	size_type size;
};

template<typename T,std::integral offset_type,std::integral size_type>
struct random_access_transmission
{
	size_type& transmitted;
	offset_type offset;
	T& reference;
};

template<typename T,std::integral offset_type,std::integral size_type>
struct random_access_transmission_with_size
{
	size_type& transmitted;
	offset_type offset;
	T& reference;
	size_type size;
};

template<typename T>
struct binary_serialization
{
	T& reference;
};

template<typename T,std::integral char_type>
struct follow_character
{
	T& reference;
	char_type character;
};

template<typename status_type,typename T>
struct status_tag
{
	status_type& status;
	T& reference;
};

template<typename T>
struct code_cvt
{
	T& reference;
};

}
template<typename T>
requires (std::floating_point<T>||std::integral<T>)
inline constexpr manip::char_view<T> char_view(T& ch)
{
	return {ch};
}
template<typename T>
requires (std::floating_point<T>||std::integral<T>)
inline constexpr manip::char_view<T const> char_view(T const& ch)
{
	return {ch};
}

template<std::integral T>
inline constexpr decltype(auto) unsigned_view(T& value)
{
	return reinterpret_cast<std::make_unsigned_t<T>&>(value);
}

template<std::integral T>
inline constexpr decltype(auto) signed_view(T& value)
{
	return reinterpret_cast<std::make_signed_t<T>&>(value);
}

template<std::integral T>
inline constexpr decltype(auto) unsigned_view(T const& value)
{
	return reinterpret_cast<std::make_unsigned_t<T const>&>(value);
}

template<std::integral T>
inline constexpr decltype(auto) floating_view(T const& value)
{
	return static_cast<long double>(value);
}

template<std::floating_point F>
inline constexpr decltype(auto) floating_view(F const& p)
{
	return p;
}

template<std::floating_point F>
inline constexpr decltype(auto) int_hint(F const& f)
{
	return manip::int_hint{f};
}

template<std::integral T>
inline constexpr decltype(auto) signed_view(T const& value)
{
	return reinterpret_cast<std::make_signed_t<T const>&>(value);
}

template<typename T>
inline constexpr std::size_t unsigned_view(T * const pointer)
{
	return bit_cast<std::size_t>(pointer);
}

template<std::size_t precision,typename T>
inline constexpr manip::fixed<precision,T const> fixed(T const &f){return {f};}

template<std::size_t precision,typename T>
inline constexpr manip::scientific<precision,false,T const> scientific(T const &f){return {f};}
template<std::size_t precision,typename T>
inline constexpr manip::scientific<precision,true,T const> scientific_upper(T const &f){return {f};}

template<typename T>
inline constexpr manip::scientific_shortest<false,T const> scientific(T const &f){return {f};}
template<typename T>
inline constexpr manip::scientific_shortest<true,T const> scientific_upper(T const &f){return {f};}

template<typename T>
inline constexpr manip::fixed_shortest<T const> fixed(T const &f){return {f};}

template<typename T>
inline constexpr manip::shortest_shortest<false,T const> shortest(T const &f){return {f};}
template<typename T>
inline constexpr manip::shortest_shortest<true,T const> shortest_upper(T const &f){return {f};}
template<typename T>
inline constexpr manip::unix<T const> local(T const &f){return {f};}
template<typename T>
inline constexpr manip::utc<T const> utc(T const &f){return {f};}
template<typename T>
inline constexpr manip::unix<T const> unix(T const &f){return {f};}

template<typename T>
inline constexpr manip::chinese<T const> chinese(T const &f){return {f};}
template<typename T>
inline constexpr manip::local_chinese<T const> local_chinese(T const &f){return {f};}
template<typename T>
inline constexpr manip::utc_chinese<T const> utc_chinese(T const &f){return {f};}

template<typename T>
inline constexpr manip::whole<T> whole(T &f){return {f};}

template<typename T>
inline constexpr manip::line<T> line(T &f){return {f};}

template<typename T>
inline constexpr manip::int_hint<T> integer_hint(T &f){return {f};}

template<typename T>
inline constexpr manip::no_decoration<T> no_decoration(T &f){return {f};}

template<input_stream T,std::integral sz_type>
inline constexpr manip::transmission<T,sz_type> transmission(sz_type& transmitted,T &f){return {transmitted,f};}

template<input_stream T,std::integral sz_type>
inline constexpr manip::transmission_with_size<T,sz_type> transmission(sz_type& transmitted,T &f,sz_type s){return {transmitted,f,s};}

template<input_stream T,std::integral sz_type,std::integral offset_type>
inline constexpr manip::random_access_transmission<T,offset_type,sz_type> random_access_transmission(sz_type& transmitted,offset_type offset,T &f){return {transmitted,offset,f};}

template<input_stream T,std::integral sz_type,std::integral offset_type>
inline constexpr manip::random_access_transmission_with_size<T,offset_type,sz_type> random_access_transmission(sz_type& transmitted,offset_type offset,T &f,sz_type s){return {transmitted,offset,f,s};}

template<std::ranges::range T>
inline constexpr manip::binary_serialization<T> binary_serialization(T &f){return {f};}

template<std::ranges::range T>
inline constexpr manip::binary_serialization<T const> binary_serialization(T const &f){return {f};}

template<typename T,std::integral ch_type>
inline constexpr manip::follow_character<T,ch_type> follow(T &f,ch_type ch){return {f,ch};}

template<typename T,std::integral ch_type>
inline constexpr manip::follow_character<T const,ch_type> follow(T const &f,ch_type ch){return {f,ch};}

template<typename T>
inline constexpr manip::code_cvt<T const> code_cvt(T const&f){return {f};}

/*template<status_stream stm,typename T>
inline constexpr manip::status_tag<typename stm::status_type,T const> status(stm const& t,T ch)
{
	return {f,ch};
}*/

template<character_output_stream output,std::integral T>
inline void print_define(output& out,manip::char_view<T> a)
{
	put(out,static_cast<typename output::char_type>(a.reference));
}

template<std::size_t indent_w,bool left=false,char8_t fill_ch=0x20,typename T>
inline constexpr manip::width<indent_w,left,fill_ch,T const> width(T const& t)
{
	return {t};
}

//https://doc.rust-lang.org/std/str/fn.from_utf8_unchecked.html
//learn from rust
inline constexpr manip::from_utf8_unchecked from_utf8_unchecked(std::string_view char_str_series)
{
	return {char_str_series};
}

template<output_stream output>
requires (std::same_as<typename output::char_type,char8_t>)
inline void print_define(output& out,manip::from_utf8_unchecked a)
{
	write(out,a.str_view);
}

template<output_stream output>
requires (std::same_as<typename output::char_type,char>)
inline void print_define(output& out,std::u8string_view u8vw)
{
	write(out,u8vw);
}

}
