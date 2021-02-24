#pragma once

namespace fast_io::details
{

template<std::integral char_type>
inline
#if __cpp_constexpr >=201907L && __cpp_constexpr_dynamic_alloc >= 201907L && __cpp_lib_is_constant_evaluated >=201811L
constexpr
#endif
char_type* local_operator_new_array_allocate(std::size_t size) noexcept
{
#if __cpp_constexpr >=201907L && __cpp_constexpr_dynamic_alloc >= 201907L && __cpp_lib_is_constant_evaluated >=201811L
	if(std::is_constant_evaluated())
	{
		return new char_type[size];
	}
	else
#endif
	{
#if (defined(_MSC_VER)&&_HAS_EXCEPTIONS!=0) || (!defined(_MSC_VER)&&__cpp_exceptions)
		try
		{
#endif
			return static_cast<char_type*>(operator new(intrinsics::cal_allocation_size_or_die<char_type>(size)));
#if (defined(_MSC_VER)&&_HAS_EXCEPTIONS!=0) || (!defined(_MSC_VER)&&__cpp_exceptions)
		}
		catch(...)
		{
			fast_terminate();
		}
#endif
	}
}

template<std::integral char_type>
inline
#if __cpp_constexpr >=201907L && __cpp_constexpr_dynamic_alloc >= 201907L && __cpp_lib_is_constant_evaluated >=201811L
constexpr
#endif
void local_operator_new_array_deallocate(char_type* ptr,std::size_t size) noexcept
{
#if __cpp_constexpr >=201907L && __cpp_constexpr_dynamic_alloc >= 201907L && __cpp_lib_is_constant_evaluated >=201811L
	if(std::is_constant_evaluated())
	{
		delete[] ptr;
	}
	else
#endif
	{
#if __cpp_sized_deallocation >= 201309L
		operator delete(ptr,size*sizeof(char_type));
#else
		operator delete(ptr);
#endif
	}
}
template<std::integral char_type>
struct local_operator_new_array_ptr
{
	std::size_t size;
	char_type* ptr;
#if __cpp_constexpr >=201907L && __cpp_constexpr_dynamic_alloc >= 201907L && __cpp_lib_is_constant_evaluated >=201811L
	constexpr
#endif
	local_operator_new_array_ptr(std::size_t sz) noexcept:size(sz),ptr(local_operator_new_array_allocate<char_type>(size))
	{}
	local_operator_new_array_ptr(local_operator_new_array_ptr const&)=delete;
	local_operator_new_array_ptr& operator=(local_operator_new_array_ptr const&)=delete;
#if __cpp_constexpr >=201907L && __cpp_constexpr_dynamic_alloc >= 201907L && __cpp_lib_is_constant_evaluated >=201811L
	constexpr
#endif
	~local_operator_new_array_ptr()
	{
		local_operator_new_array_deallocate(ptr,size);
	}
};
}