#pragma once

namespace fast_io::openssl
{

class openssl_error:public fast_io_error
{
public:
	virtual	void report(error_reporter& err) const override;
};

}