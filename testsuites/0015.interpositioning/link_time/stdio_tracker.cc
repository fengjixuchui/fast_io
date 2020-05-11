
#include "../../../include/fast_io_device.h"
#include <cstdarg>
/* malloc wrapper function */

#ifndef NDEBUG
fast_io::onative_file __fast_io_native_file_debugger("debug_report_log.txt");
#endif

extern "C" int __real_vprintf(char const* format, va_list ap) noexcept;

extern "C" int __wrap_vprintf(char const* format, va_list ap) noexcept
{
#ifndef NDEBUG
	debug_println(__fast_io_native_file_debugger,std::chrono::system_clock::now()," ",__FILE__ ,":__wrap_vprintf ",format);
#endif
	return __real_vprintf(format,ap);
}

extern "C" int __real_printf(char const* format, ... ) noexcept;

extern "C" int __wrap_printf(char const* format, ... ) noexcept
{
#ifndef NDEBUG
	debug_println(__fast_io_native_file_debugger,std::chrono::system_clock::now()," ",__FILE__ ,":__wrap_printf fp: format: ",format);
#endif
	std::va_list args;
	va_start(args, format);
	int ret = __real_vprintf(format, args);
	va_end(args);
	return ret;
}


extern "C" int __real_vfprintf(FILE *s, char const* format, va_list ap) noexcept;

extern "C" int __wrap_vfprintf(FILE *s, char const* format, va_list ap) noexcept
{
#ifndef NDEBUG
	debug_println(__fast_io_native_file_debugger,std::chrono::system_clock::now()," ",__FILE__ ,":__wrap_vfprintf(",fast_io::unsigned_view(s),",",format,")");
#endif
	return __real_vfprintf(s,format,ap);
}

extern "C" int __real_fprintf(std::FILE* stream, char const* format, ... ) noexcept;

extern "C" int __wrap_fprintf(std::FILE* stream, char const* format, ... ) noexcept
{
#ifndef NDEBUG
	debug_println(__fast_io_native_file_debugger,std::chrono::system_clock::now()," ",__FILE__ ,":__wrap_fprintf fp:",fast_io::unsigned_view(stream),",format: ",format);
#endif
	std::va_list args;
	va_start(args, format);
	int ret = __real_vfprintf(stream, format, args);
	va_end(args);
	return ret;
}


extern "C" int __real_vsprintf( char* buffer,  char const* format, va_list vlist ) noexcept;

extern "C" int __wrap_vsprintf( char* buffer, char const* format, va_list vlist ) noexcept
{
#ifndef NDEBUG
	debug_println(__fast_io_native_file_debugger,std::chrono::system_clock::now()," ",__FILE__ ,":__wrap_vsprintf(",fast_io::unsigned_view(buffer),",",format,")");
#endif
	return __real_vsprintf(buffer,format,vlist);
}

extern "C" int __real_sprintf(char* buffer, char const* format, ... ) noexcept;

extern "C" int __wrap_sprintf(char* buffer, char const* format, ... ) noexcept
{
#ifndef NDEBUG
	debug_println(__fast_io_native_file_debugger,std::chrono::system_clock::now()," ",__FILE__ ,":__wrap_sprintf fp:",fast_io::unsigned_view(buffer),",format: ",format);
#endif
	std::va_list args;
	va_start(args, format);
	int ret = __real_vsprintf(buffer, format, args);
	va_end(args);
	return ret;
}

extern "C" int __real_vsnprintf( char* buffer, std::size_t buf_size,  char const* format, va_list vlist ) noexcept;

extern "C" int __wrap_vsnprintf( char* buffer, std::size_t buf_size, char const* format, va_list vlist ) noexcept
{
#ifndef NDEBUG
	debug_println(__fast_io_native_file_debugger,std::chrono::system_clock::now()," ",__FILE__ ,":__wrap_vsnprintf(",fast_io::unsigned_view(buffer),",",format,")");
#endif
	return __real_vsnprintf(buffer,buf_size,format,vlist);
}

extern "C" int __real_snprintf(char* buffer, std::size_t buf_size, char const* format, ... ) noexcept;

