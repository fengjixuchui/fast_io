#pragma once

namespace fast_io
{

template<std::integral ch_type,std::ranges::contiguous_range stg_type=std::vector<ch_type>>
struct basic_c_lconv_storage:public basic_lconv_storage<ch_type,stg_type>
{
	using char_type = ch_type;
	using storage_type = stg_type;
	using iterator = storage_type::iterator;
	using string_view_type = std::basic_string_view<char_type>;
	constexpr basic_c_lconv_storage()=default;
	basic_c_lconv_storage(c_locale_observer clob)
	{
#if defined(__WINNT__) || defined(_MSC_VER)
		auto& lcv{*(clob.native_handle()->locinfo->lconv)};
#else
		c_locale_thread_local_guard guard(clob);
		auto& lcv{*localeconv()};
#endif
		this->decimal_point=*lcv.decimal_point;
		this->thousands_sep=*lcv.thousands_sep;

		this->mon_decimal_point=*lcv.mon_decimal_point;
		this->mon_thousands_sep=*lcv.mon_thousands_sep;

		this->frac_digits=lcv.frac_digits;

		this->p_cs_precedes=lcv.p_cs_precedes;
		this->n_cs_precedes=lcv.n_cs_precedes;
		this->p_sep_by_space=lcv.p_sep_by_space;
		this->n_sep_by_space=lcv.n_sep_by_space;
		this->p_sign_posn=lcv.p_sign_posn;
		this->n_sign_posn=lcv.n_sign_posn;

		this->int_frac_digits=lcv.int_frac_digits;
#if !defined(__WINNT__) && !defined(_MSC_VER)
		this->int_p_cs_precedes=lcv.int_p_cs_precedes;
		this->int_n_cs_precedes=lcv.int_n_cs_precedes;
		this->int_p_sep_by_space=lcv.int_p_sep_by_space;
		this->int_n_sep_by_space=lcv.int_n_sep_by_space;
		this->int_p_sign_posn=lcv.int_p_sign_posn;
		this->int_n_sign_posn=lcv.int_n_sign_posn;
#endif
		auto& stog{this->storage};
		auto insert_lmd([&](char const* itemptr)
		{
			std::size_t const size{std::strlen(itemptr)};
			stog.insert(stog.end(),itemptr,itemptr+size);
			return stog.size();
		});
		auto mon_grouping_start_pos{insert_lmd(lcv.grouping)};
		auto positive_sign_start_pos{insert_lmd(lcv.mon_grouping)};
		auto negative_sign_start_pos{insert_lmd(lcv.positive_sign)};
		auto currency_symbol_start_pos{insert_lmd(lcv.negative_sign)};
		auto int_curr_symbol_start_pos{insert_lmd(lcv.currency_symbol)};
		insert_lmd(lcv.int_curr_symbol);

		this->mon_grouping_start=stog.begin()+mon_grouping_start_pos;
		this->positive_sign_start=stog.begin()+positive_sign_start_pos;
		this->negative_sign_start=stog.begin()+negative_sign_start_pos;
		this->currency_symbol_start=stog.begin()+currency_symbol_start_pos;
		this->int_curr_symbol_start=stog.begin()+int_curr_symbol_start_pos;
	}
};

using c_lconv_storage = basic_c_lconv_storage<char>;
using wc_lconv_storage = basic_c_lconv_storage<wchar_t>;
using u8c_lconv_storage = basic_c_lconv_storage<char8_t>;

}