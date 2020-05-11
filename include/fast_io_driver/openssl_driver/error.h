#pragma once

namespace fast_io::openssl
{

class openssl_error:public std::runtime_error
{
public:
	template<typename... Args>
	requires std::constructible_from<std::runtime_error,Args...>
	explicit openssl_error(Args&& ...args):std::runtime_error(std::forward<Args>(args)...){}
};

}