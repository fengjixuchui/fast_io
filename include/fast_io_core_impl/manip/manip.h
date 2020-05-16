#pragma once

namespace fast_io
{

namespace manip
{

template<typename T>
struct char_view
{
	using manip_tag = manip_tag_t;
	T& reference;
};

template<std::integral T>
struct unsigned_view
{
	using manip_tag = manip_tag_t;
	T& reference;
};

template<std::integral T>
struct signed_view
{
	using manip_tag = manip_tag_t;
	T& reference;
};

template<typename T>
struct unix
{
	using manip_tag = manip_tag_t;
	T& reference;
};

template<typename T>
struct local
{
	using manip_tag = manip_tag_t;
	T& reference;
};
template<typename T>
struct utc
{
	using manip_tag = manip_tag_t;
	T& reference;
};
template<typename T>
struct chinese
{
	using manip_tag = manip_tag_t;
	T& reference;
};
template<typename T>
struct utc_chinese
{
	using manip_tag = manip_tag_t;
	T& reference;
};
template<typename T>
struct local_chinese
{
	using manip_tag = manip_tag_t;
	T& reference;
};

template<typename T>
struct whole
{
	using manip_tag = manip_tag_t;
	T& reference;
};

template<typename T>
struct line
{
	using manip_tag = manip_tag_t;
	T reference;
};

template<typename T>
struct no_decoration
{
	using manip_tag = manip_tag_t;
	T& reference;
};

template<typename T,std::integral size_type>
struct transmission
{
	using manip_tag = manip_tag_t;
	size_type& transmitted;
	T& reference;
};

template<typename T,std::integral size_type>
struct transmission_with_size
{
	using manip_tag = manip_tag_t;
	size_type& transmitted;
	T& reference;
	size_type size;
};

template<typename T,std::integral offset_type,std::integral size_type>
struct random_access_transmission
{
	using manip_tag = manip_tag_t;
	size_type& transmitted;
	offset_type offset;
	T& reference;
};

template<typename T,std::integral offset_type,std::integral size_type>
struct random_access_transmission_with_size
{
	using manip_tag = manip_tag_t;
	size_type& transmitted;
	offset_type offset;
	T& reference;
	size_type size;
};

template<typename T>
struct binary_serialization
{
	using manip_tag = manip_tag_t;
	T& reference;
};

template<typename T,std::integral char_type>
struct follow_character
{
	using manip_tag = manip_tag_t;
	T& reference;
	char_type character;
};

template<typename status_type,typename T>
struct status_tag
{
	using manip_tag = manip_tag_t;
	status_type& status;
	T& reference;
};

template<typename T>
struct code_cvt
{
	using manip_tag = manip_tag_t;
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
inline constexpr decltype(auto) signed_view(T const& value)
{
	return reinterpret_cast<std::make_signed_t<T const>&>(value);
}

template<typename T>
inline constexpr std::size_t unsigned_view(T * const pointer)
{
	return bit_cast<std::size_t>(pointer);
}


template<typename T>
inline constexpr manip::local<T const> local(T const &f){return {f};}

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
inline constexpr manip::line<T&> line(T &f){return {f};}

template<typename T>
inline constexpr manip::line<T> line(T&& f){return {std::move(f)};}

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

template<output_stream output>
requires (std::same_as<typename output::char_type,char>)
inline void print_define(output& out,std::u8string_view u8vw)
{
	write(out,u8vw);
}


}
