#pragma once
#undef unix
namespace fast_io
{

namespace manip
{


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
	T reference;
};

template<typename T,typename Func>
struct space
{
	using manip_tag = manip_tag_t;
	T reference;
	Func function;
};

template<typename T>
struct drainage
{
	using manip_tag = manip_tag_t;
	T reference;
};

template<typename T,char8_t base,bool uppercase,bool space>
requires ((base==2&&!uppercase)||base==16)
struct representation
{
	using manip_tag = manip_tag_t;
	T reference;
};


}

template<output_stream T>
inline constexpr manip::drainage<T&> drainage(T&& age)
{
	return {age};
}

template<typename T>
struct chinese
{
	using manip_tag = manip_tag_t;
	T reference;
};

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

template<typename T,std::integral ch_type>
inline constexpr manip::follow_character<T,ch_type> follow(T &f,ch_type ch){return {f,ch};}

template<typename T,std::integral ch_type>
inline constexpr manip::follow_character<T const,ch_type> follow(T const &f,ch_type ch){return {f,ch};}


template<char8_t base,bool uppercase=false,bool space=true,typename T>
requires ((base==2&&!uppercase)||base==16)
inline constexpr manip::representation<T,base,uppercase,space> representation(T const&f){return {f};}

template<typename T,typename Func>
inline constexpr manip::space<T&,Func&> space(T&& f,Func&& func){return {f,func};}


}
