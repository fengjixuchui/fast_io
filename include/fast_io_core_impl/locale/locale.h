#pragma once
//https://en.cppreference.com/w/cpp/locale/lconv
namespace fast_io::locale
{

template<std::integral ch_type>
struct numeric
{
	using char_type = ch_type;
	using string_view_type = std::basic_string_view<char_type>;
	char_type decimal_point{u8'.'};
	char_type separator{u8','};
	string_view_type grouping;
};

template<std::integral ch_type>
struct signs
{
	using char_type = ch_type;
	using string_view_type = std::basic_string_view<char_type>;
	string_view_type positive_sign;
	string_view_type negative_sign;
};

enum class seperate_by_space:std::uint8_t
{
no_space=0,
sign_stick_to_cs_value_sep_by_space=1,
sign_stick_to_value_cs_sep_by_space=2
};

enum class sign_position_monetary:std::uint8_t
{
parentheses_around_value_cs_represents_sign=0,
sign_before_both=1,
sign_after_both=2,
sign_before_cs=3,
sign_after_cs=4
};

template<std::integral ch_type>
struct monetary
{
	using char_type = ch_type;
	using string_view_type = std::basic_string_view<char_type>;
	string_view_type currency_symbol;
	std::size_t fraction_digits{};
	bool cs_before_non_negative_value{};
	bool cs_before_negative_value{};
	seperate_by_space sep_by_space{};
	sign_position_monetary sign_posn{};
};

template<std::integral ch_type>
struct basic_locale
{
	numeric none_monetary_numeric,monetary_numeric;
	signs monetary_signs;
	monetary<ch_type> locale_monetary,international_monetary;
};

}