#pragma once

namespace fast_io::openssl
{

class openssl_error:public fast_io_error
{
public:
	virtual
#if __cpp_constexpr >= 201907L
	constexpr
#endif
	void report(error_reporter& err) const override;
};

}