#pragma once

namespace fast_io
{
template<std::integral ch_type,typename funct>
struct basic_c_ctype_is:public basic_ctype_is<ch_type>
{
	using char_type = ch_type;
	using function_type = funct;
	using unsigned_char_type = std::make_unsigned_t<char_type>;
	using bitset_type = basic_ctype_is<ch_type>::bitset_type;
	using storage_type = basic_ctype_is<ch_type>::storage_type;
	constexpr basic_c_ctype_is()=default;
	constexpr basic_c_ctype_is(c_locale_observer clob):basic_ctype_is<ch_type>{storage_type(new bitset_type)}
	{
		funct func;
		constexpr auto mx{std::numeric_limits<unsigned_char_type>::max()};
		if(func(0,clob))
			this->storage->set(0);
		for(unsigned_char_type i{1};i;++i)
			if(func(i,clob))
				this->storage->set(i);
	}
};

template<std::integral ch_type,typename funct>
struct basic_c_ctype_to:public basic_ctype_to<ch_type>
{
	using char_type = ch_type;
	using function_type = funct;
	using unsigned_char_type = std::make_unsigned_t<char_type>;
	using array_type = basic_ctype_to<ch_type>::array_type;
	using storage_type = basic_ctype_to<ch_type>::storage_type;
	constexpr basic_c_ctype_to()=default;
	constexpr basic_c_ctype_to(c_locale_observer clob):basic_ctype_to<ch_type>{storage_type(new array_type)}
	{
		funct func;
		constexpr auto mx{std::numeric_limits<unsigned_char_type>::max()};
		*(this->storage).front()=static_cast<char_type>(func(0,clob));
		for(unsigned_char_type i{1};i;++i)
			*(this->storage)[i]=static_cast<char_type>(func(i,clob));
	}
};

using c_ctype_isalpha=basic_c_ctype_is<char,decltype([](auto i,c_locale_observer clob)
{
#if defined(__WINNT__) || defined(_MSC_VER)
	return _isalpha_l(i,clob.native_handle());
#else
	return isalpha_l(i,clob.native_handle());
#endif
})>;
using c_ctype_islower=basic_c_ctype_is<char,decltype([](auto i,c_locale_observer clob)
{
#if defined(__WINNT__) || defined(_MSC_VER)
	return _islower_l(i,clob.native_handle());
#else
	return islower_l(i,clob.native_handle());
#endif
})>;
using c_ctype_isupper=basic_c_ctype_is<char,decltype([](auto i,c_locale_observer clob)
{
#if defined(__WINNT__) || defined(_MSC_VER)
	return _isupper_l(i,clob.native_handle());
#else
	return isupper_l(i,clob.native_handle());
#endif
})>;

using c_ctype_isdigit=basic_c_ctype_is<char,decltype([](auto i,c_locale_observer clob)
{
#if defined(__WINNT__) || defined(_MSC_VER)
	return _isdigit_l(i,clob.native_handle());
#else
	return isdigit_l(i,clob.native_handle());
#endif
})>;
using c_ctype_isxdigit=basic_c_ctype_is<char,decltype([](auto i,c_locale_observer clob)
{
#if defined(__WINNT__) || defined(_MSC_VER)
	return _isxdigit_l(i,clob.native_handle());
#else
	return isxdigit_l(i,clob.native_handle());
#endif
})>;

using c_ctype_iscntrl=basic_c_ctype_is<char,decltype([](auto i,c_locale_observer clob)
{
#if defined(__WINNT__) || defined(_MSC_VER)
	return _iscntrl_l(i,clob.native_handle());
#else
	return iscntrl_l(i,clob.native_handle());
#endif
})>;
using c_ctype_isgraph=basic_c_ctype_is<char,decltype([](auto i,c_locale_observer clob)
{
#if defined(__WINNT__) || defined(_MSC_VER)
	return _isgraph_l(i,clob.native_handle());
#else
	return isgraph_l(i,clob.native_handle());
#endif
})>;
using c_ctype_isspace=basic_c_ctype_is<char,decltype([](auto i,c_locale_observer clob)
{
#if defined(__WINNT__) || defined(_MSC_VER)
	return _isspace_l(i,clob.native_handle());
#else
	return isspace_l(i,clob.native_handle());
#endif
})>;
using c_ctype_isblank=basic_c_ctype_is<char,decltype([](auto i,c_locale_observer clob)
{
#if defined(__WINNT__) || defined(_MSC_VER)
	return _isblank_l(i,clob.native_handle());
#else
	return isblank_l(i,clob.native_handle());
#endif
})>;
using c_ctype_isprint=basic_c_ctype_is<char,decltype([](auto i,c_locale_observer clob)
{
#if defined(__WINNT__) || defined(_MSC_VER)
	return _isprint_l(i,clob.native_handle());
#else
	return isprint_l(i,clob.native_handle());
#endif
})>;
using c_ctype_ispunct=basic_c_ctype_is<char,decltype([](auto i,c_locale_observer clob)
{
#if defined(__WINNT__) || defined(_MSC_VER)
	return _ispunct_l(i,clob.native_handle());
#else
	return ispunct_l(i,clob.native_handle());
#endif
})>;

using c_ctype_tolower=basic_c_ctype_to<char,decltype([](auto i,c_locale_observer clob)
{
#if defined(__WINNT__) || defined(_MSC_VER)
	return _tolower_l(i,clob.native_handle());
#else
	return tolower_l(i,clob.native_handle());
#endif
})>;
using c_ctype_toupper=basic_c_ctype_to<char,decltype([](auto i,c_locale_observer clob)
{
#if defined(__WINNT__) || defined(_MSC_VER)
	return _toupper_l(i,clob.native_handle());
#else
	return toupper_l(i,clob.native_handle());
#endif
})>;

}