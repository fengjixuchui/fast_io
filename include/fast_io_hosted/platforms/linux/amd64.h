#pragma once
//https://github.com/llvm-mirror/compiler-rt/blob/master/lib/sanitizer_common/sanitizer_syscall_linux_x86_64.inc

namespace fast_io
{

template<std::size_t syscall_number,std::signed_integral return_value_type>
requires (1<sizeof(return_value_type))
inline auto system_call()
{
	return_value_type ret;
	__asm__ __volatile__
	(
	"syscall"
	: "=a" (ret)
	//EDI      RSI       RDX
	: "0"(syscall_number)
	: "rcx", "r11", "memory", "cc"
	);
	return ret;
}

template<std::size_t syscall_number,std::signed_integral return_value_type>
requires (1<sizeof(return_value_type))
inline auto system_call(auto p1)
{
	return_value_type ret;
	__asm__ __volatile__
	(
	"syscall"
	: "=a" (ret)
	//EDI      RSI       RDX
	: "0"(syscall_number), "D"(p1)
	: "rcx", "r11", "memory", "cc"
	);
	return ret;
}

template<std::size_t syscall_number>
inline void system_call_no_return(auto p1)
{
	std::size_t ret;
	__asm__ __volatile__
	(
	"syscall"
	: "=a" (ret)
	//EDI      RSI       RDX
	: "0"(syscall_number), "D"(p1)
	: "rcx", "r11", "memory", "cc"
	);
}

template<std::size_t syscall_number,std::signed_integral return_value_type>
requires (1<sizeof(return_value_type))
inline auto system_call(auto p1, auto p2)
{
	return_value_type ret;
	__asm__ __volatile__
	(
	"syscall"
	: "=a" (ret)
	//EDI      RSI       RDX
	: "0"(syscall_number), "D"(p1), "S"(p2)
	: "rcx", "r11", "memory", "cc"
	);
	return ret;
}

template<std::size_t syscall_number,std::signed_integral return_value_type>
requires (1<sizeof(return_value_type))
inline auto system_call(auto p1, auto p2, auto p3)
{
	return_value_type ret;
	__asm__ __volatile__
	(
	"syscall"
	: "=a" (ret)
	//EDI      RSI       RDX
	: "0"(syscall_number), "D"(p1), "S"(p2), "d"(p3)
	: "rcx", "r11", "memory", "cc"
	);
	return ret;
}

template<std::size_t syscall_number,std::signed_integral return_value_type>
requires (1<sizeof(return_value_type))
inline auto system_call(auto p1, auto p2, auto p3, auto p4)
{
	return_value_type ret;
	__asm__ __volatile__
	(
	"mov %5, %%r10;"
	"syscall"
	: "=a" (ret)
	//EDI      RSI       RDX
	: "0"(syscall_number), "D"(p1), "S"(p2), "d"(p3), "r"((std::uint64_t)p4)
	: "rcx", "r11", "r10", "memory", "cc"
	);
	return ret;
}

template<std::size_t syscall_number,std::signed_integral return_value_type>
requires (1<sizeof(return_value_type))
inline auto system_call(auto p1, auto p2, auto p3, auto p4,auto p5)
{
	return_value_type ret;
	__asm__ __volatile__
	(
	"mov %5, %%r10;"
	"mov %6, %%r8;"
	"syscall"
	: "=a" (ret)
	//EDI      RSI       RDX
	: "0"(syscall_number), "D"(p1), "S"(p2), "d"(p3), "r"((std::uint64_t)p4), "r"((std::uint64_t)p5)
	: "rcx", "r11", "r10", "r8", "memory", "cc"
	);
	return ret;
}
template<std::size_t syscall_number,std::signed_integral return_value_type>
requires (1<sizeof(return_value_type))
inline auto system_call(auto p1, auto p2, auto p3, auto p4,auto p5,auto p6)
{
	return_value_type ret;
	__asm__ __volatile__
	(
	"mov %5, %%r10;"
	"mov %6, %%r8;"
	"mov %7, %%r9;"
	"syscall"
	: "=a" (ret)
	//EDI      RSI       RDX
	: "0"(syscall_number), "D"(p1), "S"(p2), "d"(p3), "r"((std::uint64_t)p4),"r"((std::uint64_t)p5),"r"((std::uint64_t)p6)
	: "rcx", "r11", "r10", "r8", "r9", "memory", "cc"
	);
	return ret;
}


template<std::integral I>
inline void fast_exit(I ret)
{
#if defined(__linux__) && defined(__x86_64__)
	system_call_no_return<60>(ret);
#else
	_exit(ret);
#endif
}
}