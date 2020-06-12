#pragma once

namespace fast_io
{
template<typename T,typename M,std::size_t init_mem_size=UINT32_MAX>
class basic_omap
{
public:
	using native_handle_type = T;
	using map_handle_type = M;
private:
	native_handle_type hd;
	map_handle_type fm;
	void close_impl() noexcept
	{
#ifdef __cpp_exceptions
		try
		{
#endif
			fm.close();
			if(hd)
				truncate(hd,current_position);
#ifdef __cpp_exceptions
		}
		catch(...)
		{}
#endif
	}
public:
	std::size_t current_position{};
public:
	using char_type = char;//only char is allowed for punning
	template<typename ...Args>
	requires std::constructible_from<native_handle_type,Args...>
	basic_omap(Args&& ...args):hd(std::forward<Args>(args)...),fm(hd,fast_io::file_map_attribute::read_write,init_mem_size)
	{
	}
	auto& native_handle()
	{
		return hd;
	}
	auto& map_handle()
	{
		return fm;
	}
	basic_omap(basic_omap const&)=delete;
	basic_omap& operator=(basic_omap const&)=delete;
	basic_omap(basic_omap &&om) noexcept:hd(std::move(om.hd)),fm(std::move(om.fm)),current_position(om.current_position)
	{
		om.current_position={};
	}
	basic_omap& operator=(basic_omap&& om) noexcept
	{
		if(std::addressof(om)!=this)
		{
			close_impl();
			hd=std::move(om.hd);
			fm=std::move(om.fm);
			current_position=om.current_position;
		}
		return *this;
	}
	auto& region()
	{
		return fm.region();
	}
	~basic_omap()
	{
		close_impl();
	}
};


template<typename T,typename M>
inline std::size_t size(basic_omap<T,M>& om)
{
	return om.region().size();
}

template<typename T,typename M>
inline void reserve(basic_omap<T,M>& om,std::size_t trunc)
{
	om.map_handle()=M(om.native_handle(),fast_io::file_map_attribute::read_write,trunc);
	if(trunc<om.current_position)
		om.current_position=trunc;
}

namespace details
{
template<typename T,typename M>
inline void grow_omap(basic_omap<T,M>& om,std::size_t sz,std::size_t n)
{
	std::size_t const db(sz<<1);
	if(db<n)
		reserve(om,n);
	else
		reserve(om,db);
}
}

template<typename T,typename M,std::contiguous_iterator Iter>
inline void write(basic_omap<T,M>& om,Iter cbegin,Iter cend)
{
//http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2018/p1072r2.html
//strict aliasing rule
	std::size_t const bytes(sizeof(*cbegin)*(cend-cbegin));
	auto& region(om.region());
	std::size_t after(om.current_position+bytes);
	if(region.size()<=after)[[unlikely]]
	{
		details::grow_omap(om,region.size(),after);
		region=om.region();
	}
	memcpy(region.data()+om.current_position,std::to_address(cbegin),bytes);
	om.current_position=after;
}
template<typename T,typename M>
inline void flush(basic_omap<T,M>&){}

template<typename T,typename M>
inline void put(basic_omap<T,M>& om,typename basic_omap<T,M>::char_type ch)
{
	auto& region(om.region());
	if(region.size()==om.current_position)[[unlikely]]
		details::grow_omap(om,region.size(),region.size()+1);
	region[om.current_position]=static_cast<std::byte>(ch);
	++om.current_position;
}

template<typename T,typename M>
inline char unsigned* oreserve(basic_omap<T,M>& om,std::size_t n)
{
	if(om.region().size()<(om.current_position+=n))[[unlikely]]
	{
		details::grow_omap(om,om.region().size(),om.current_position);
		return static_cast<char unsigned*>(static_cast<void*>(om.region().data()+om.current_position));
	}
	return static_cast<char unsigned*>(static_cast<void*>(om.region().data()+om.current_position));
}

template<typename T,typename M>
inline auto orelease(basic_omap<T,M>& om,std::size_t n)
{
	om.current_position-=n;
}

}