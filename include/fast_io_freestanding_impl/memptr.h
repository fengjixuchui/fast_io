#pragma once

namespace fast_io
{
namespace details
{
//usable unique_ptr in constexpr context
template<typename T>
class temp_unique_arr_ptr
{
public:
	T* ptr{};
	constexpr temp_unique_arr_ptr()=default;
#if __cpp_constexpr_dynamic_alloc >= 201907L
	constexpr
#endif
	temp_unique_arr_ptr(std::size_t size):ptr(new T[size]){}
	temp_unique_arr_ptr(temp_unique_arr_ptr const&)=delete;
	temp_unique_arr_ptr& operator=(temp_unique_arr_ptr const&)=delete;
	constexpr temp_unique_arr_ptr(temp_unique_arr_ptr&& bmv) noexcept:ptr(bmv.ptr)
	{
		bmv.ptr=nullptr;
	}
	constexpr T* data() noexcept
	{
		return ptr;
	}
	constexpr T* data() const noexcept
	{
		return ptr;
	}
#if __cpp_constexpr_dynamic_alloc >= 201907L
	constexpr
#endif
	temp_unique_arr_ptr& operator=(temp_unique_arr_ptr&& bmv) noexcept
	{
		if(bmv.ptr==ptr)
			return *this;
		delete[] ptr;
		ptr=bmv.ptr;
		bmv.ptr=nullptr;
		return *this;
	}
#if __cpp_constexpr_dynamic_alloc >= 201907L
	constexpr
#endif
	~temp_unique_arr_ptr()
	{
		delete[] ptr;
	}
};
}
}