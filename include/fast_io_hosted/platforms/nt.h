#pragma once

namespace fast_io
{

template<std::integral ch_type>
class basic_nt_io_observer
{
public:
	using native_handle_type = void*;
	using char_type = ch_type;
	native_handle_type handle{};
	constexpr auto& native_handle() noexcept
	{
		return handle;
	}
	constexpr auto& native_handle() const noexcept
	{
		return handle;
	}
	explicit constexpr operator bool() const noexcept
	{
		return handle;
	}
};


template<std::integral ch_type,std::contiguous_iterator Iter>
inline Iter write(basic_nt_io_observer<ch_type> obs,Iter cbegin,Iter cend)
{
	std::size_t to_write((cend-cbegin)*sizeof(*cbegin));
	if constexpr(4<sizeof(std::size_t))
		if(static_cast<std::size_t>(UINT32_MAX)<to_write)
			to_write=static_cast<std::size_t>(UINT32_MAX);
	win32::nt::io_status_block block{};
	auto const status{win32::nt::nt_write_file(obs.handle,nullptr,nullptr,nullptr,
		std::addressof(block), std::to_address(cbegin), static_cast<std::uint32_t>(to_write), nullptr, nullptr)};
	if(status)
#ifdef __cpp_exceptions
		throw nt_error(status);
#else
		fast_terminate();
#endif
	return cbegin+(*block.Information)/sizeof(*cbegin);
}

template<std::integral ch_type>
inline constexpr void flush(basic_nt_io_observer<ch_type>) noexcept
{

}

template<std::integral ch_type>
class basic_nt_io_handle:public basic_nt_io_observer<ch_type>
{
public:
	using char_type = ch_type;
	using native_handle_type = void*;
protected:
	void close_impl() noexcept
	{
		if(this->native_handle())
			win32::nt::nt_close(this->native_handle());
	}
public:
	constexpr basic_nt_io_handle() noexcept = default;
	constexpr basic_nt_io_handle(native_handle_type hd) noexcept:basic_nt_io_observer<ch_type>(hd){}
	constexpr void reset() noexcept
	{
		this->native_handle()=nullptr;
	}
};


template<std::integral ch_type>
class basic_nt_file:public basic_nt_io_handle<ch_type>
{
public:
	
};


/*
template<std::integral ch_type,std::contiguous_iterator Iter>
inline Iter read(basic_nt_io_handle<ch_type>& hd,Iter begin,Iter end)
{
	if(::NtReadFile(hd.native_handle(),nullptr,{},{},{}))
	{

	}
}

template<std::integral ch_type,std::contiguous_iterator Iter>
inline Iter write(basic_nt_io_handle<ch_type>& hd,Iter begin,Iter end)
{
	
}

template<std::integral ch_type>
inline void flush(basic_nt_io_handle<ch_type>& hd)
{
	
}

template<std::integral ch_type,bool kernel=false>
class basic_nt_file:public basic_nt_io_handle<ch_type>
{
public:
	using basic_nt_io_handle<ch_type>::native_handle_type;
	using basic_nt_io_handle<ch_type>::char_type;

	template<std::size_t om,perms pm>
	basic_nt_file(std::wstring_view filename,open::interface_t<om>,perms_interface_t<pm>)
	{
		UNICODE_STRING ustr{filename.size(),filename.size(),filename.data()};
		OBJECT_ATTRIBUTES oba{sizeof(OBJECT_ATTRIBUTES),nullptr,std::addressof(ustr)};
		if constexpr(kernel)
			oba.Attributes = 0x00000200;	//0x00000200
		if(::NtCreateFile(std::addressof(native_handle()),
			details::win32_file_openmode<om,pm>::mode.dwDesiredAccess,
			std::addressof(oba),
			nullptr,
			nullptr,
			))
		{

		}
	}
	~basic_nt_file()
	{
		this->close_impl();
	}
};*/
using nt_io_observer=basic_nt_io_observer<char>;

}