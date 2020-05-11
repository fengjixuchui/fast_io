#pragma once
#include<chrono>

namespace fast_io
{

//We use seconds since seconds is the standard unit of SI
//Use my own tweaked ryu algorithm for counting seconds
template<character_output_stream output,typename Rep,typename Period>
inline constexpr void print_define(output& out, std::chrono::duration<Rep,Period> const& duration)
{
	print(out,std::chrono::duration_cast<std::chrono::duration<double>>(duration).count());
	put(out,u8's');
}

/*

Use the emoji characters of Chinese Semantics for date time since English is a disaster for this.
No order. Everything is represented by word instead of number
2019✝️12🌙30☀️ ⛪6 19:10:03
2019年12月30日 星期六 19:10:03

Literal Meaning:
✝️ 年       Year
the period of 365 days (or 366 days in leap years) starting from the first of January, used for reckoning time in ordinary affairs.
🌙 月 Moon Month
☀️ 日 Sun  month day
⛪星期     Week  day
Order:From High to Low
*/

template<character_output_stream output>
inline constexpr void print_define(output& out,std::tm t)
//due to std::tm is often not thread safe. We make a copy
{
	print(out,1900+t.tm_year,u8"✝️");
	if(t.tm_mon<9)
		put(out,u8'0');
	print(out,1+t.tm_mon,u8"🌙");
	if(t.tm_mday<9)
		put(out,u8'0');
	print(out,1+t.tm_mday,u8"☀️ ⛪",t.tm_wday);
	put(out,u8' ');
	if(t.tm_hour<10)
		put(out,u8'0');
	print(out,t.tm_hour);
	put(out,u8':');
	if(t.tm_min<10)
		put(out,u8'0');
	print(out,t.tm_min);
	put(out,u8':');
	if(t.tm_sec<10)
		put(out,u8'0');
	print(out,t.tm_sec);
}

template<character_output_stream output>
inline constexpr void print_define(output& out,manip::chinese<std::tm const> ref)
//due to std::tm is often not thread safe. We make a copy
{
	std::tm t(ref.reference);
	print(out,1900+t.tm_year,u8"年");
	if(t.tm_mon<9)
		put(out,u8'0');
	print(out,1+t.tm_mon,u8"月");
	if(t.tm_mday<9)
		put(out,u8'0');
	print(out,1+t.tm_mday,u8"日 星期");
/*
Unfortunately Chinese encoding in Unicode is not contiguous
t.tm_wday
Number	小写	大写
0	〇	零
1	一	壹
2	二	貳
3	三	叁
4	四	肆
5	五	伍
6	六	陸
7	七	柒
8	八	捌
9	九	玖
https://en.wikibooks.org/wiki/Written_Chinese/Numbers
*/
	switch(t.tm_wday)
	{
	case 0:
		print(out,u8"日");
	break;
	case 1:
		print(out,u8"一");
	break;
	case 2:
		print(out,u8"二");
	break;
	case 3:
		print(out,u8"三");
	break;
	case 4:
		print(out,u8"四");
	break;
	case 5:
		print(out,u8"五");
	break;
	case 6:
		print(out,u8"六");
	break;
	default:
		put(out,u8'?');
	}
	put(out,u8' ');
	if(t.tm_hour<10)
		put(out,u8'0');
	print(out,t.tm_hour,u8"时");
	if(t.tm_min<10)
		put(out,u8'0');
	print(out,t.tm_min,u8"分");
	if(t.tm_sec<10)
		put(out,u8'0');
	print(out,t.tm_sec,u8"秒");
}

template<character_output_stream output,typename Clock,typename Duration>
inline constexpr void print_define(output& out, std::chrono::time_point<Clock,Duration> const& tmp)
{
	auto tmt(Clock::to_time_t(tmp));
	print_define(out,*localtime(std::addressof(tmt)));
}

template<character_output_stream output,typename Clock,typename Duration>
inline constexpr void print_define(output& out, manip::local<std::chrono::time_point<Clock,Duration> const> tmp)
{
	auto tmt(Clock::to_time_t(tmp.reference));
	print_define(out,*print_define(std::addressof(tmt)));
}

template<character_output_stream output,typename Clock,typename Duration>
inline constexpr void print_define(output& out, manip::utc<std::chrono::time_point<Clock,Duration> const> tmp)
{
	auto tmt(Clock::to_time_t(tmp.reference));
	print_define(out,*gmtime(std::addressof(tmt)));
}
/*
template<character_output_stream output,typename Clock,typename Duration>
inline constexpr void print_define(output& out, manip::unix<std::chrono::time_point<Clock,Duration> const> tmp)
{
	print_define(out,std::chrono::duration_cast<std::chrono::duration<double>>(tmp.reference.time_since_epoch()));
}
*/
template<character_output_stream output,typename Clock,typename Duration>
inline constexpr void print_define(output& out, manip::local_chinese<std::chrono::time_point<Clock,Duration> const> tmp)
{
	auto tmt(Clock::to_time_t(tmp.reference));
	print_define(out,chinese(*localtime(std::addressof(tmt))));
}

template<character_output_stream output,typename Clock,typename Duration>
inline constexpr void print_define(output& out, manip::utc_chinese<std::chrono::time_point<Clock,Duration> const> tmp)
{
	auto tmt(Clock::to_time_t(tmp.reference));
	print_define(out,chinese(*gmtime(std::addressof(tmt))));
}

/*
//current libraries have no these facilities
template<output_stream output>
inline constexpr void print_define(output& out, std::chrono::time_zone const& tmp)
{
	print(out,tmp.name());
}
*/

}