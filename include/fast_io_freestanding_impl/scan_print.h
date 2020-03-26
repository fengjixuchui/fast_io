#pragma once

namespace fast_io
{
inline namespace print_scan_details
{
template<typename output,typename T>
concept weak_printable=output_stream<output>&&general_printable<basic_ostring<std::basic_string<typename output::char_type>>,T>;

template<typename output,typename T>
concept weak_sendable=output_stream<output>&&requires(basic_ostring<std::basic_string<typename output::char_type>>& ostr,T const& t)
{
	send_define(ostr,t);
};

template<output_stream output,typename ...Args>
inline constexpr void buffer_print(output &out,Args&& ...args)
{
	if constexpr((weak_printable<output,Args>||...))
	{
		basic_ostring<std::basic_string<typename output::char_type>> ostr;
		(print_control(ostr,std::forward<Args>(args)),...);
		write(out,ostr.str().cbegin(),ostr.str().cend());
	}
	else if constexpr(output_stream<output>)
		static_assert(!output_stream<output>,u8"unsupported type. consider define your own one with print_define");
}

template<output_stream output,typename ...Args>
inline constexpr void buffer_println(output &out,Args&& ...args)
{
	if constexpr((weak_printable<output,Args>||...))
	{
		basic_ostring<std::basic_string<typename output::char_type>> ostr;
		(print_control(ostr,std::forward<Args>(args)),...);
		put(ostr,0xA);
		write(out,ostr.str().cbegin(),ostr.str().cend());
	}
	else if constexpr(output_stream<output>)
		static_assert(!output_stream<output>,u8"unsupported type. consider define your own one with print_define");
}

template<output_stream output,typename ...Args>
inline constexpr void buffer_fprint(output &out,std::basic_string_view<typename output::char_type> format,Args&& ...args)
{
	if constexpr((weak_printable<output,Args>||...))
	{
		basic_ostring<std::basic_string<typename output::char_type>> ostr;
		print_scan_details::fprint_impl(ostr,format,std::forward<Args>(args)...);
		write(out,ostr.str().cbegin(),ostr.str().cend());
	}
	else if constexpr(output_stream<output>)
		static_assert(!output_stream<output>,u8"unsupported type. consider define your own one with print_define");
}

template<output_stream output,typename ...Args>
requires (std::same_as<typename output::char_type,char>)
inline constexpr void buffer_fprint(output &out,std::basic_string_view<char8_t> format,Args&& ...args)
{
	if constexpr((weak_printable<output,Args>||...))
	{
		basic_ostring<std::basic_string<typename output::char_type>> ostr;
		print_scan_details::fprint_impl(ostr,format,std::forward<Args>(args)...);
		write(out,ostr.str().cbegin(),ostr.str().cend());
	}
	else if constexpr(output_stream<output>)
		static_assert(!output_stream<output>,u8"unsupported type. consider define your own one with print_define");
}

template<output_stream output,typename ...Args>
inline constexpr void buffer_send(output &out,Args&& ...args)
{
	if constexpr((weak_sendable<output,Args>||...))
	{
		basic_ostring<std::basic_string<typename output::char_type>> ostr;
		(send_define(ostr,std::forward<Args>(args)),...);
		write(out,ostr.str().cbegin(),ostr.str().cend());
	}
	else if constexpr(output_stream<output>)
		static_assert(!output_stream<output>,u8"unsupported type. consider define your own one with send_define");
}
}
}