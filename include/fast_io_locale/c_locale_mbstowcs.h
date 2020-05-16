#pragma once

namespace fast_io
{
struct c_locale_mbstowcs
{
	using manip_tag = manip_tag_t;
	c_locale_observer cloc_ob;
	char* begin_ptr,char* end_ptr;
	constexpr c_locale_mbstowcs(c_locale_observer c,Iter begin,Iter end):cioc_ob(c),begin_ptr(std::to_address(begin_ptr)),end_ptr(std::to_address(end_ptr)){}
};
#if defined(__WINNT__) || defined(_MSC_VER)
extern "C" errno_t _mbstowcs_s_l(std::size_t*,wchar_t*,std::size_t,char const*,std::size_t,_locale_t);
#endif
template<output_stream output>
requires std::same_as<typename output::char_type,wchar_t>
void print_define(output& out,c_locale_mbstowcs ref)
{
#if defined(__WINNT__) || defined(_MSC_VER)
	std::size_t required_sz{};
	auto errcd{_mbstowcs_s_l(std::addressof(required_sz),nullptr,0,ref.begin_ptr,static_cast<std::size_t>(ref.end_ptr-ref.begin_ptr),ref.cloc_ob.native_handle())};
	if(errcd)
#ifdef __cpp_exceptions
		throw std::system_error(static_cast<int>(errcd),std::generic_category());
#else
		fast_terminate();
#endif
#else
	std::size_t required_sz{mbstowcs_l(nullptr,ref.begin_ptr,static_cast<std::size_t>(ref.end_ptr-ref.begin_ptr))};
	if(required_sz==std::numeric_limits<std::size_t>::max())
		throw std::system_error(errno,std::generic_category());
#endif
	int error{};
	reserve_write(out,required_sz,[&](wchar_t* iter)
	{
#if defined(__WINNT__) || defined(_MSC_VER)
		std::size_t sz{};
		auto err{_mbstowcs_s_l(std::addressof(sz),iter,required_sz,ref.begin_ptr,static_cast<std::size_t>(ref.end_ptr-ref.begin_ptr),ref.cloc_ob.native_handle())};
		if(err)
		{
			error=static_cast<int>(err);
			return iter;
		}
#else
		std::size_t sz{mbstowcs_l(nullptr,ref.begin_ptr,static_cast<std::size_t>(ref.end_ptr-ref.begin_ptr))};
		if(sz==std::numeric_limits<std::size_t>::max())
		{
			error=errno;
			return iter;
		}
#endif
		return iter+sz;
	});
	if(error)
#ifdef __cpp_exceptions
		throw std::system_error(error,std::generic_category());
#else
		fast_terminate();
#endif
}

}