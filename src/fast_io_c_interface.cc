#include"../include/fast_io_device.h"
#include"../include/fast_io_c_interface.h"
#include"../include/fast_io_legacy_impl/c/impl.h"

namespace fast_io
{

namespace details
{
template<bool buffered,typename Func>
constexpr inline int c_interface_call(Func f,void* d) noexcept
{
	try
	{
		if constexpr(buffered)
			f(*bit_cast<iobuf_io_file*>(d));
		else if constexpr(!buffered)
		{
			io_io_observer iob{bit_cast<io_io_observer::native_handle_type>(d)};
			f(iob);
		}
		return {};
	}
	catch(std::system_error const& error)
	{
		if(error.code().category()==std::generic_category())
			return error.code().value();
		return EIO;
	}
	catch(...)
	{
		return EIO;
	}
}
template<bool buffered,bool line,bool sck=false,typename T>
constexpr inline auto c_interface_print(void* d,T value) noexcept
{
	return details::c_interface_call<buffered>([&](auto& iob){
		if constexpr(sck)
			scan(iob,value);
		else
		{
		if constexpr(line)
			println(iob,value);
		else
			print(iob,value);
		}
	},d);
}

template<typename observer_type,typename file_type,typename T>
inline int c_interface_open(void** gen,T value, bool noclose, bool buffered) noexcept
{
	try
	{
		if(noclose)
		{
			if(buffered)
				*gen=bit_cast<void*>(new iobuf_io_file(fast_io::io_cookie,
					std::in_place_type<observer_type>,value));
			else
				*gen=bit_cast<void*>(io_file(fast_io::io_cookie,
					std::in_place_type<observer_type>,value).release());
		}
		else
		{
			if(buffered)
				*gen=bit_cast<void*>(new iobuf_io_file(fast_io::io_cookie,
					std::in_place_type<file_type>,value));
			else
				*gen=bit_cast<void*>(io_file(fast_io::io_cookie,
					std::in_place_type<file_type>,value).release());
		}
		return 0;
	}
	catch(std::system_error const& error)
	{
		if(error.code().category()==std::generic_category())
			return error.code().value();
		return EIO;
	}
	catch(...)
	{
		return EIO;
	}
}


}

extern "C"
{

int cxx_fast_io_read(char** readed,void* d,char* begin,char* end) noexcept
{
	return details::c_interface_call<false>([&](auto iob){
		*readed=read(iob,begin,end);
	},d);
}
int cxx_fast_io_write(char const** written,void* d,char const* begin,char const* end) noexcept
{
	return details::c_interface_call<false>([&](auto iob){
		*written=write(iob,begin,end);
	},d);
}
int cxx_fast_io_flush(void* d) noexcept
{
	return details::c_interface_call<false>([&](auto iob){
		flush(iob);
	},d);
}

int cxx_fast_io_print_size_t(void* d,std::size_t value) noexcept
{
	return details::c_interface_print<false,false>(d,value);
}
int cxx_fast_io_print_ptrdiff_t(void* d,std::ptrdiff_t value) noexcept
{
	return details::c_interface_print<false,false>(d,value);
}
int cxx_fast_io_print_double(void* d,double value) noexcept
{
	return details::c_interface_print<false,false>(d,value);
}

int cxx_fast_io_println_size_t(void* d,std::size_t value) noexcept
{
	return details::c_interface_print<false,true>(d,value);
}
int cxx_fast_io_println_ptrdiff_t(void* d,std::ptrdiff_t value) noexcept
{
	return details::c_interface_print<false,true>(d,value);
}
int cxx_fast_io_println_double(void* d,double value) noexcept
{
	return details::c_interface_print<false,true>(d,value);
}

int cxx_fast_io_bufferred_read(char** readed,void* d,char* begin,char* end) noexcept
{
	return details::c_interface_call<false>([&](auto& iob){
		*readed=read(iob,begin,end);
	},d);
}
int cxx_fast_io_bufferred_write(char const** written,void* d,char const* begin,char const* end) noexcept
{
	return details::c_interface_call<false>([&](auto& iob){
		*written=write(iob,begin,end);
	},d);
}
int cxx_fast_io_bufferred_flush(void* d) noexcept
{
	return details::c_interface_call<false>([&](auto& iob){
		flush(iob);
	},d);
}

int cxx_fast_io_bufferred_print_size_t(void* d,std::size_t value) noexcept
{
	return details::c_interface_print<true,false>(d,value);
}
int cxx_fast_io_bufferred_print_ptrdiff_t(void* d,std::ptrdiff_t value) noexcept
{
	return details::c_interface_print<true,false>(d,value);
}
int cxx_fast_io_bufferred_print_double(void* d,double value) noexcept
{
	return details::c_interface_print<true,false>(d,value);
}

int cxx_fast_io_bufferred_println_size_t(void* d,std::size_t value) noexcept
{
	return details::c_interface_print<true,true>(d,value);
}
int cxx_fast_io_bufferred_println_ptrdiff_t(void* d,std::ptrdiff_t value) noexcept
{
	return details::c_interface_print<true,true>(d,value);
}
int cxx_fast_io_bufferred_println_double(void* d,double value) noexcept
{
	return details::c_interface_print<true,true>(d,value);
}


int cxx_fast_io_bufferred_scan_size_t(void* d,std::size_t* value) noexcept
{
	return details::c_interface_print<true,false,true>(d,*value);
}
int cxx_fast_io_bufferred_scan_ptrdiff_t(void* d,std::ptrdiff_t* value) noexcept
{
	return details::c_interface_print<true,false,true>(d,*value);
}
int cxx_fast_io_bufferred_scan_double(void* d,double* value) noexcept
{
	return details::c_interface_print<true,false,true>(d,*value);
}

#if defined(__WINNT__) || defined(_MSC_VER)
int cxx_fast_io_win32_handle_open(void** gen,void* handle,bool noclose,bool buffered) noexcept
{
	return details::c_interface_open<win32_io_observer,win32_file>(gen,handle,noclose,buffered);
}
#endif

int cxx_fast_io_posix_fd_open(void** gen,int fd,bool noclose,bool buffered) noexcept
{
	return details::c_interface_open<posix_io_observer,posix_file>(gen,fd,noclose,buffered);
}

int cxx_fast_io_c_fp_open(void** gen,std::FILE* fp,bool noclose,bool buffered) noexcept
{
	return details::c_interface_open<c_io_observer,c_file>(gen,fp,noclose,buffered);
}

void cxx_fast_io_release(void* d,bool buffered) noexcept
{
	if(buffered)
		delete bit_cast<iobuf_io_file*>(d);
	else
		delete bit_cast<io_io_observer::native_handle_type>(d);
}

void cxx_fast_io_buffered_get_opointers(void* d,char*** begin,char*** curr,char*** end) noexcept
{
	auto& iob{*bit_cast<iobuf_io_file*>(d)};
	*begin=std::addressof(iob.obuffer.beg);
	*curr=std::addressof(iob.obuffer.curr);
	*end=std::addressof(iob.obuffer.end);
}

int cxx_fast_io_buffered_overflow(void* d,char ch) noexcept
{
	return details::c_interface_call<true>([&](auto& iob){
		overflow(iob,ch);
	},d);
}

int cxx_fast_io_buffered_read(char** readed,void* d,char* begin,char* end) noexcept
{
	return details::c_interface_call<true>([&](auto& iob){
		*readed=read(iob,begin,end);
	},d);
}
int cxx_fast_io_buffered_write(char const** written,void* d,char const* begin,char const* end) noexcept
{
	return details::c_interface_call<true>([&](auto& iob){
		write(iob,begin,end);
		*written=end;
	},d);
}
int cxx_fast_io_buffered_flush(void* d) noexcept
{
	return details::c_interface_call<true>([&](auto& iob){
		flush(iob);
	},d);
}

void cxx_fast_io_buffered_get_ipointers(void* d,char*** begin,char*** curr,char*** end) noexcept
{
	auto& ib{bit_cast<iobuf_io_file*>(d)->native_handle()};
	*begin=std::addressof(ib.ibuffer.beg);
	*curr=std::addressof(ib.ibuffer.curr);
	*end=std::addressof(ib.ibuffer.end);
}

int cxx_fast_io_buffered_underflow(char *ch,void* d) noexcept
{
	return details::c_interface_call<true>([&](auto& iob){
		*ch=underflow(iob);
	},d);
}

}
}