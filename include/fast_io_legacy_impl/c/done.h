#pragma once

namespace fast_io
{

namespace details
{

#if defined(__CYGWIN__)
[[gnu::dllimport]] extern std::size_t __cdecl my_cygwin_fwrite_unlocked(void const* __restrict buffer,std::size_t size,std::size_t count,FILE* __restrict) noexcept asm("fwrite_unlocked");
[[gnu::dllimport]] extern std::size_t __cdecl my_cygwin_fread_unlocked(void* __restrict buffer,std::size_t size,std::size_t count,FILE* __restrict) noexcept asm("fread_unlocked");
#endif

inline std::size_t c_fwrite_unlocked_impl(void const* __restrict begin,std::size_t type_size,std::size_t count,std::FILE* __restrict fp)
{
#if defined(__NEWLIB__) && !defined(__CYGWIN__)
	struct _reent rent;
	std::size_t written_count{_fwrite_unlocked_r(__builtin_addressof(rent),begin,type_size,count,fp)};
	if(!written_count)[[unlikely]]
		throw_posix_error(rent._errno);
	return written_count;
#else
	if(count==0)[[unlikely]]
		return 0;
	std::size_t written_count{
#if defined(_MSC_VER)||defined(_UCRT)
	_fwrite_nolock
#elif defined(__CYGWIN__)
	my_cygwin_fwrite_unlocked
#elif defined(__NEWLIB__) && !defined(__IMPL_UNLOCKED__)
	fwrite
#elif defined(_POSIX_SOURCE) || defined(__BSD_VISIBLE)
	fwrite_unlocked 
#elif defined(__MINGW32__)
#if defined(__MSVCRT_VERSION__) && __MSVCRT_VERSION__ >= 0x800
	::fast_io::win32::_fwrite_nolock
#else
	::fast_io::win32::fwrite
#endif
#else
	fwrite
#endif
	(begin,type_size,count,fp)};
	if(!written_count)[[unlikely]]
		throw_posix_error();
#endif
	return written_count;
}

inline std::size_t c_fread_unlocked_impl(void* __restrict begin,std::size_t type_size,std::size_t count,std::FILE* __restrict fp)
{
#if defined(__NEWLIB__) && !defined(__CYGWIN__)
	struct _reent rent;
	std::size_t read_count{_fread_unlocked_r(__builtin_addressof(rent),begin,type_size,count,fp)};
	if(read_count==0)[[unlikely]]
	{
		if(__sferror(fp))
			throw_posix_error(rent._errno);
	}
	return read_count;
#else
	std::size_t read_count{
#if defined(_MSC_VER)||defined(_UCRT)
	_fread_nolock
#elif defined(__CYGWIN__)
	my_cygwin_fread_unlocked
#elif defined(__NEWLIB__) && !defined(__IMPL_UNLOCKED__)
	fread
#elif defined(_POSIX_C_SOURCE) || defined(__BSD_VISIBLE)
	fread_unlocked
#elif defined(__MINGW32__)
#if defined(__MSVCRT_VERSION__) && __MSVCRT_VERSION__ >= 0x800
	::fast_io::win32::_fread_nolock
#else
	::fast_io::win32::fread
#endif
#else
	fread
#endif
	(begin,type_size,count,fp)};
	if(read_count==0)[[unlikely]]
	{
		if(
#ifdef __NEWLIB__
	__sferror(fp)
#elif defined(_POSIX_C_SOURCE) || defined(__BSD_VISIBLE) || defined(__DARWIN_C_LEVEL)
	ferror_unlocked(fp)
#elif defined(__MINGW32__)
	fp->_flag&0x0020
#else
	ferror(fp)
#endif
		)
			throw_posix_error();
	}
		
#endif
	return read_count;
}



template<std::integral char_type>
inline std::size_t c_io_write_impl(basic_c_io_observer_unlocked<char_type> cfhd,char_type const* begin,char_type const* end)
{
	std::ptrdiff_t const count(end-begin);
	if constexpr((std::same_as<char_type,char>&&buffer_io_stream<c_io_observer_unlocked>)
	||(std::same_as<char_type,wchar_t>&&buffer_io_stream<wc_io_observer_unlocked>)
	||(std::same_as<char_type,char8_t>&&buffer_output_stream<u8c_io_observer_unlocked>)
	||(std::same_as<char_type,char16_t>&&buffer_output_stream<u16c_io_observer_unlocked>)
	||(std::same_as<char_type,char32_t>&&buffer_output_stream<u32c_io_observer_unlocked>)
)
	{
		auto curr{obuffer_curr(cfhd)};
		auto ed{obuffer_end(cfhd)};
		if(count<ed-curr)[[likely]]
		{
			non_overlapped_copy_n(begin,count,curr);
			obuffer_set_curr(cfhd,curr+count);
			return count;
		}
	}
	return c_fwrite_unlocked_impl(begin,sizeof(char_type),static_cast<std::size_t>(count),cfhd.fp);
}

template<std::integral char_type>
inline std::size_t c_io_read_impl(basic_c_io_observer_unlocked<char_type> cfhd,char_type* begin,char_type* end)
{
	std::ptrdiff_t const count(end-begin);
	if constexpr((std::same_as<char_type,char>&&buffer_io_stream<c_io_observer_unlocked>)
	||(std::same_as<char_type,wchar_t>&&buffer_io_stream<wc_io_observer_unlocked>)
	||(std::same_as<char_type,char8_t>&&buffer_io_stream<u8c_io_observer_unlocked>)
	||(std::same_as<char_type,char16_t>&&buffer_io_stream<u16c_io_observer_unlocked>)
	||(std::same_as<char_type,char32_t>&&buffer_io_stream<u32c_io_observer_unlocked>)
)
	{
		auto curr{ibuffer_curr(cfhd)};
		auto ed{ibuffer_end(cfhd)};
		if(count<ed-curr)[[likely]]
		{
			non_overlapped_copy_n(curr,count,begin);
			ibuffer_set_curr(cfhd,curr+count);
			return count;
		}
	}
	return c_fread_unlocked_impl(begin,sizeof(char_type),static_cast<std::size_t>(count),cfhd.fp);
}

}

template<std::integral T,::fast_io::freestanding::contiguous_iterator Iter>
requires (std::same_as<T,::fast_io::freestanding::iter_value_t<Iter>>||std::same_as<T,char>)
inline Iter write(basic_c_io_observer_unlocked<T> cfhd,Iter cbegin,Iter cend)
{
	if constexpr(std::same_as<::fast_io::freestanding::iter_value_t<Iter>,T>)
		return cbegin+details::c_io_write_impl(cfhd,::fast_io::freestanding::to_address(cbegin),::fast_io::freestanding::to_address(cend));
	else
		return cbegin+details::c_io_write_impl(cfhd,reinterpret_cast<char const*>(::fast_io::freestanding::to_address(cbegin)),reinterpret_cast<char const*>(::fast_io::freestanding::to_address(cend)))/sizeof(*cbegin);
}

template<std::integral T,::fast_io::freestanding::contiguous_iterator Iter>
requires (std::same_as<T,::fast_io::freestanding::iter_value_t<Iter>>||std::same_as<T,char>)
[[nodiscard]] inline Iter read(basic_c_io_observer_unlocked<T> cfhd,Iter begin,Iter end)
{
	if constexpr(std::same_as<::fast_io::freestanding::iter_value_t<Iter>,T>)
		return begin+details::c_io_read_impl(cfhd,::fast_io::freestanding::to_address(begin),::fast_io::freestanding::to_address(end));
	else
		return begin+details::c_io_read_impl(cfhd,reinterpret_cast<char*>(::fast_io::freestanding::to_address(begin)),reinterpret_cast<char*>(::fast_io::freestanding::to_address(end)))/sizeof(*begin);
}

}
