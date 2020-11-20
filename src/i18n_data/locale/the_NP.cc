#include"../localedef.h"

namespace fast_io_i18n
{
namespace
{

inline constexpr std::size_t numeric_grouping_storage[]{3};

inline constexpr lc_all lc_all_global{.identification={.title=tsc("Tharu language locale for Nepal"),.source=tsc("Chitwanix OS Development\t\t;\t\tfast_io"),.address=tsc("Sangam Market, narayanghat, Nepal\t\t;\t\thttps://github.com/expnkx/fast_io"),.contact=tsc("fast_io"),.email=tsc("info@chitwanix.com;euloanty@live.com"),.tel=tsc(""),.fax=tsc(""),.language=tsc("Chitwania Tharu"),.territory=tsc("Nepal"),.revision=tsc("1.1"),.date=tsc("2013-11-15")},.monetary={.int_curr_symbol=tsc("NPR "),.currency_symbol=tsc("रू"),.mon_decimal_point=tsc("."),.mon_thousands_sep=tsc(","),.mon_grouping={numeric_grouping_storage,1},.positive_sign=tsc(""),.negative_sign=tsc("-"),.int_frac_digits=2,.frac_digits=2,.p_cs_precedes=1,.p_sep_by_space=1,.n_cs_precedes=1,.n_sep_by_space=1,.p_sign_posn=1,.n_sign_posn=1},.numeric={.decimal_point=tsc("."),.thousands_sep=tsc(","),.grouping={numeric_grouping_storage,1}},.time={.abday={tsc("आइत"),tsc("सोम"),tsc("मंगल"),tsc("बुध"),tsc("बिहि"),tsc("शुक्र"),tsc("शनि")},.day={tsc("आइतबार"),tsc("सोमबार"),tsc("मंगलबार"),tsc("बुधबार"),tsc("बिहिबार"),tsc("शुक्रबार"),tsc("शनिबार")},.abmon={tsc("जनवरी"),tsc("फ़रवरी"),tsc("मार्च"),tsc("अप्रेल"),tsc("मई"),tsc("जून"),tsc("जुलाई"),tsc("अगस्त"),tsc("सितम्बर"),tsc("अक्टूबर"),tsc("नवम्बर"),tsc("दिसम्बर")},.mon={tsc("जनवरी"),tsc("फ़रवरी"),tsc("मार्च"),tsc("अप्रेल"),tsc("मई"),tsc("जून"),tsc("जुलाई"),tsc("अगस्त"),tsc("सितम्बर"),tsc("अक्टूबर"),tsc("नवम्बर"),tsc("दिसम्बर")},.d_t_fmt=tsc("%A %d %b %Y %I:%M:%S %p"),.d_fmt=tsc("%A %d %b %Y"),.t_fmt=tsc("%I:%M:%S %p %Z"),.t_fmt_ampm=tsc("%I:%M:%S %p %Z"),.date_fmt=tsc("%A %d %b %Y %I:%M:%S %p %Z"),.am_pm={tsc("पूर्वाह्न"),tsc("अपराह्न")},.week={7,19971130,1}},.messages={.yesexpr=tsc("^[+1yY]"),.noexpr=tsc("^[-0nN]")},.paper={.width=210,.height=297},.telephone={.tel_int_fmt=tsc("+%c %a%t%l"),.int_select=tsc("00"),.int_prefix=tsc("977")},.name={.name_fmt=tsc("%p%t%f%t%g"),.name_gen=tsc(""),.name_miss=tsc("Miss."),.name_mr=tsc("Mr."),.name_mrs=tsc("Mrs."),.name_ms=tsc("Ms.")},.address={.postal_fmt=tsc("%z%c%T%s%b%e%r"),.country_name=tsc("नेपाल"),.country_ab2=tsc("NP"),.country_ab3=tsc("NPL"),.country_num=524,.country_car=tsc("NEP"),.lang_name=tsc("थारु"),.lang_term=tsc("the"),.lang_lib=tsc("the")},.measurement={.measurement=1}};

inline constexpr wlc_all wlc_all_global{.identification={.title=tsc(L"Tharu language locale for Nepal"),.source=tsc(L"Chitwanix OS Development\t\t;\t\tfast_io"),.address=tsc(L"Sangam Market, narayanghat, Nepal\t\t;\t\thttps://github.com/expnkx/fast_io"),.contact=tsc(L"fast_io"),.email=tsc(L"info@chitwanix.com;euloanty@live.com"),.tel=tsc(L""),.fax=tsc(L""),.language=tsc(L"Chitwania Tharu"),.territory=tsc(L"Nepal"),.revision=tsc(L"1.1"),.date=tsc(L"2013-11-15")},.monetary={.int_curr_symbol=tsc(L"NPR "),.currency_symbol=tsc(L"रू"),.mon_decimal_point=tsc(L"."),.mon_thousands_sep=tsc(L","),.mon_grouping={numeric_grouping_storage,1},.positive_sign=tsc(L""),.negative_sign=tsc(L"-"),.int_frac_digits=2,.frac_digits=2,.p_cs_precedes=1,.p_sep_by_space=1,.n_cs_precedes=1,.n_sep_by_space=1,.p_sign_posn=1,.n_sign_posn=1},.numeric={.decimal_point=tsc(L"."),.thousands_sep=tsc(L","),.grouping={numeric_grouping_storage,1}},.time={.abday={tsc(L"आइत"),tsc(L"सोम"),tsc(L"मंगल"),tsc(L"बुध"),tsc(L"बिहि"),tsc(L"शुक्र"),tsc(L"शनि")},.day={tsc(L"आइतबार"),tsc(L"सोमबार"),tsc(L"मंगलबार"),tsc(L"बुधबार"),tsc(L"बिहिबार"),tsc(L"शुक्रबार"),tsc(L"शनिबार")},.abmon={tsc(L"जनवरी"),tsc(L"फ़रवरी"),tsc(L"मार्च"),tsc(L"अप्रेल"),tsc(L"मई"),tsc(L"जून"),tsc(L"जुलाई"),tsc(L"अगस्त"),tsc(L"सितम्बर"),tsc(L"अक्टूबर"),tsc(L"नवम्बर"),tsc(L"दिसम्बर")},.mon={tsc(L"जनवरी"),tsc(L"फ़रवरी"),tsc(L"मार्च"),tsc(L"अप्रेल"),tsc(L"मई"),tsc(L"जून"),tsc(L"जुलाई"),tsc(L"अगस्त"),tsc(L"सितम्बर"),tsc(L"अक्टूबर"),tsc(L"नवम्बर"),tsc(L"दिसम्बर")},.d_t_fmt=tsc(L"%A %d %b %Y %I:%M:%S %p"),.d_fmt=tsc(L"%A %d %b %Y"),.t_fmt=tsc(L"%I:%M:%S %p %Z"),.t_fmt_ampm=tsc(L"%I:%M:%S %p %Z"),.date_fmt=tsc(L"%A %d %b %Y %I:%M:%S %p %Z"),.am_pm={tsc(L"पूर्वाह्न"),tsc(L"अपराह्न")},.week={7,19971130,1}},.messages={.yesexpr=tsc(L"^[+1yY]"),.noexpr=tsc(L"^[-0nN]")},.paper={.width=210,.height=297},.telephone={.tel_int_fmt=tsc(L"+%c %a%t%l"),.int_select=tsc(L"00"),.int_prefix=tsc(L"977")},.name={.name_fmt=tsc(L"%p%t%f%t%g"),.name_gen=tsc(L""),.name_miss=tsc(L"Miss."),.name_mr=tsc(L"Mr."),.name_mrs=tsc(L"Mrs."),.name_ms=tsc(L"Ms.")},.address={.postal_fmt=tsc(L"%z%c%T%s%b%e%r"),.country_name=tsc(L"नेपाल"),.country_ab2=tsc(L"NP"),.country_ab3=tsc(L"NPL"),.country_num=524,.country_car=tsc(L"NEP"),.lang_name=tsc(L"थारु"),.lang_term=tsc(L"the"),.lang_lib=tsc(L"the")},.measurement={.measurement=1}};

inline constexpr u8lc_all u8lc_all_global{.identification={.title=tsc(u8"Tharu language locale for Nepal"),.source=tsc(u8"Chitwanix OS Development\t\t;\t\tfast_io"),.address=tsc(u8"Sangam Market, narayanghat, Nepal\t\t;\t\thttps://github.com/expnkx/fast_io"),.contact=tsc(u8"fast_io"),.email=tsc(u8"info@chitwanix.com;euloanty@live.com"),.tel=tsc(u8""),.fax=tsc(u8""),.language=tsc(u8"Chitwania Tharu"),.territory=tsc(u8"Nepal"),.revision=tsc(u8"1.1"),.date=tsc(u8"2013-11-15")},.monetary={.int_curr_symbol=tsc(u8"NPR "),.currency_symbol=tsc(u8"रू"),.mon_decimal_point=tsc(u8"."),.mon_thousands_sep=tsc(u8","),.mon_grouping={numeric_grouping_storage,1},.positive_sign=tsc(u8""),.negative_sign=tsc(u8"-"),.int_frac_digits=2,.frac_digits=2,.p_cs_precedes=1,.p_sep_by_space=1,.n_cs_precedes=1,.n_sep_by_space=1,.p_sign_posn=1,.n_sign_posn=1},.numeric={.decimal_point=tsc(u8"."),.thousands_sep=tsc(u8","),.grouping={numeric_grouping_storage,1}},.time={.abday={tsc(u8"आइत"),tsc(u8"सोम"),tsc(u8"मंगल"),tsc(u8"बुध"),tsc(u8"बिहि"),tsc(u8"शुक्र"),tsc(u8"शनि")},.day={tsc(u8"आइतबार"),tsc(u8"सोमबार"),tsc(u8"मंगलबार"),tsc(u8"बुधबार"),tsc(u8"बिहिबार"),tsc(u8"शुक्रबार"),tsc(u8"शनिबार")},.abmon={tsc(u8"जनवरी"),tsc(u8"फ़रवरी"),tsc(u8"मार्च"),tsc(u8"अप्रेल"),tsc(u8"मई"),tsc(u8"जून"),tsc(u8"जुलाई"),tsc(u8"अगस्त"),tsc(u8"सितम्बर"),tsc(u8"अक्टूबर"),tsc(u8"नवम्बर"),tsc(u8"दिसम्बर")},.mon={tsc(u8"जनवरी"),tsc(u8"फ़रवरी"),tsc(u8"मार्च"),tsc(u8"अप्रेल"),tsc(u8"मई"),tsc(u8"जून"),tsc(u8"जुलाई"),tsc(u8"अगस्त"),tsc(u8"सितम्बर"),tsc(u8"अक्टूबर"),tsc(u8"नवम्बर"),tsc(u8"दिसम्बर")},.d_t_fmt=tsc(u8"%A %d %b %Y %I:%M:%S %p"),.d_fmt=tsc(u8"%A %d %b %Y"),.t_fmt=tsc(u8"%I:%M:%S %p %Z"),.t_fmt_ampm=tsc(u8"%I:%M:%S %p %Z"),.date_fmt=tsc(u8"%A %d %b %Y %I:%M:%S %p %Z"),.am_pm={tsc(u8"पूर्वाह्न"),tsc(u8"अपराह्न")},.week={7,19971130,1}},.messages={.yesexpr=tsc(u8"^[+1yY]"),.noexpr=tsc(u8"^[-0nN]")},.paper={.width=210,.height=297},.telephone={.tel_int_fmt=tsc(u8"+%c %a%t%l"),.int_select=tsc(u8"00"),.int_prefix=tsc(u8"977")},.name={.name_fmt=tsc(u8"%p%t%f%t%g"),.name_gen=tsc(u8""),.name_miss=tsc(u8"Miss."),.name_mr=tsc(u8"Mr."),.name_mrs=tsc(u8"Mrs."),.name_ms=tsc(u8"Ms.")},.address={.postal_fmt=tsc(u8"%z%c%T%s%b%e%r"),.country_name=tsc(u8"नेपाल"),.country_ab2=tsc(u8"NP"),.country_ab3=tsc(u8"NPL"),.country_num=524,.country_car=tsc(u8"NEP"),.lang_name=tsc(u8"थारु"),.lang_term=tsc(u8"the"),.lang_lib=tsc(u8"the")},.measurement={.measurement=1}};

inline constexpr u16lc_all u16lc_all_global{.identification={.title=tsc(u"Tharu language locale for Nepal"),.source=tsc(u"Chitwanix OS Development\t\t;\t\tfast_io"),.address=tsc(u"Sangam Market, narayanghat, Nepal\t\t;\t\thttps://github.com/expnkx/fast_io"),.contact=tsc(u"fast_io"),.email=tsc(u"info@chitwanix.com;euloanty@live.com"),.tel=tsc(u""),.fax=tsc(u""),.language=tsc(u"Chitwania Tharu"),.territory=tsc(u"Nepal"),.revision=tsc(u"1.1"),.date=tsc(u"2013-11-15")},.monetary={.int_curr_symbol=tsc(u"NPR "),.currency_symbol=tsc(u"रू"),.mon_decimal_point=tsc(u"."),.mon_thousands_sep=tsc(u","),.mon_grouping={numeric_grouping_storage,1},.positive_sign=tsc(u""),.negative_sign=tsc(u"-"),.int_frac_digits=2,.frac_digits=2,.p_cs_precedes=1,.p_sep_by_space=1,.n_cs_precedes=1,.n_sep_by_space=1,.p_sign_posn=1,.n_sign_posn=1},.numeric={.decimal_point=tsc(u"."),.thousands_sep=tsc(u","),.grouping={numeric_grouping_storage,1}},.time={.abday={tsc(u"आइत"),tsc(u"सोम"),tsc(u"मंगल"),tsc(u"बुध"),tsc(u"बिहि"),tsc(u"शुक्र"),tsc(u"शनि")},.day={tsc(u"आइतबार"),tsc(u"सोमबार"),tsc(u"मंगलबार"),tsc(u"बुधबार"),tsc(u"बिहिबार"),tsc(u"शुक्रबार"),tsc(u"शनिबार")},.abmon={tsc(u"जनवरी"),tsc(u"फ़रवरी"),tsc(u"मार्च"),tsc(u"अप्रेल"),tsc(u"मई"),tsc(u"जून"),tsc(u"जुलाई"),tsc(u"अगस्त"),tsc(u"सितम्बर"),tsc(u"अक्टूबर"),tsc(u"नवम्बर"),tsc(u"दिसम्बर")},.mon={tsc(u"जनवरी"),tsc(u"फ़रवरी"),tsc(u"मार्च"),tsc(u"अप्रेल"),tsc(u"मई"),tsc(u"जून"),tsc(u"जुलाई"),tsc(u"अगस्त"),tsc(u"सितम्बर"),tsc(u"अक्टूबर"),tsc(u"नवम्बर"),tsc(u"दिसम्बर")},.d_t_fmt=tsc(u"%A %d %b %Y %I:%M:%S %p"),.d_fmt=tsc(u"%A %d %b %Y"),.t_fmt=tsc(u"%I:%M:%S %p %Z"),.t_fmt_ampm=tsc(u"%I:%M:%S %p %Z"),.date_fmt=tsc(u"%A %d %b %Y %I:%M:%S %p %Z"),.am_pm={tsc(u"पूर्वाह्न"),tsc(u"अपराह्न")},.week={7,19971130,1}},.messages={.yesexpr=tsc(u"^[+1yY]"),.noexpr=tsc(u"^[-0nN]")},.paper={.width=210,.height=297},.telephone={.tel_int_fmt=tsc(u"+%c %a%t%l"),.int_select=tsc(u"00"),.int_prefix=tsc(u"977")},.name={.name_fmt=tsc(u"%p%t%f%t%g"),.name_gen=tsc(u""),.name_miss=tsc(u"Miss."),.name_mr=tsc(u"Mr."),.name_mrs=tsc(u"Mrs."),.name_ms=tsc(u"Ms.")},.address={.postal_fmt=tsc(u"%z%c%T%s%b%e%r"),.country_name=tsc(u"नेपाल"),.country_ab2=tsc(u"NP"),.country_ab3=tsc(u"NPL"),.country_num=524,.country_car=tsc(u"NEP"),.lang_name=tsc(u"थारु"),.lang_term=tsc(u"the"),.lang_lib=tsc(u"the")},.measurement={.measurement=1}};

inline constexpr u32lc_all u32lc_all_global{.identification={.title=tsc(U"Tharu language locale for Nepal"),.source=tsc(U"Chitwanix OS Development\t\t;\t\tfast_io"),.address=tsc(U"Sangam Market, narayanghat, Nepal\t\t;\t\thttps://github.com/expnkx/fast_io"),.contact=tsc(U"fast_io"),.email=tsc(U"info@chitwanix.com;euloanty@live.com"),.tel=tsc(U""),.fax=tsc(U""),.language=tsc(U"Chitwania Tharu"),.territory=tsc(U"Nepal"),.revision=tsc(U"1.1"),.date=tsc(U"2013-11-15")},.monetary={.int_curr_symbol=tsc(U"NPR "),.currency_symbol=tsc(U"रू"),.mon_decimal_point=tsc(U"."),.mon_thousands_sep=tsc(U","),.mon_grouping={numeric_grouping_storage,1},.positive_sign=tsc(U""),.negative_sign=tsc(U"-"),.int_frac_digits=2,.frac_digits=2,.p_cs_precedes=1,.p_sep_by_space=1,.n_cs_precedes=1,.n_sep_by_space=1,.p_sign_posn=1,.n_sign_posn=1},.numeric={.decimal_point=tsc(U"."),.thousands_sep=tsc(U","),.grouping={numeric_grouping_storage,1}},.time={.abday={tsc(U"आइत"),tsc(U"सोम"),tsc(U"मंगल"),tsc(U"बुध"),tsc(U"बिहि"),tsc(U"शुक्र"),tsc(U"शनि")},.day={tsc(U"आइतबार"),tsc(U"सोमबार"),tsc(U"मंगलबार"),tsc(U"बुधबार"),tsc(U"बिहिबार"),tsc(U"शुक्रबार"),tsc(U"शनिबार")},.abmon={tsc(U"जनवरी"),tsc(U"फ़रवरी"),tsc(U"मार्च"),tsc(U"अप्रेल"),tsc(U"मई"),tsc(U"जून"),tsc(U"जुलाई"),tsc(U"अगस्त"),tsc(U"सितम्बर"),tsc(U"अक्टूबर"),tsc(U"नवम्बर"),tsc(U"दिसम्बर")},.mon={tsc(U"जनवरी"),tsc(U"फ़रवरी"),tsc(U"मार्च"),tsc(U"अप्रेल"),tsc(U"मई"),tsc(U"जून"),tsc(U"जुलाई"),tsc(U"अगस्त"),tsc(U"सितम्बर"),tsc(U"अक्टूबर"),tsc(U"नवम्बर"),tsc(U"दिसम्बर")},.d_t_fmt=tsc(U"%A %d %b %Y %I:%M:%S %p"),.d_fmt=tsc(U"%A %d %b %Y"),.t_fmt=tsc(U"%I:%M:%S %p %Z"),.t_fmt_ampm=tsc(U"%I:%M:%S %p %Z"),.date_fmt=tsc(U"%A %d %b %Y %I:%M:%S %p %Z"),.am_pm={tsc(U"पूर्वाह्न"),tsc(U"अपराह्न")},.week={7,19971130,1}},.messages={.yesexpr=tsc(U"^[+1yY]"),.noexpr=tsc(U"^[-0nN]")},.paper={.width=210,.height=297},.telephone={.tel_int_fmt=tsc(U"+%c %a%t%l"),.int_select=tsc(U"00"),.int_prefix=tsc(U"977")},.name={.name_fmt=tsc(U"%p%t%f%t%g"),.name_gen=tsc(U""),.name_miss=tsc(U"Miss."),.name_mr=tsc(U"Mr."),.name_mrs=tsc(U"Mrs."),.name_ms=tsc(U"Ms.")},.address={.postal_fmt=tsc(U"%z%c%T%s%b%e%r"),.country_name=tsc(U"नेपाल"),.country_ab2=tsc(U"NP"),.country_ab3=tsc(U"NPL"),.country_num=524,.country_car=tsc(U"NEP"),.lang_name=tsc(U"थारु"),.lang_term=tsc(U"the"),.lang_lib=tsc(U"the")},.measurement={.measurement=1}};


}
}

#include"../main.h"