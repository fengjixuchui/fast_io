#pragma once
namespace fast_io
{

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
		return reinterpret_cast<T*>(operator new[](n<<12,std::align_val_t{alignof(T)},std::nothrow));
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
		return ::operator delete[](ptr,n<<12,std::align_val_t{alignof(T)});
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