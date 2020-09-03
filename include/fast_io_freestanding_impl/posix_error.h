#pragma once

namespace fast_io
{

class posix_error:public fast_io_error
{
public:
	int ec{};
	explicit posix_error(int errn=errno):ec(errn){}
	constexpr auto code() const noexcept
	{
		return ec;
	}
#if __cpp_constexpr >= 201907L
	//constexpr
#endif
	void report(error_reporter& report) const override
	{
#ifdef _WIN32
		// TODO: 
		print(report, ec);
#else
		print(report,chvw(strerror(ec)));
#endif
	}
};

inline void throw_posix_error()
{
#ifdef __cpp_exceptions
	throw posix_error();
#else
	fast_terminate();
#endif
}
inline void throw_posix_error(int err)
{
#ifdef __cpp_exceptions
	throw posix_error(err);
#else
	fast_terminate();
#endif
}
}
