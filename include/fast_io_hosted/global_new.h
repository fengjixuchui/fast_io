#pragma once
#ifdef FAST_IO_GLOBAL_NEW

namespace fast_io
{

namespace details::allocation
{
#if defined(__WINNT__) || defined(_MSC_VER)
extern "C" void* __stdcall VirtualAlloc(void*,std::size_t,std::uint32_t,std::uint32_t) noexcept;
extern "C" int __stdcall VirtualFree(void*,std::size_t,std::uint32_t) noexcept;
#endif

template<typename T>
inline constexpr auto map_a_page(std::size_t allocate_bytes,T* hint=nullptr) noexcept
{
#if defined(__WINNT__) || defined(_MSC_VER)
	return reinterpret_cast<T*>(VirtualAlloc(nullptr,allocate_bytes,0x00001000|0x00002000,0x04));
#elif defined(__linux__)&&defined(__x86_64__)
	return reinterpret_cast<T*>(system_call<9,std::ptrdiff_t>(hint,allocate_bytes,PROT_READ|PROT_WRITE,
		MAP_PRIVATE | MAP_ANONYMOUS,0,0));
#elif defined(_POSIX_C_SOURCE)
	return reinterpret_cast<T*>(mmap(hint,allocate_bytes,PROT_READ|PROT_WRITE,
		MAP_PRIVATE | MAP_ANONYMOUS,0,0));
#else
	return reinterpret_cast<T*>(std::realloc(hint,allocate_bytes));
#endif
}

struct page_mapped
{
	std::byte* page_mapped_end{};
	std::byte* page_mapped_capacity{};
	std::size_t allocated_pages{};
};

struct spin_lock_guard
{
	std::atomic_flag* lock;
	spin_lock_guard(std::atomic_flag& e):lock(std::addressof(e))
	{
		while (lock->test_and_set(std::memory_order_acquire));
	}
	spin_lock_guard(spin_lock_guard const&) = delete;
	spin_lock_guard& operator=(spin_lock_guard const&) = delete;
	~spin_lock_guard()
	{
		lock->clear();
	}
};

struct bucket
{
	std::atomic_flag lock{};
	std::byte* flist{};
	page_mapped pm;
};

constinit inline std::array<std::array<std::byte,4096>,7> bucket_extras;

inline std::byte* non_happy_buc_allocate(page_mapped& pm,std::size_t bytes)
{
	if(pm.allocated_pages==0)
	{
		pm.allocated_pages=4096;
		if(4096<bytes)[[unlikely]]
			pm.allocated_pages=bytes;
		else
		{
			pm.page_mapped_capacity=(pm.page_mapped_end=bucket_extras[std::bit_width(bytes>>5)].data())+pm.allocated_pages;
			goto next;
		}
	}
	pm.page_mapped_capacity=(pm.page_mapped_end=map_a_page<std::byte>(pm.allocated_pages))+pm.allocated_pages;
next:;
	pm.allocated_pages<<=1;
	auto temp{pm.page_mapped_end};
	pm.page_mapped_end+=bytes;
	return temp;
}

inline std::byte* buc_allocate(bucket& buc,std::size_t bytes) noexcept
{
	spin_lock_guard lg{buc.lock};
	if(buc.flist==nullptr)[[unlikely]]
	{
		if(buc.pm.page_mapped_end==buc.pm.page_mapped_capacity)[[unlikely]]
			return non_happy_buc_allocate(buc.pm,bytes);
		auto temp{buc.pm.page_mapped_end};
		buc.pm.page_mapped_end+=bytes;
		return temp;
	}
	std::byte* ptr{buc.flist};
	memcpy(std::addressof(buc.flist),buc.flist,sizeof(std::uintptr_t));
	return ptr;
}

inline void buc_deallocate(bucket& buc,std::byte* ptr) noexcept
{
	spin_lock_guard lg{buc.lock};
	memcpy(ptr,std::addressof(buc.flist),sizeof(std::uintptr_t));
	buc.flist=ptr;
}

inline constinit std::array<bucket,sizeof(std::byte*)*8-5> buckets;

inline std::byte* real_allocate(std::size_t sz)
{
	using namespace fast_io::details::allocation;
	return buc_allocate(fast_io::details::allocation::buckets[std::bit_width(sz>>5)],std::bit_ceil(sz));
}
}
}

inline void* operator new(std::size_t sz) noexcept
{
	return fast_io::details::allocation::real_allocate(sz);
}

inline void operator delete(void* ptr,std::size_t sz) noexcept
{
	if(ptr==nullptr)[[unlikely]]
		return;
	fast_io::details::allocation::buc_deallocate(fast_io::details::allocation::buckets[std::bit_width(sz>>5)],reinterpret_cast<std::byte*>(ptr));
}

inline void* operator new[](std::size_t sz) noexcept
{
	auto ptr{fast_io::details::allocation::real_allocate(sizeof(std::size_t)+sz)};
	std::memcpy(ptr,std::addressof(sz),sizeof(sz));
	return ptr+sizeof(std::size_t);
}

inline void operator delete[](void* ptr) noexcept
{
	if(ptr==nullptr)[[unlikely]]
		return;
	std::size_t bytes;
	auto real_ptr{reinterpret_cast<std::byte*>(ptr)-sizeof(std::size_t)};
	std::memcpy(std::addressof(bytes),real_ptr,sizeof(std::size_t));
	operator delete(real_ptr,bytes);
}

#endif