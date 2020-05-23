#pragma once
#include<streambuf>

namespace fast_io
{

template<typename T>
class streambuf_handle
{
public:
	stream_view_details::streambuf_pub<T> handle;
	using streambuf_type = T;
	using char_type = typename streambuf_type::char_type;
	template<typename ...Args>
	requires std::constructible_from<T,Args...>
	streambuf_handle(Args&& ...args):handle(std::forward<Args>(args)...)
	{
	}
	auto& native_handle()
	{
		return handle;
	}

};

template<typename T,std::contiguous_iterator Iter>
inline Iter read(streambuf_handle<T>& hd,Iter begin,Iter end)
{
	using char_type = typename T::char_type;
	return begin+(hd.handle.sgetn(static_cast<char_type*>(static_cast<void*>(std::to_address(begin))),(end-begin)*sizeof(*begin)/sizeof(char_type))*sizeof(char_type)/sizeof(*begin));
}

template<typename T,std::contiguous_iterator Iter>
inline void write(streambuf_handle<T>& hd,Iter begin,Iter end) 
{
	using char_type = typename T::char_type;
	if(!hd.handle.sputn(static_cast<char_type const*>(static_cast<void const*>(std::to_address(begin))),(end-begin)*sizeof(*begin)/sizeof(char_type)))
#ifdef __cpp_exceptions
		throw posix_error(EIO);
#else
		fast_terminate();
#endif
}

template<typename T>
inline void flush(streambuf_handle<T>& hd)
{
	hd.handle.flush();
}

template<typename T>
inline auto oreserve(streambuf_handle<T>& hd,std::size_t size) -> typename T::char_type*
{
	auto p(hd.handle.pptr());
	if(hd.handle.epptr()-p<=size)
		return nullptr;
	hd.handle.pbump(static_cast<int>(size));
	return p+size;
}

template<typename T>
inline void orelease(streambuf_handle<T>& hd,std::size_t size)
{
	hd.handle.pbump(-static_cast<int>(size));
}
}