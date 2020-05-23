#pragma once

#include<fstream>

namespace fast_io
{

//stream has performance problems on windows for libstdc++
template<typename T>
class filebuf_pub:public T
{
public:
	using T::showmanyc;
	using T::setg;
	using T::eback;
	using T::gptr;
	using T::egptr;
	using T::underflow;

	using T::pbase;
	using T::pptr;
	using T::epptr;
	using T::overflow;
	using T::pbump;
	using T::setp;
#ifdef __GLIBCXX__
	using T::_M_file;
#endif
};


template<std::integral ch_type,typename Traits=std::char_traits<ch_type>>
class basic_filebuf_handle
{
public:
	using native_handle_type = filebuf_pub<std::basic_filebuf<ch_type,Traits>>*;
	using char_type = ch_type;

/*
https://www.ginac.de/~kreckel/fileno/

Hack iostream's internal
*/
	native_handle_type handle;
	basic_filebuf_handle(std::basic_filebuf<ch_type,Traits>* buf):
		handle(static_cast<filebuf_pub<std::basic_filebuf<ch_type,Traits>>*>(buf)){}
	basic_filebuf_handle(std::basic_ifstream<ch_type,Traits>& w):
		handle(static_cast<filebuf_pub<std::basic_filebuf<ch_type,Traits>>*>(w.rdbuf())){}
	basic_filebuf_handle(std::basic_ofstream<ch_type,Traits>& w):
		handle(static_cast<filebuf_pub<std::basic_filebuf<ch_type,Traits>>*>(w.rdbuf())){}
	basic_filebuf_handle(std::basic_fstream<ch_type,Traits>& w):
		handle(static_cast<filebuf_pub<std::basic_filebuf<ch_type,Traits>>*>(w.rdbuf())){}
#ifdef __GLIBCXX__
	explicit operator basic_c_io_observer_unlocked<char_type>() const
	{
		return {handle->_M_file.file()};
	}
	explicit operator basic_c_io_observer<char_type>() const
	{
		return {handle->_M_file.file()};
	}

	explicit operator basic_posix_io_observer<char_type>() const
	{
		return static_cast<basic_c_io_observer_unlocked<char_type>>(*this);
	}
#ifdef __WINNT__
	explicit operator basic_win32_io_observer<char_type>() const
	{
		return static_cast<basic_posix_io_observer<char_type>>(*this);
	}
#endif

#endif
};

using filebuf_handle = basic_filebuf_handle<char>;
#ifdef __GLIBCXX__
#ifdef __linux__
template<std::integral T,typename Traits>
inline auto zero_copy_in_handle(basic_filebuf_handle<T,Traits>& h)
{
	return h.handle->_M_file.fd();
}

template<std::integral T,typename Traits>
inline auto zero_copy_out_handle(basic_filebuf_handle<T,Traits>& h)
{
	return h.handle->_M_file.fd();
}
#endif
#endif

template<std::integral char_type,typename Traits,std::contiguous_iterator Iter>
inline Iter read(basic_filebuf_handle<char_type,Traits>& hd,Iter begin,Iter end)
{
	return begin+(hd.handle->sgetn(static_cast<char_type*>(static_cast<void*>(std::to_address(begin))),(end-begin)*sizeof(*begin)/sizeof(char_type))*sizeof(char_type)/sizeof(*begin));
}

template<std::integral char_type,typename Traits,std::contiguous_iterator Iter>
inline void write(basic_filebuf_handle<char_type,Traits>& hd,Iter begin,Iter end) 
{
	if(!hd.handle->sputn(static_cast<char_type const*>(static_cast<void const*>(std::to_address(begin))),(end-begin)*sizeof(*begin)/sizeof(char_type)))
#ifdef __cpp_exceptions
		throw posix_error(EIO);
#else
		fast_terminate();
#endif
}

template<typename T,typename Traits>
inline void flush(basic_filebuf_handle<T,Traits>& hd)
{
	hd.handle->flush();
}

template<typename T,typename Traits>
inline auto oreserve(basic_filebuf_handle<T,Traits>& hd,std::size_t size) -> typename T::char_type*
{
	auto p(hd.handle->pptr());
	if(hd.handle->epptr()-p<=size)
		return nullptr;
	hd.handle->pbump(static_cast<int>(size));
	return p+size;
}
template<typename T,typename Traits>
inline void orelease(basic_filebuf_handle<T,Traits>& hd,std::size_t size)
{
	hd.handle->pbump(-static_cast<int>(size));
}
}
