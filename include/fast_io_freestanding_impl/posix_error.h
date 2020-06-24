#pragma once

namespace fast_io
{

class posix_error:public fast_io_error
{
	int ecd;
public:
	explicit posix_error(int errn=errno):ecd(errn){}
	constexpr auto code() const noexcept
	{
		return ecd;
	}
#if __cpp_constexpr >= 201907L
	//constexpr
#endif
	void report(error_reporter& report) const override
	{
		print(report,std::string_view(strerror(ecd)));
	}
};

}