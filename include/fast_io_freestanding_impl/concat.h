#pragma once

namespace fast_io
{
//potential constexpr in the future if std::string can be constexpr


namespace details
{

template <typename T>
struct is_std_string
{
inline static constexpr bool value{};
};
//https://stackoverflow.com/questions/51862465/check-if-a-type-is-stdbasic-stringt-in-compile-time-in-c
template <typename T, typename Traits, typename Alloc>
struct is_std_string<std::basic_string<T, Traits, Alloc>>
{
inline static constexpr bool value{true};
};

template<bool ln,typename T,typename U,typename... Args>
inline constexpr bool test_one()
{
	using no_cvref = std::remove_cvref_t<U>;
	if constexpr(!reserve_printable<no_cvref>)
		return false;
	else
	{
		constexpr auto size{print_reserve_size(print_reserve_type<no_cvref>)+static_cast<std::size_t>(ln)};
		return string_hack::local_capacity<T>()<size;
	}
}

template<typename T,bool ln,typename U>
inline constexpr T deal_with_one(U&& t)
{
	using value_type = typename T::value_type;
	using no_cvref = std::remove_cvref_t<U>;

	constexpr auto size{print_reserve_size(print_reserve_type<no_cvref>)+static_cast<std::size_t>(ln)};
	std::array<value_type,size> array;
	if constexpr(ln)
	{
		auto p {print_reserve_define(print_reserve_type<no_cvref>,array.data(),std::forward<U>(t))};
		*p=u8'\n';
		return T(array.data(),++p);
	}
	else
	{
		return T(array.data(),
		print_reserve_define(print_reserve_type<no_cvref>,array.data(),std::forward<U>(t)));
	}
}

template<typename T,typename U,typename... Args>
inline constexpr bool test_first_is_string_rvalue_reference()
{
	if constexpr(std::is_rvalue_reference_v<U>)
	{
		using no_cvref_t = std::remove_cvref_t<U>;
		if constexpr(is_std_string<no_cvref_t>::value&&std::same_as<no_cvref_t,T>)
			return true;
	}
	return false;
}


template<bool ln,typename T,typename U,typename... Args>
inline constexpr decltype(auto) deal_with_first_is_string_rvalue_reference(U&& u,Args&& ...args)
{
	if constexpr(!ln&&sizeof...(Args)==0)
		return std::forward<U>(u);
	else
	{
		ostring_ref t{u};
		if constexpr(ln)
			println(t,std::forward<Args>(args)...);
		else
			print(t,std::forward<Args>(args)...);
		return std::forward<U>(u);
	}
}

}

template<typename T=std::string,typename... Args>
inline constexpr T concat(Args&& ...args)
{
	if constexpr(sizeof...(Args)==0)
		return {};
	else if constexpr(sizeof...(Args)==1&&details::test_one<false,T,Args...>())
	{
		return details::deal_with_one<T,false>(std::forward<Args>(args)...);
	}
	else
	{
		if constexpr(details::test_first_is_string_rvalue_reference<T,Args&&...>())
			return details::deal_with_first_is_string_rvalue_reference<false,T>(std::forward<Args>(args)...);
		else
		{
			T v;
			ostring_ref ref{v};
			print(ref,std::forward<Args>(args)...);
			return v;
		}
	}
}

template<typename T=std::string,typename... Args>
inline constexpr T concatln(Args&& ...args)
{
	if constexpr(sizeof...(Args)==0)
		return T(1,u8'\n');
	else if constexpr(sizeof...(Args)==1&&details::test_one<true,T,Args...>())
	{
		return details::deal_with_one<T,true>(std::forward<Args>(args)...);
	}
	else
	{
		if constexpr(details::test_first_is_string_rvalue_reference<T,Args&&...>())
			return details::deal_with_first_is_string_rvalue_reference<true,T>(std::forward<Args>(args)...);
		else
		{
			T v;
			ostring_ref t{v};
			println(t,std::forward<Args>(args)...);
			return v;
		}
	}
}

template<typename T,typename... Args>
inline
#if __cpp_lib_constexpr_string >= 201907L
constexpr
#endif
void in_place_to(T& t,Args&& ...args)
{
	std::string str;
	ostring_ref ref{str};
	print(ref,std::forward<Args>(args)...);
	basic_istring_view<std::string_view> is(str);
	scan(is,t);		//Todo. no_decoration
}

template<typename... Args>
inline
#if __cpp_lib_constexpr_string >= 201907L
constexpr
#endif
void in_place_to(std::string& t,Args&& ...args)
{
	t.clear();
	ostring_ref ref{t};
	print(ref,std::forward<Args>(args)...);
}

template<typename T,typename... Args>
inline constexpr T to(Args&& ...args)
{
	if constexpr(details::is_std_string<T>::value)
	{
		return fast_io::concat<T>(std::forward<Args>(args)...);
	}
	else if constexpr(std::same_as<T,std::runtime_error>||
		std::same_as<T,std::logic_error>||std::same_as<T,std::domain_error>||
		std::same_as<T,std::invalid_argument>||std::same_as<T,std::length_error>||
		std::same_as<T,std::out_of_range>||std::same_as<T,std::range_error>||
		std::same_as<T,std::overflow_error>||std::same_as<T,std::underflow_error>)
		return T(fast_io::concat(std::forward<Args>(args)...));
	else
	{
		T t;
		in_place_to(t,std::forward<Args>(args)...);
		return t;
	}
}
}