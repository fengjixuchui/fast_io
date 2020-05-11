#pragma once

namespace fast_io::openssl
{

class crypto
{
public:
	crypto(std::uint64_t opts,settings_observer sob)
	{
		if(!OPENSSL_init_crypto(opt,sob.native_handle()))
			throw std::runtime_error("OPENSSL_init_crypto() failed");
	}
	crypto(crypto const&)=delete;
	crypto const& operator=(crypto const&)=delete;
	~crypto()
	{
		OPENSSL_cleanup();
	}
};

};