#pragma once


namespace fast_io
{

template< typename T>
class basic_istring_view
{
public:
	T s;
	using string_view_type = T;
	using char_type = typename T::value_type;
	template<typename ...Args>
	requires std::constructible_from<T,Args...>
	constexpr basic_istring_view(Args&& ...args):s(std::forward<Args>(args)...){}
	constexpr auto& str()
	{
		return s;
	}
	constexpr auto empty() const {return s.empty();}
};

template<typename T>
constexpr void iremove_prefix(basic_istring_view<T>& isv,std::size_t n)
{
	isv.s.remove_prefix(n);
}
template<typename T>
constexpr bool iempty(basic_istring_view<T>& isv)
{
	return isv.s.empty();
}

template<typename T>
constexpr decltype(auto) ifront(basic_istring_view<T>& isv)
{
	return isv.s.front();
}

template<typename T>
constexpr decltype(auto) idata(basic_istring_view<T>& isv)
{
	return isv.s.data();
}

template<typename T>
constexpr decltype(auto) isize(basic_istring_view<T>& isv)
{
	return isv.s.size();
}

template<typename T>
constexpr void iclear(basic_istring_view<T>& isv)
{
	clear(isv.s);
}

template<typename T,std::contiguous_iterator Iter>
requires (sizeof(typename T::value_type)==1||
	std::same_as<typename T::value_type,typename std::iterator_traits<Iter>::value_type>)
inline constexpr Iter read(basic_istring_view<T>& istrvw,Iter begin,Iter end)
{
	using char_type = typename T::value_type;
	using iter_value_type = typename std::iterator_traits<Iter>::value_type;
	if constexpr(std::same_as<char_type,iter_value_type>)
	{
		std::size_t const cped(istrvw.str().copy(std::to_address(begin),
			std::to_address(end)-std::to_address(begin)));
		istrvw.str().remove_prefix(cped);
		return begin+cped;
	}
	else
	{
		auto pb(std::to_address(begin));
		auto pe(std::to_address(end));
		std::size_t const bytes((pe-pb)*sizeof(iter_value_type));
		if(istrvw.str().size()<bytes)
		{
			std::size_t const copied(istrvw.str().size()/sizeof(iter_value_type));
			std::memcpy(pb,istrvw.str().data(),copied*sizeof(iter_value_type));
			istrvw.str()={};
			return begin+copied;	
		}
		else
		{
			std::memcpy(pb,istrvw.str().data(),bytes);
			istrvw.str().remove_prefix(bytes);
			return end;
		}
	}

}

using u8istring_view = basic_istring_view<std::u8string_view>;
using istring_view = basic_istring_view<std::string_view>;



template<contiguous_input_stream T>
class contiguous_input_stream_generator
{
public:
	T* ptr_s={};
};

template<contiguous_input_stream T>
class contiguous_input_stream_generator_iterator
{
public:
	T* ptr_s={};
	constexpr auto operator->() noexcept
	{
		return idata(*ptr_s);
	}
	constexpr auto& operator*() noexcept
	{
		return ifront(*ptr_s);
	}
};

template<contiguous_input_stream T>
inline constexpr contiguous_input_stream_generator_iterator<T>& operator++(contiguous_input_stream_generator_iterator<T>& gen) noexcept
{
	iremove_prefix(*gen.ptr_s,1);
	return gen;
}

template<contiguous_input_stream T>
inline constexpr void operator++(contiguous_input_stream_generator_iterator<T>& gen,int) noexcept
{
	iremove_prefix(*gen.ptr_s,1);
}

template<contiguous_input_stream T>
inline constexpr bool operator==(std::default_sentinel_t, contiguous_input_stream_generator_iterator<T> const& b)
{
	return iempty(*b.ptr_s);
}

template<contiguous_input_stream T>
inline constexpr bool operator==(contiguous_input_stream_generator_iterator<T> const& b, std::default_sentinel_t)
{
	return iempty(*b.ptr_s);
}

template<contiguous_input_stream T>
inline constexpr bool operator!=(std::default_sentinel_t, contiguous_input_stream_generator_iterator<T> const& b)
{
	return !iempty(*b.ptr_s);
}

template<contiguous_input_stream T>
inline constexpr bool operator!=(contiguous_input_stream_generator_iterator<T> const& b, std::default_sentinel_t)
{
	return !iempty(*b.ptr_s);
}

template<contiguous_input_stream T>
inline constexpr contiguous_input_stream_generator_iterator<T> begin(contiguous_input_stream_generator<T>& gen)
{
	return {gen.ptr_s};
}
template<contiguous_input_stream T>
inline constexpr std::default_sentinel_t end(contiguous_input_stream_generator<T>&)
{
	return {};
}
template<contiguous_input_stream T>
inline constexpr contiguous_input_stream_generator_iterator<T> cbegin(contiguous_input_stream_generator<T> const& gen)
{
	return {gen.ptr_s};
}
template<contiguous_input_stream T>
inline constexpr std::default_sentinel_t cend(contiguous_input_stream_generator<T> const&)
{
	return {};
}
template<contiguous_input_stream T>
inline constexpr contiguous_input_stream_generator_iterator<T> begin(contiguous_input_stream_generator<T> const& gen)
{
	return {gen.ptr_s};
}
template<contiguous_input_stream T>
inline constexpr std::default_sentinel_t end(contiguous_input_stream_generator<T> const&)
{
	return {};
}

template<contiguous_input_stream T>
inline constexpr contiguous_input_stream_generator<T> igenerator(T& stm)
{
	return {std::addressof(stm)};
}

template<contiguous_input_stream T>
inline constexpr auto ispan(T& stm)
{
	return std::span(idata(stm),isize(stm));
}

/*
template<contiguous_input_stream T>
inline constexpr auto ibuffer_cbegin(T& in)
{
	return data(in);
}

template<contiguous_input_stream T>
inline constexpr bool underflow(T& in)
{
	return false;		//always eof
}

template<contiguous_input_stream T>
struct contiguous_stream_gbegin_proxy_pointer
{
	T* ptr{};
	inline constexpr contiguous_stream_gbegin_proxy_pointer& operator=(T::char_type const* p)
	{
		iremove_prefix(*ptr,p-idata(*ptr));
		return *this;
	}
	inline constexpr contiguous_stream_gbegin_proxy_pointer& operator++()
	{
		iremove_prefix(*ptr,1);
		return *this;
	}
	inline constexpr void operator++(int) noexcept
	{
		iremove_prefix(*ptr,1);
	}
	inline constexpr decltype(auto) operator*() noexcept
	{
		return ifront(*ptr);
	}
	inline constexpr auto operator->() noexcept
	{
		return idata(*ptr);
	}
};

template<contiguous_input_stream T>
struct contiguous_stream_gend_proxy_pointer
{
	T* ptr{};

	inline constexpr contiguous_stream_gend_proxy_pointer& operator=(T::char_type const* p)
	{
		iremove_prefix(*ptr,p-idata(*ptr));
		return *this;
	}
};

template<contiguous_input_stream T>
inline constexpr auto to_address(contiguous_stream_proxy_pointer<T> p)
{
	return idata(p.ptr);
}

template<contiguous_input_stream T>
inline constexpr contiguous_stream_gbegin_proxy_pointer<T> ibuffer_gbegin(T& in)
{
	return {std::addressof(in)};
}

template<contiguous_input_stream T>
inline constexpr contiguous_stream_gend_proxy_pointer ibuffer_gend(T& in)
{
	return {std::addressof(in)};
}
*/
}
