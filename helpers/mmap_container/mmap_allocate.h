#pragma once
#ifdef _POSIX_C_SOURCE
#include <sys/mman.h>
#endif

namespace fast_io
{

#if defined(__WINNT__) || defined(_MSC_VER)
namespace win32::details
{
extern "C" void* __stdcall VirtualAlloc(void*,std::size_t,std::uint32_t,std::uint32_t);
extern "C" int __stdcall VirtualFree(void*,std::size_t,std::uint32_t);
}
#endif

template<std::size_t page_bytes_exp=12,typename T>
inline constexpr T* svo_allocate(std::size_t n,T* hint=nullptr) noexcept
{
	if(std::is_constant_evaluated())
	{
		std::allocator<T> alloc;
		return std::allocator_traits<std::allocator<T>>::allocate(alloc,n<<page_bytes_exp,hint);
	}
	else
	{

/*
#if defined(__WINNT__) || defined(_MSC_VER)
		std::uint32_t flags{0x00001000|0x00002000};//MEM_COMMIT|MEM_RESERVE
		if constexpr(19<page_bytes_exp)//large pages probably
			flags|=0x20000000;
		return reinterpret_cast<T*>(win32::details::VirtualAlloc(nullptr,n<<page_bytes_exp,
		flags,0x04));
#elif defined(__linux__)&&defined(__x86_64__)
		return bit_cast<T*>(system_call<9,std::ptrdiff_t>(hint,n<<page_bytes_exp,PROT_READ|PROT_WRITE,
			MAP_PRIVATE | MAP_ANONYMOUS,0,0));
#elif defined(_POSIX_C_SOURCE)
		return reinterpret_cast<T*>(mmap(hint,n<<page_bytes_exp,PROT_READ|PROT_WRITE,
			MAP_PRIVATE | MAP_ANONYMOUS,0,0));
#else
#error "current not supported"
#endif
*/
	}
}

template<std::size_t page_bytes_exp=12,typename T>
inline constexpr void svo_deallocate(T* ptr,std::size_t n) noexcept
{
	if(std::is_constant_evaluated())
	{
		std::allocator<T> alloc;
		return std::allocator_traits<std::allocator<T>>::deallocate(alloc,ptr,n<<page_bytes_exp);
	}
	else
	{
		if(ptr==nullptr)
			return;
/*
#if defined(__WINNT__) || defined(_MSC_VER)
		win32::details::VirtualFree(ptr,n<<page_bytes_exp,0x00004000);
#elif defined(__linux__)&&defined(__x86_64__)
		system_call<11,int>(ptr,n<<page_bytes_exp);
#elif defined(_POSIX_C_SOURCE)
		munmap(ptr,n<<page_bytes_exp);
#else
#error "current not supported"
#endif
*/
	}
}
template<typename T,std::size_t page_bytes_exp=12>
class svo_allocation_unique_ptr
{
public:
	T* internal_ptr{};
	std::size_t nb{};
	constexpr T* get() noexcept
	{
		return internal_ptr;
	}
	constexpr T* get() const noexcept
	{
		return internal_ptr;
	}
	constexpr svo_allocation_unique_ptr() = default;
	constexpr svo_allocation_unique_ptr(std::size_t n,T* hint=nullptr):
		internal_ptr(svo_allocate<page_bytes_exp>(n,hint)),nb(n){}
	constexpr T* release() noexcept
	{
		auto temp{internal_ptr};
		internal_ptr = nullptr;
		return temp;
	}
	svo_allocation_unique_ptr(svo_allocation_unique_ptr const&)=delete;
	svo_allocation_unique_ptr& operator=(svo_allocation_unique_ptr const&)=delete;
	constexpr svo_allocation_unique_ptr(svo_allocation_unique_ptr&& bmv) noexcept:internal_ptr(bmv.internal_ptr)
	{
		bmv.internal_ptr=nullptr;
	}
	constexpr svo_allocation_unique_ptr& operator=(svo_allocation_unique_ptr&& bmv) noexcept
	{
		if(bmv.internal_ptr==internal_ptr)[[unlikely]]
			return *this;
		svo_deallocate<page_bytes_exp>(internal_ptr);
		internal_ptr=bmv.internal_ptr;
		bmv.internal_ptr=nullptr;
		return *this;
	}
	constexpr ~svo_allocation_unique_ptr()
	{
		svo_deallocate<page_bytes_exp>(internal_ptr,nb);
	}
};

}