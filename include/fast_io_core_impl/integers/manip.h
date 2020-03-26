#pragma once

namespace fast_io
{


namespace manip
{
	
template<char8_t bs,bool uppercase,typename T>
requires (2<=bs&&bs<=36)
struct base_t
{
	T& reference;
};

template<char8_t bs,bool uppercase,typename T,std::integral char_type>
requires (2<=bs&&bs<=36)
struct base_split_t
{
	T& reference;
	char_type character;
};

}

template<char8_t b,bool uppercase=false,typename T>
inline constexpr manip::base_t<b,uppercase,T> base(T& t) {return {t};}
template<char8_t b,bool uppercase=false,typename T>
inline constexpr manip::base_t<b,uppercase,T const> base(T const& t) {return {t};}

template<typename T> inline constexpr manip::base_t<16,false,T> hex(T& t) {return {t};}
template<typename T> inline constexpr manip::base_t<16,false,T const> hex(T const& t){return {t};}

template<typename T> inline constexpr manip::base_t<16,true,T> hexupper(T& t){return {t};}
template<typename T> inline constexpr manip::base_t<16,true,T const> hexupper(T const& t) {return {t};}

template<typename T> inline constexpr manip::base_t<8,false,T> oct(T& t) {return {t};}
template<typename T> inline constexpr manip::base_t<8,false,T const> oct(T const& t){return {t};}

template<typename T> inline constexpr manip::base_t<10,false,T> dec(T& t) {return {t};}
template<typename T> inline constexpr manip::base_t<10,false,T const> dec(T const& t){return {t};}

template<typename T> inline constexpr manip::base_t<2,false,T> bin(T& t){return {t};}
template<typename T> inline constexpr manip::base_t<2,false,T const> bin(T const& t) {return {t};}


template<char8_t b,bool uppercase=false,typename T,std::integral char_type>
inline constexpr manip::base_split_t<b,uppercase,T,char_type> base_split(T& t,char_type ch) {return {t,ch};}
template<char8_t b,bool uppercase=false,typename T,std::integral char_type>
inline constexpr manip::base_split_t<b,uppercase,T const,char_type> base_split(T const& t,char_type ch) {return {t,ch};}

template<typename T,std::integral char_type> inline constexpr manip::base_split_t<16,false,T,char_type> hex_split(T& t,char_type ch) {return {t,ch};}
template<typename T,std::integral char_type> inline constexpr manip::base_split_t<16,false,T const,char_type> hex_split(T const& t,char_type ch){return {t,ch};}

template<typename T,std::integral char_type> inline constexpr manip::base_split_t<16,true,T,char_type> hexupper_split(T& t,char_type ch){return {t,ch};}
template<typename T,std::integral char_type> inline constexpr manip::base_split_t<16,true,T const,char_type> hexupper_split(T const& t,char_type ch) {return {t,ch};}

template<typename T,std::integral char_type> inline constexpr manip::base_split_t<8,false,T,char_type> oct_split(T& t,char_type ch) {return {t,ch};}
template<typename T,std::integral char_type> inline constexpr manip::base_split_t<8,false,T const,char_type> oct_split(T const& t,char_type ch){return {t,ch};}

template<typename T,std::integral char_type> inline constexpr manip::base_split_t<10,false,T,char_type> dec_split(T& t,char_type ch) {return {t,ch};}
template<typename T,std::integral char_type> inline constexpr manip::base_split_t<10,false,T const,char_type> dec_split(T const& t,char_type ch){return {t,ch};}

template<typename T,std::integral char_type> inline constexpr manip::base_split_t<2,false,T,char_type> bin_split(T& t,char_type ch){return {t,ch};}
template<typename T,std::integral char_type> inline constexpr manip::base_split_t<2,false,T const,char_type> bin_split(T const& t,char_type ch) {return {t,ch};}

}