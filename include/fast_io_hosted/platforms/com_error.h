#pragma once

#include <comdef.h>

namespace fast_io
{
namespace details
{

inline void report_com_error(error_reporter& report, auto hresult) requires(std::same_as<TCHAR,char>)
{
	_com_error ce(hresult);
	print(report,std::string_view{ce.ErrorMessage()});
}

inline void report_com_error(error_reporter& report, auto hresult) requires(std::same_as<TCHAR,wchar_t>&&sizeof(wchar_t)==2)
{
	_com_error ce(hresult);
	print(report,fast_io::code_cvt(std::wstring_view{ce.ErrorMessage()}));
}
}

class com_error : public fast_io_error
{
public:
	HRESULT hresult{};
	explicit com_error(HRESULT hr):hresult(hr){}
	constexpr auto code() const noexcept
	{
		return hresult;
	}
	void report(error_reporter& report) const override
	{
		details::report_com_error(report,hresult);
	}
};

}