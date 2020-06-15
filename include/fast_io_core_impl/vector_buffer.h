#pragma once
//std::vector is not usable in freestanding environments and cause problems for this library
//This is a very simple stuff for internal use

namespace fast_io
{

template<std::integral ch_type>
class vector_buffer
{
public:
	using char_type = ch_type;
	using pointer = char_type;
	using iterator = pointer;
	using const_iterator = pointer;
	using allocator_type = std::allocator<char_type>;
	pointer *beg_ptr{},*end_ptr{},*capacity_ptr{};
	constexpr vector_buffer()=default;
	vector_buffer(vector_buffer const& other)=delete;
	vector_buffer& operator=(vector_buffer const& other)=delete;
#if __cpp_constexpr_dynamic_alloc >= 201907L
	constexpr
#endif
	vector_buffer(vector_buffer&& other) noexcept:beg_ptr(other.beg_ptr),end_ptr(other.end_ptr),capacity_ptr(other.capacity_ptr)
	{
		other.beg_ptr=other.end_ptr=other.capacity_ptr=nullptr;
	}
#if __cpp_constexpr_dynamic_alloc >= 201907L
	constexpr
#endif
	vector_buffer& operator=(vector_buffer&& other) noexcept
	{
		if(std::addressof(other)==this)
			return *this;
		if(beg_ptr)[[likely]]
		{
			allocator_type alloc;
			std::allocator_traits<allocator_type>::deallocate(alloc,beg_ptr,capacity_ptr-beg_ptr);
		}
		beg_ptr=other.beg_ptr;
		end_ptr=other.end_ptr;
		capacity_ptr=other.capacity_ptr;
		other.beg_ptr=other.end_ptr=other.capacity_ptr=nullptr;
		return *this;
	}
#if __cpp_constexpr_dynamic_alloc >= 201907L
	constexpr
#endif
	~vector_buffer()
	{
		if(beg_ptr)[[likely]]
		{
			allocator_type alloc;
			std::allocator_traits<allocator_type>::deallocate(alloc,beg_ptr,capacity_ptr-beg_ptr);
		}
	}
};

template<std::integral ch_type>
[[nodiscard]] constexpr auto obuffer_begin(vector_buffer<ch_type>& ob)
{
	return ob.beg_ptr;
}
template<std::integral ch_type>
[[nodiscard]] constexpr auto obuffer_curr(vector_buffer<ch_type>& ob)
{
	return ob.end_ptr;
}

template<std::integral ch_type>
[[nodiscard]] constexpr auto obuffer_end(vector_buffer<ch_type>& ob)
{
	return ob.capacity_ptr;
}

template<std::integral ch_type>
inline constexpr void obuffer_set_curr(vector_buffer<ch_type>& ob,ch_type* ptr)
{
	ob.end_ptr=ptr;
}

template<std::integral ch_type>
inline constexpr void ogrow(vector_buffer<ch_type>& ob,std::size_t new_capacity)
{
	details::internal_temporary_buffer_impl::ogrow_impl<true>(ob,new_capacity);
}

template<std::integral ch_type>
inline constexpr void overflow(vector_buffer<ch_type>& ob,ch_type ch)
{
	details::internal_temporary_buffer_impl::overflow_impl<true>(ob,ch);
}


template<std::integral char_type>
inline constexpr void otakeover(vector_buffer<char_type>& ob,char_type* beg_ptr,char_type* end_ptr,char_type* cap_ptr)
{
	ob.beg_ptr=beg_ptr;
	ob.end_ptr=end_ptr;
	ob.capacity_ptr=cap_ptr;
}

template<std::integral char_type>
inline constexpr bool ocan_takeover(vector_buffer<char_type>& ob)
{
	return ob.beg_ptr==nullptr;
}

template<std::integral ch_type,std::contiguous_iterator Iter>
requires (std::same_as<ch_type,char>||
	std::same_as<ch_type,typename std::iterator_traits<Iter>::value_type>)
inline constexpr void write(vector_buffer<ch_type>& ob,Iter cbegin,Iter cend)
{
	details::internal_temporary_buffer_impl::write_impl<true>(ob,cbegin,cend);
}

template<std::integral ch_type>
inline constexpr void flush(vector_buffer<ch_type>&){}
template<std::integral ch_type>
inline constexpr auto oallocator(vector_buffer<ch_type>&)
{
	return std::allocator<ch_type>();
}

static_assert(dynamic_buffer_output_stream<vector_buffer<char>>);

}