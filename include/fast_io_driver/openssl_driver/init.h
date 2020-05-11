#pragma once

namespace fast_io::openssl
{

class global_initializer
{
public:
	explicit global_initializer() noexcept
	{
		SSL_library_init();
	}
};


}