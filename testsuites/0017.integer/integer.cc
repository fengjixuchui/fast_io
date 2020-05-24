#include"../../include/fast_io.h"


template<typename T>
using my_make_signed_t=
#ifdef __SIZEOF_INT128__
std::conditional_t<
std::same_as<std::remove_cv_t<T>,__int128_t>||std::same_as<std::remove_cv_t<T>,__uint128_t>,
std::conditional_t<std::same_as<std::remove_cv_t<T>,__int128_t>,T,
std::conditional_t<std::same_as<T,__uint128_t volatile const>,__int128_t volatile const,
std::conditional_t<std::same_as<T,__uint128_t const>,__int128_t const,
std::conditional_t<std::same_as<T,__uint128_t volatile>,__int128_t volatile,
__int128_t>>>>,
std::make_signed_t<std::conditional_t<std::same_as<std::remove_cv_t<T>,__int128_t>||std::same_as<std::remove_cv_t<T>,__uint128_t>,int,T>>>;
#else
std::make_signed_t<T>;
#endif
template<typename T>
using my_make_unsigned_t=
#ifdef __SIZEOF_INT128__
std::conditional_t<
std::same_as<std::remove_cv_t<T>,__int128_t>||std::same_as<std::remove_cv_t<T>,__uint128_t>,
std::conditional_t<std::same_as<std::remove_cv_t<T>,__uint128_t>,T,
std::conditional_t<std::same_as<T,__int128_t volatile const>,__uint128_t volatile const,
std::conditional_t<std::same_as<T,__int128_t const>,__uint128_t const,
std::conditional_t<std::same_as<T,__int128_t volatile>,__uint128_t volatile,
__uint128_t>>>>,
std::make_unsigned_t<std::conditional_t<std::same_as<std::remove_cv_t<T>,__int128_t>||std::same_as<std::remove_cv_t<T>,__uint128_t>,int,T>>>;
#else
std::make_unsigned_t<T>;
#endif

template<typename T>
concept my_integral = 
std::integral<T>
#ifdef __SIZEOF_INT128__
||std::same_as<std::remove_cv_t<T>,__uint128_t>||std::same_as<std::remove_cv_t<T>,__int128_t>
#endif
;

template<typename T>
concept my_signed_integral = 
std::signed_integral<T>
#ifdef __SIZEOF_INT128__
||std::same_as<std::remove_cv_t<T>,__int128_t>
#endif
;
template<typename T>
concept my_unsigned_integral = my_integral<T>&&!my_signed_integral<T>;

int main()
{
#ifdef __SIZEOF_INT128__
	static_assert(std::same_as<my_make_signed_t<__uint128_t>,__int128_t>);
	static_assert(std::same_as<my_make_signed_t<__int128_t>,__int128_t>);
	static_assert(std::same_as<my_make_signed_t<__uint128_t const>,__int128_t const>);
	static_assert(std::same_as<my_make_signed_t<__int128_t const>,__int128_t const>);
	static_assert(std::same_as<my_make_signed_t<__uint128_t const volatile>,__int128_t const volatile>);
	static_assert(std::same_as<my_make_signed_t<__int128_t const volatile>,__int128_t const volatile>);


	static_assert(std::same_as<my_make_unsigned_t<__uint128_t>,__uint128_t>);
	static_assert(std::same_as<my_make_unsigned_t<__int128_t>,__uint128_t>);
	static_assert(std::same_as<my_make_unsigned_t<__uint128_t const>,__uint128_t const>);
	static_assert(std::same_as<my_make_unsigned_t<__int128_t const>,__uint128_t const>);
	static_assert(std::same_as<my_make_unsigned_t<__uint128_t const volatile>,__uint128_t const volatile>);
	static_assert(std::same_as<my_make_unsigned_t<__int128_t const volatile>,__uint128_t const volatile>);

	static_assert(my_integral<__int128_t>);
	static_assert(my_signed_integral<__int128_t>);
	static_assert(!my_unsigned_integral<__int128_t>);

	static_assert(my_integral<__uint128_t>);
	static_assert(!my_signed_integral<__uint128_t>);
	static_assert(my_unsigned_integral<__uint128_t>);

	static_assert(my_integral<__int128_t volatile>);
	static_assert(my_signed_integral<__int128_t volatile>);
	static_assert(!my_unsigned_integral<__int128_t volatile>);

	static_assert(my_integral<__uint128_t volatile>);
	static_assert(!my_signed_integral<__uint128_t volatile>);
	static_assert(my_unsigned_integral<__uint128_t volatile>);

	static_assert(my_integral<__int128_t const volatile>);
	static_assert(my_signed_integral<__int128_t const volatile>);
	static_assert(!my_unsigned_integral<__int128_t const volatile>);

	static_assert(my_integral<__uint128_t const volatile>);
	static_assert(!my_signed_integral<__uint128_t const volatile>);
	static_assert(my_unsigned_integral<__uint128_t const volatile>);

#endif
	static_assert(std::same_as<my_make_signed_t<long>,long>);
	static_assert(std::same_as<my_make_signed_t<long>,long>);
	static_assert(std::same_as<my_make_signed_t<long const>,long const>);
	static_assert(std::same_as<my_make_signed_t<long unsigned const>,long const>);
	static_assert(std::same_as<my_make_signed_t<long const volatile>,long const volatile>);
	static_assert(std::same_as<my_make_signed_t<long unsigned const volatile>,long const volatile>);

	static_assert(std::same_as<my_make_unsigned_t<long>,long unsigned>);
	static_assert(std::same_as<my_make_unsigned_t<long>,long unsigned>);
	static_assert(std::same_as<my_make_unsigned_t<long const>,long unsigned const>);
	static_assert(std::same_as<my_make_unsigned_t<long unsigned const>,long unsigned const>);
	static_assert(std::same_as<my_make_unsigned_t<long const volatile>,long unsigned const volatile>);
	static_assert(std::same_as<my_make_unsigned_t<long unsigned const volatile>,long unsigned const volatile>);

	static_assert(std::same_as<my_make_signed_t<int>,int>);
	static_assert(std::same_as<my_make_signed_t<int>,int>);
	static_assert(std::same_as<my_make_signed_t<int const>,int const>);
	static_assert(std::same_as<my_make_signed_t<int unsigned const>,int const>);
	static_assert(std::same_as<my_make_signed_t<int const volatile>,int const volatile>);
	static_assert(std::same_as<my_make_signed_t<int unsigned const volatile>,int const volatile>);

	static_assert(std::same_as<my_make_unsigned_t<int>,int unsigned>);
	static_assert(std::same_as<my_make_unsigned_t<int>,int unsigned>);
	static_assert(std::same_as<my_make_unsigned_t<int const>,int unsigned const>);
	static_assert(std::same_as<my_make_unsigned_t<int unsigned const>,int unsigned const>);
	static_assert(std::same_as<my_make_unsigned_t<int const volatile>,int unsigned const volatile>);
	static_assert(std::same_as<my_make_unsigned_t<int unsigned const volatile>,int unsigned const volatile>);

	static_assert(std::unsigned_integral<int unsigned>);
	static_assert(!std::unsigned_integral<int unsigned&>);

	static_assert(my_unsigned_integral<int unsigned>);
	static_assert(!my_unsigned_integral<int unsigned&>);

	static_assert(!std::signed_integral<int unsigned>);
	static_assert(!std::signed_integral<int unsigned&>);

	static_assert(!my_signed_integral<int unsigned>);
	static_assert(!my_signed_integral<int unsigned&>);
	auto v{std::numeric_limits<__uint128_t>::max()};
}