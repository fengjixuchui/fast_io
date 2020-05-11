#pragma once
#include<stddef.h>
#include<stdio.h>
#include<stdbool.h>
#include<string.h>
#include<stdlib.h>
//This library is stil header only. Just need compile for C interface if you want to use C interface

#ifdef __cplusplus
extern "C"
{
#define CXX_FAST_IO_NOEXCEPT noexcept
#else
#define CXX_FAST_IO_NOEXCEPT
#endif
/*
//C++ does not define errno_t. Let's use int instead.
//no check for nullptr. precondition violation!

[[nodiscard("Please NEVER ignore the error code. Ignoring error codes are 99% sources of the security vulnerabilities of C programs.")]] 
*/

int cxx_fast_io_read(char** readed,void* d,char* begin,char* end) CXX_FAST_IO_NOEXCEPT;

int cxx_fast_io_write(char const** written,void* d,char const* begin,char const* end) CXX_FAST_IO_NOEXCEPT;

int cxx_fast_io_flush(void* d) CXX_FAST_IO_NOEXCEPT;

int cxx_fast_io_print_size_t(void* d,size_t value) CXX_FAST_IO_NOEXCEPT;

int cxx_fast_io_print_ptrdiff_t(void* d,ptrdiff_t value) CXX_FAST_IO_NOEXCEPT;

int cxx_fast_io_print_double(void* d,double value) CXX_FAST_IO_NOEXCEPT;

int cxx_fast_io_println_size_t(void* d,size_t value) CXX_FAST_IO_NOEXCEPT;

int cxx_fast_io_println_ptrdiff_t(void* d,ptrdiff_t value) CXX_FAST_IO_NOEXCEPT;

int cxx_fast_io_println_double(void* d,double value) CXX_FAST_IO_NOEXCEPT;

int cxx_fast_io_bufferred_read(char** readed,void* d,char* begin,char* end) CXX_FAST_IO_NOEXCEPT;

int cxx_fast_io_bufferred_write(char const** written,void* d,char const* begin,char const* end) CXX_FAST_IO_NOEXCEPT;

int cxx_fast_io_bufferred_flush(void* d) CXX_FAST_IO_NOEXCEPT;

int cxx_fast_io_bufferred_print_size_t(void* d,size_t value) CXX_FAST_IO_NOEXCEPT;

int cxx_fast_io_bufferred_print_ptrdiff_t(void* d,ptrdiff_t value) CXX_FAST_IO_NOEXCEPT;

int cxx_fast_io_bufferred_print_double(void* d,double value) CXX_FAST_IO_NOEXCEPT;

int cxx_fast_io_bufferred_println_size_t(void* d,size_t value) CXX_FAST_IO_NOEXCEPT;

int cxx_fast_io_bufferred_println_ptrdiff_t(void* d,ptrdiff_t value) CXX_FAST_IO_NOEXCEPT;

int cxx_fast_io_bufferred_println_double(void* d,double value) CXX_FAST_IO_NOEXCEPT;

int cxx_fast_io_bufferred_scan_size_t(void* d,size_t* value) CXX_FAST_IO_NOEXCEPT;

int cxx_fast_io_bufferred_scan_ptrdiff_t(void* d,ptrdiff_t* value) CXX_FAST_IO_NOEXCEPT;

int cxx_fast_io_bufferred_scan_double(void* d,double* value) CXX_FAST_IO_NOEXCEPT;

#if defined(__WINNT__) || defined(_MSC_VER)
int cxx_fast_io_win32_handle_open(void** gen,void* handle,bool noclose,bool buffered) CXX_FAST_IO_NOEXCEPT;
#endif
int cxx_fast_io_posix_fd_open(void** gen,int fd,bool noclose,bool buffered) CXX_FAST_IO_NOEXCEPT;

int cxx_fast_io_c_fp_open(void** gen,FILE* fp,bool noclose,bool buffered) CXX_FAST_IO_NOEXCEPT;

void cxx_fast_io_release(void* d,bool buffered) CXX_FAST_IO_NOEXCEPT;

void cxx_fast_io_buffered_get_opointers(void* d,char*** begin,char*** curr,char*** end) CXX_FAST_IO_NOEXCEPT;

int cxx_fast_io_buffered_overflow(void* d,char ch) CXX_FAST_IO_NOEXCEPT;

int cxx_fast_io_buffered_read(char** readed,void* d,char* begin,char* end) CXX_FAST_IO_NOEXCEPT;

int cxx_fast_io_buffered_write(char const** written,void* d,char const* begin,char const* end) CXX_FAST_IO_NOEXCEPT;

int cxx_fast_io_buffered_flush(void* d) CXX_FAST_IO_NOEXCEPT;

void cxx_fast_io_buffered_get_ipointers(void* d,char*** begin,char*** curr,char*** end) CXX_FAST_IO_NOEXCEPT;

int cxx_fast_io_buffered_underflow(char *ch,void* d) CXX_FAST_IO_NOEXCEPT;

static inline int cxx_fast_io_print_c_str(void* d,char const* str)
{
	char const* out;
	return cxx_fast_io_write(&out,d,str,str+strlen(str));
}

static inline int cxx_fast_io_buffered_print_c_str(void* d,char const* str)
{
	char const* out;
	return cxx_fast_io_buffered_write(&out,d,str,str+strlen(str));

}


#ifdef __cplusplus
}

#endif

#undef CXX_FAST_IO_NOEXCEPT


#ifdef __cplusplus

namespace fast_io
{

template<bool buffered>
class basic_c_interface_file
{
public:
	using native_handle_type=void*;
	using char_type = char*;
	native_handle_type cint_ptr;
	basic_c_interface_file():cint_ptr(0){}
	basic_c_interface_file(native_handle_type hd):cint_ptr(hd){};
#if __cplusplus>=201103L
	basic_c_interface_file(basic_c_interface_file const&)=delete;
	basic_c_interface_file& operator=(basic_c_interface_file const&)=delete;
	basic_c_interface_file(basic_c_interface_file&& bmv) noexcept:cint_ptr(bmv.cint_ptr)
	{
		bmv.cint_ptr=nullptr;
	}
	basic_c_interface_file& operator=(basic_c_interface_file&& bmv) noexcept
	{
		if(bmv.cint_ptr==cint_ptr)
			return *this;
		cxx_fast_io_release(cint_ptr,buffered);
		cint_ptr=bmv.cint_ptr;
		bmv.cint_ptr=nullptr;
		return *this;
	}
#else
private:
	basic_c_interface_file(basic_c_interface_file const&){}
	basic_c_interface_file& operator=(basic_c_interface_file const&){}
public:
#endif
	native_handle_type const& native_handle() const
	{
		return cint_ptr;
	}
	native_handle_type& native_handle()
	{
		return cint_ptr;
	}
	native_handle_type release()
	{
		native_handle_type hd(cint_ptr);
		cint_ptr=0;
		return hd;
	}
	~basic_c_interface_file()
	{
		cxx_fast_io_release(cint_ptr,buffered);
	}
};

using c_interface_file_buffered=basic_c_interface_file<true>;
using c_interface_file=basic_c_interface_file<false>;
}

#endif