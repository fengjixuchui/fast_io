#pragma once

namespace fast_io
{
/*
template<bool uppercase=false,typename T>
inline constexpr manip::comma_decimal_point<T&> comma(T&f){return {f};}
*/
template<typename T>
inline constexpr manip::comma<T&> comma(T&&f){return {f};}
template<bool uppercase=false,typename T>
inline constexpr manip::comma<manip::general<false,T const>> comma_general(T const &f){return {{f}};}
template<bool uppercase=false,typename T>
inline constexpr manip::comma<manip::general_precision<uppercase,T const>> comma_general(T const &f,std::size_t precision){return {{f,precision}};}

template<typename T>
inline constexpr manip::comma<manip::fixed_precision<T const>> comma_fixed(T const &f,std::size_t precision){return {{f,precision}};}
template<typename T>
inline constexpr manip::comma<manip::fixed<T const>> comma_fixed(T const &f){return {{f}};}

template<bool uppercase=false,typename T>
inline constexpr manip::comma<manip::scientific<uppercase,T const>> comma_scientific(T const &f){return {{f}};}

template<bool uppercase=false,typename T>
inline constexpr manip::comma<manip::scientific_precision<uppercase,T const>> comma_scientific(T const &f,std::size_t precision){return {{f,precision}};}


}