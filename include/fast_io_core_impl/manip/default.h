#pragma once

namespace fast_io
{

template<bool uppercase=false,typename T>
inline constexpr manip::dot<manip::general<false,T const>> general(T const &f){return {{f}};}

template<bool uppercase=false,typename T>
inline constexpr manip::dot<manip::general_precision<false,T const>> general(T const &f,std::size_t precision){return {{f,precision}};}

template<typename T>
inline constexpr manip::dot<manip::fixed_precision<T const>> fixed(T const &f,std::size_t precision){return {{f,precision}};}
template<typename T>
inline constexpr manip::dot<manip::fixed<T const>> fixed(T const &f){return {{f}};}

template<bool uppercase=false,typename T>
inline constexpr manip::dot<manip::general<uppercase,T const>> scientific(T const &f){return {{f}};}

template<bool uppercase=false,typename T>
inline constexpr manip::dot<manip::scientific_precision<uppercase,T const>> scientific(T const &f,std::size_t precision){return {{f,precision}};}

}