extern "C" int __wrap_snprintf(char* buffer, std::size_t buf_size, char const* format, ... ) noexcept
{
#ifndef NDEBUG
	debug_println(__fast_io_native_file_debugger,std::chrono::system_clock::now()," ",__FILE__ ,":__wrap_snprintf fp:",fast_io::unsigned_view(buffer),",format: ",format);
#endif
	std::va_list args;
	va_start(args, format);
	int ret = __real_vsnprintf(buffer, buf_size, format, args);
	va_end(args);
	return ret;
}

extern "C" int __real_vscanf(char const* format, va_list vlist ) noexcept;

extern "C" int __wrap_vscanf(char const* format, va_list vlist ) noexcept
{
#ifndef NDEBUG
	debug_println(__fast_io_native_file_debugger,std::chrono::system_clock::now()," ",__FILE__ ,":__real_vscanf fp: format: ",format);
#endif
	return __real_vscanf(format, vlist);
}

extern "C" int __wrap_scanf(char const* format, ... ) noexcept
{
#ifndef NDEBUG
	debug_println(__fast_io_native_file_debugger,std::chrono::system_clock::now()," ",__FILE__ ,":__wrap_scanf fp: format: ",format);
#endif
	std::va_list args;
	va_start(args, format);
	int ret = __real_vscanf(format, args);
	va_end(args);
	return ret;
}

extern "C" int __real_vfscanf(std::FILE* fp, char const* format, va_list vlist ) noexcept;

extern "C" int __wrap_vfscanf(std::FILE* fp, char const* format, va_list vlist ) noexcept
{
#ifndef NDEBUG
	debug_println(__fast_io_native_file_debugger,std::chrono::system_clock::now()," ",__FILE__ ,":__wrap_vfscanf fp:",fast_io::unsigned_view(fp),",format: ",format);
#endif
	return __real_vfscanf(fp,format, vlist);
}

extern "C" int __wrap_fscanf(std::FILE* fp, char const* format, ... ) noexcept
{
#ifndef NDEBUG
	debug_println(__fast_io_native_file_debugger,std::chrono::system_clock::now()," ",__FILE__ ,":__wrap_fscanf fp:",fast_io::unsigned_view(fp),",format: ",format);
#endif
	std::va_list args;
	va_start(args, format);
	int ret = __real_vfscanf(fp, format, args);
	va_end(args);
	return ret;
}
extern "C" int __real_vsscanf(const char* buffer,char const* format, va_list vlist ) noexcept;

extern "C" int __wrap_vsscanf(const char* buffer,char const* format, va_list vlist ) noexcept
{
#ifndef NDEBUG
	debug_println(__fast_io_native_file_debugger,std::chrono::system_clock::now()," ",__FILE__ ,":__wrap_vsscanf ",fast_io::unsigned_view(buffer),",format: ",format);
#endif
	return __real_vsscanf(buffer,format,vlist);
}

extern "C" int __wrap_sscanf(const char* buffer,char const* format, ... ) noexcept
{
#ifndef NDEBUG
	debug_println(__fast_io_native_file_debugger,std::chrono::system_clock::now()," ",__FILE__ ,":__wrap_sscanf ",fast_io::unsigned_view(buffer),",format: ",format);
#endif
	std::va_list args;
	va_start(args, format);
	int ret = __wrap_vsscanf(buffer,format, args);
	va_end(args);
	return ret;
}
extern "C" int __real_fputs(char const* ptr,std::FILE* stream) noexcept;

extern "C" int __wrap_fputs(char const* ptr,std::FILE* stream) noexcept
{
#ifndef NDEBUG
	debug_println(__fast_io_native_file_debugger,std::chrono::system_clock::now()," ",__FILE__ ,":__wrap_fputs fp:",fast_io::unsigned_view(stream),",string: ",ptr);
#endif
	return __real_fputs(ptr,stream);
}

extern "C" int __real_puts(char const* ptr) noexcept;

extern "C" int __wrap_puts(char const* ptr) noexcept
{
#ifndef NDEBUG
	debug_println(__fast_io_native_file_debugger,std::chrono::system_clock::now()," ",__FILE__ ,":__wrap_puts string: ",ptr);
#endif
	return __real_fputs(ptr,stdout);
}

/*

g++ -c stdio_tracker.cc -Ofast -std=c++20
*/