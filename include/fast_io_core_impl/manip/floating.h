#pragma once

namespace fast_io::manip
{

enum class floating_formats
{
general=0,
scientific=1,
fixed=2,
hexfloat=3
};

template<floating_formats fm,bool uppercase,typename T>
struct floating_manip
{
	T& reference;
};

template<floating_formats fm,bool uppercase,typename T>
struct floating_manip_precision
{
	T& reference;
	std::size_t precision;
};

template<bool uppercase,typename T>
using general = floating_manip<floating_formats::general,uppercase,T>;

template<typename T>
using fixed = floating_manip<floating_formats::fixed,false,T>;

template<bool uppercase,typename T>
using scientific = floating_manip<floating_formats::scientific,uppercase,T>;

template<bool uppercase,typename T>
using general_precision = floating_manip_precision<floating_formats::general,uppercase,T>;

template<typename T>
using fixed_precision = floating_manip_precision<floating_formats::fixed,false,T>;

template<bool uppercase,typename T>
using scientific_precision = floating_manip_precision<floating_formats::scientific,uppercase,T>;
/*
template<typename T>
struct int_hint
{
	T& reference;
};
*/
}