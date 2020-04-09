#pragma once
#include"ryu/ryu.h"
//#include"grisu_exact/grisu_exact.h"
//#include"grisu_exact/grisu_exact_api.h"

namespace fast_io
{

template<buffer_input_stream input,std::floating_point T>
inline constexpr bool scan_define(input& in,T &t)
{
	if(!skip_space(in))
		return false;
	auto igen{igenerator(in)};
	t=static_cast<std::remove_cvref_t<T>>(details::ryu::input_floating<u8'.',double>(begin(igen),end(igen)));
	return true;
}

template<char32_t dec,buffer_input_stream input,std::floating_point T>
inline constexpr bool scan_define(input& in,manip::decimal_point<T&,dec> t)
{
	if(!skip_space(in))
		return false;
	auto igen{igenerator(in)};
	t.value=static_cast<std::remove_cvref_t<T>>(details::ryu::input_floating<dec,double>(begin(igen),end(igen)));
	return true;
}

template<manip::floating_formats fm,bool uppercase,std::floating_point T,char32_t dec>
inline constexpr std::size_t print_reserve_size
	(print_reserve_type_t<manip::decimal_point<manip::floating_manip_precision<fm,uppercase,T const>,dec>>)
{
	if constexpr(fm==manip::floating_formats::general||fm==manip::floating_formats::fixed)
		return 2048;
	else if constexpr(fm==manip::floating_formats::scientific)
		return 1024;
}

template<std::random_access_iterator raiter,manip::floating_formats fm,std::floating_point T,bool uppercase,char32_t dec,typename U>
requires (dec<std::numeric_limits<std::iter_value_t<raiter>>::max())
inline raiter print_reserve_define(print_reserve_type_t<manip::decimal_point<manip::floating_manip_precision<fm,uppercase,T const>,dec>>,raiter start,U a)
{
	if constexpr(fm==manip::floating_formats::fixed)
	{
		if(1024<a.value.precision)
			throw std::runtime_error("precision too large");
		return details::ryu::output_fixed<dec,false,uppercase>(start,a.value.reference,a.value.precision);
	}
	else if constexpr(fm==manip::floating_formats::scientific)
	{
		if(512<a.value.precision)
			throw std::runtime_error("precision too large");
		return details::ryu::output_fixed<dec,true,uppercase>(start,a.value.reference,a.value.precision);
	}
	else if constexpr(fm==manip::floating_formats::general)
	{
		if(1024<a.value.precision)
			throw std::runtime_error("precision too large");
		auto fixed_iter{details::ryu::output_fixed<dec,false,uppercase>(start,a.value.reference,a.value.precision)};
		std::array<std::iter_value_t<raiter>,512> scientific;
		auto scientific_it{details::ryu::output_fixed<dec,true,uppercase>(scientific.data(),a.value.reference,a.value.precision)};
		if(scientific_it-scientific.data()<fixed_iter-start)[[unlikely]]
		{
			details::my_copy(scientific.data(),scientific_it,start);
			return start+(scientific_it-scientific.data());
		}
		return fixed_iter;
	}
}

template<std::floating_point T>
inline constexpr std::size_t print_reserve_size(print_reserve_type_t<T>)
{
	return 30;
}

template<std::random_access_iterator raiter,std::floating_point T>
inline raiter print_reserve_define(print_reserve_type_t<T>,raiter start,T a)
{
	return details::ryu::output_shortest<u8'.',false,0,true>(start,static_cast<double>(a));
}

template<manip::floating_formats fm,bool uppercase,std::floating_point T,char32_t dec>
inline constexpr std::size_t print_reserve_size
	(print_reserve_type_t<manip::decimal_point<manip::floating_manip<fm,uppercase,T const>,dec>>)
{
	if constexpr(fm==manip::floating_formats::general||fm==manip::floating_formats::scientific)
		return 30;
	else if constexpr(fm==manip::floating_formats::fixed)
		return 350;
}

template<std::random_access_iterator raiter,manip::floating_formats fm,std::floating_point T,bool uppercase,char32_t dec,typename U>
requires (dec<std::numeric_limits<std::iter_value_t<raiter>>::max())
inline raiter print_reserve_define(print_reserve_type_t<manip::decimal_point<manip::floating_manip<fm,uppercase,T const>,dec>>,raiter start,U a)
{
	if constexpr(fm==manip::floating_formats::general)
		return details::ryu::output_shortest<dec,uppercase,0,true>(start,static_cast<double>(a.value.reference));
	else if constexpr(fm==manip::floating_formats::fixed)
		return details::ryu::output_shortest<dec,false,1,true>(start,static_cast<double>(a.value.reference));
	else if constexpr(fm==manip::floating_formats::scientific)
		return details::ryu::output_shortest<dec,uppercase,2,true>(start,static_cast<double>(a.value.reference));
}

template<std::floating_point T,char32_t dec>
inline constexpr std::size_t print_reserve_size
	(print_reserve_type_t<manip::decimal_point<T&,dec>>)
{
	return 30;
}

template<std::random_access_iterator raiter,std::floating_point T,char32_t dec,typename U>
requires (dec<std::numeric_limits<std::iter_value_t<raiter>>::max())
inline raiter print_reserve_define(print_reserve_type_t<manip::decimal_point<T&,dec>>,raiter start,U a)
{
	return details::ryu::output_shortest<dec,false,0,true>(start,static_cast<double>(a.value));
}

}
