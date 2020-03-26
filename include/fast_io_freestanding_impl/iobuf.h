#pragma once

namespace fast_io
{

template<typename T,std::size_t alignment=4096>
struct io_aligned_allocator
{
	using value_type = T;
	using size_type = std::size_t;
	using difference_type = std::ptrdiff_t;
	[[nodiscard]] inline T* allocate(std::size_t n)
	{
		return static_cast<T*>(operator new(n*sizeof(T),std::align_val_t{alignment}));
	}
	inline void deallocate(T* p, std::size_t n) noexcept
	{
		operator delete(p,n*sizeof(T),std::align_val_t{alignment});
	}
};

template<std::integral CharT,std::size_t buffer_size = ((
#if defined(__WINNT__) || defined(_MSC_VER)
1048576
#else
65536
#endif
<sizeof(CharT))?1:
#if defined(__WINNT__) || defined(_MSC_VER)
1048576
#else
65536
#endif
/sizeof(CharT)),typename Allocator = io_aligned_allocator<CharT>>
class basic_buf_handler
{
	Allocator alloc;
public:
	using char_type = CharT;
	using allocator_type = Allocator;
	char_type *beg{},*curr{},*end{};
	basic_buf_handler()=default;
	basic_buf_handler& operator=(basic_buf_handler const&)=delete;
	basic_buf_handler(basic_buf_handler const&)=delete;
	static constexpr std::size_t size = buffer_size;
	basic_buf_handler(basic_buf_handler&& m) noexcept:beg(m.beg),curr(m.curr),end(m.end)
	{
		m.end=m.curr=m.beg=nullptr;
	}
	basic_buf_handler& operator=(basic_buf_handler&& m) noexcept
	{
		if(std::addressof(m)!=this)[[likely]]
		{
			if(m.beg)
				alloc.deallocate(beg,buffer_size);
			beg=m.beg;
			curr=m.curr;
			end=m.end;
			m.end=m.curr=m.beg=nullptr;
		}
		return *this;
	}
	inline void init_space()
	{
		end=curr=beg=alloc.allocate(buffer_size);
	}
	inline void release()
	{
		if(beg)[[likely]]
			alloc.deallocate(beg,buffer_size);
		end=curr=beg=nullptr;
	}
	~basic_buf_handler()
	{
		if(beg)[[likely]]
			alloc.deallocate(beg,buffer_size);
	}
	Allocator get_allocator() const{ return alloc;}
};


template<input_stream Ihandler,typename Buf=basic_buf_handler<typename Ihandler::char_type>>
class basic_ibuf
{
public:
	Ihandler ih;
	Buf ibuffer;

	using native_handle_type = Ihandler;
	using buffer_type = Buf;
	using char_type = typename Buf::char_type;
	template<typename... Args>
	requires std::constructible_from<Ihandler,Args...>
	basic_ibuf(Args&&... args):ih(std::forward<Args>(args)...){}
	inline constexpr auto& native_handle()
	{
		return ih;
	}
};
template<input_stream Ihandler,typename Buf>
[[nodiscard]] inline constexpr bool underflow(basic_ibuf<Ihandler,Buf>& ib)
{
	if(ib.ibuffer.end==nullptr)
		ib.ibuffer.init_space();
	ib.ibuffer.end=read(ib.ih,ib.ibuffer.beg,ib.ibuffer.beg+Buf::size);
	ib.ibuffer.curr=ib.ibuffer.beg;
	return ib.ibuffer.end!=ib.ibuffer.beg;
}

template<input_stream Ihandler,typename Buf>
[[nodiscard]] inline constexpr auto ibuffer_begin(basic_ibuf<Ihandler,Buf>& ib)
{
	return ib.ibuffer.beg;
}
template<input_stream Ihandler,typename Buf>
[[nodiscard]] inline constexpr auto ibuffer_curr(basic_ibuf<Ihandler,Buf>& ib)
{
	return ib.ibuffer.curr;
}
template<input_stream Ihandler,typename Buf>
[[nodiscard]] inline constexpr auto ibuffer_end(basic_ibuf<Ihandler,Buf>& ib)
{
	return ib.ibuffer.end;
}

template<input_stream Ihandler,typename Buf>
inline constexpr void ibuffer_set_curr(basic_ibuf<Ihandler,Buf>& ib,typename Ihandler::char_type* ptr)
{
	ib.ibuffer.curr=ptr;
}


template<buffer_output_stream Ihandler,typename Buf>
inline constexpr decltype(auto) overflow(basic_ibuf<Ihandler,Buf>& ib,typename Ihandler::char_type ch)
{
	return overflow(ib.oh,ch);
}

template<buffer_output_stream Ihandler,typename Buf>
[[nodiscard]] inline constexpr decltype(auto) obuffer_begin(basic_ibuf<Ihandler,Buf>& ib)
{
	return obuffer_begin(ib.oh);
}

template<buffer_output_stream Ihandler,typename Buf>
[[nodiscard]] inline constexpr decltype(auto) obuffer_curr(basic_ibuf<Ihandler,Buf>& ib)
{
	return obuffer_curr(ib.oh);
}
template<buffer_output_stream Ihandler,typename Buf>
[[nodiscard]] inline constexpr decltype(auto) obuffer_end(basic_ibuf<Ihandler,Buf>& ib)
{
	return obuffer_end(ib.oh);
}

template<buffer_output_stream Ihandler,typename Buf>
[[nodiscard]] inline constexpr decltype(auto) obuffer_set_curr(basic_ibuf<Ihandler,Buf>& ib,typename Ihandler::char_type* ptr)
{
	return obuffer_set_curr(ib.oh,ptr);
}

template<output_stream Ihandler,typename Buf>
inline constexpr void flush(basic_ibuf<Ihandler,Buf>& ib)
{
	flush(ib.native_handle());
}

template<output_stream Ihandler,typename Buf,std::contiguous_iterator Iter>
inline constexpr decltype(auto) write(basic_ibuf<Ihandler,Buf>& ib,Iter b,Iter e)
{
	return write(ib.native_handle(),b,e);
}

template<redirect_stream Ihandler,typename Buf>
inline constexpr decltype(auto) redirect_handle(basic_ibuf<Ihandler,Buf>& ib)
{
	return redirect_handle(ib.native_handle());
}

template<typename T,typename Iter>
concept write_read_punned_constraints = (std::contiguous_iterator<Iter>&&sizeof(typename T::char_type)==1) ||
	(std::random_access_iterator<Iter>&&std::same_as<typename T::char_type,typename std::iterator_traits<Iter>::value_type>);

namespace details
{
template<std::size_t buffer_size,bool punning=false,typename T,typename Iter>
inline constexpr Iter ibuf_read(T& ib,Iter begin,Iter end)
{
	std::size_t const buffer_remain(ib.ibuffer.end-ib.ibuffer.curr);

	std::size_t n(end-begin);
	if(buffer_remain<n)			//cache miss
	{
		if(ib.ibuffer.end==nullptr)
		{
			if(buffer_size<=n)
			{
				return read(ib.native_handle(),begin,end);
			}
			ib.ibuffer.init_space();
			ib.ibuffer.curr=ib.ibuffer.end=ib.ibuffer.beg;
		}
		if constexpr(punning)
		{
			std::memcpy(begin,ib.ibuffer.curr,buffer_remain);
			begin+=buffer_remain;
		}
		else
			begin=std::copy_n(ib.ibuffer.curr,buffer_remain,begin);
		if(begin+buffer_size<end)
		{
//			if constexpr(std::contiguous_iterator<Iter>)
				begin=read(ib.native_handle(),begin,end);
/*			else
			{
				
			}*/
			if(begin!=end)
			{
				ib.ibuffer.end=ib.ibuffer.curr=ib.ibuffer.beg;
				return begin;
			}
		}
		ib.ibuffer.end=read(ib.native_handle(),ib.ibuffer.beg,ib.ibuffer.beg+buffer_size);
		ib.ibuffer.curr=ib.ibuffer.beg;
		n=end-begin;
		std::size_t const sz(ib.ibuffer.end-ib.ibuffer.beg);
		if(sz<n)
			n=sz;
	}
	if constexpr(punning)
	{
		std::memcpy(begin,ib.ibuffer.curr,n);
		begin+=n;
	}
	else
		begin=std::copy_n(ib.ibuffer.curr,n,begin);
	ib.ibuffer.curr+=n;
	return begin;
}
}

template<input_stream Ihandler,typename Buf,std::contiguous_iterator Iter>
requires (write_read_punned_constraints<basic_ibuf<Ihandler,Buf>,Iter>)
inline constexpr Iter read(basic_ibuf<Ihandler,Buf>& ib,Iter begin,Iter end)
{
	using char_type = typename basic_ibuf<Ihandler,Buf>::char_type;
	if constexpr(std::same_as<char_type,typename std::iterator_traits<Iter>::value_type>)
		return details::ibuf_read<Buf::size>(ib,begin,end);
	else
	{
		auto b(reinterpret_cast<char const*>(std::to_address(begin)));
		return begin+(details::ibuf_read<Buf::size,true>(ib,b,reinterpret_cast<char const*>(std::to_address(end)))-b)/sizeof(*begin);
	}
}

template<input_stream Ihandler,std::integral ch_type,typename Buf>
requires random_access_stream<Ihandler>
inline constexpr auto seek(basic_ibuf<Ihandler,Buf>& ib,seek_type_t<ch_type>,std::intmax_t u=0,seekdir s=seekdir::cur)
{
	std::intmax_t val(u-(ib.end-ib.curr));
	ib.ibuffer.curr=ib.ibuffer.end;
	return seek(ib.native_handle(),seek_type<ch_type>,val,s);
}

template<input_stream Ihandler,typename Buf>
requires random_access_stream<Ihandler>
inline constexpr auto seek(basic_ibuf<Ihandler,Buf>& ib,std::intmax_t u=0,seekdir s=seekdir::cur)
{
	return seek(ib,seek_type<typename basic_ibuf<Ihandler,Buf>::char_type>,u,s);
}

template<zero_copy_input_stream Ihandler,typename Buf>
inline constexpr decltype(auto) zero_copy_in_handle(basic_ibuf<Ihandler,Buf>& ib)
{
	return zero_copy_in_handle(ib.native_handle());
}

template<zero_copy_output_stream Ohandler,typename Buf>
inline constexpr decltype(auto) zero_copy_out_handle(basic_ibuf<Ohandler,Buf>& ib)
{
	return zero_copy_out_handle(ib.native_handle());
}

template<memory_map_input_stream Ihandler,typename Buf>
inline constexpr decltype(auto) memory_map_in_handle(basic_ibuf<Ihandler,Buf>& handle)
{
	return memory_map_in_handle(handle.native_handle());
}

template<output_stream Ohandler,typename Buf=basic_buf_handler<typename Ohandler::char_type>>
class basic_obuf
{
public:
	Ohandler oh;
	Buf obuffer;
	inline constexpr void close_impl() noexcept
	{
#ifdef __cpp_exceptions
		try
		{
#endif
			if(obuffer.beg)
				write(oh,obuffer.beg,obuffer.curr);
#ifdef __cpp_exceptions
		}
		catch(...){}
#endif
	}
public:
	using native_handle_type = Ohandler;
	using buffer_type = Buf;
	using char_type = typename Buf::char_type;
	template<typename... Args>
	requires std::constructible_from<Ohandler,Args...>
	basic_obuf(Args&&... args):oh(std::forward<Args>(args)...){}
	~basic_obuf()
	{
		close_impl();
	}
	basic_obuf& operator=(basic_obuf const&)=delete;
	basic_obuf(basic_obuf const&)=delete;
	basic_obuf(basic_obuf&& bmv) noexcept:oh(std::move(bmv.oh)),obuffer(std::move(bmv.obuffer)){}
	basic_obuf& operator=(basic_obuf&& b) noexcept
	{
		if(std::addressof(b)!=this)
		{
			close_impl();
			oh=std::move(b.oh);
			obuffer=std::move(b.obuffer);
		}
		return *this;
	}
	inline constexpr auto& native_handle()
	{
		return oh;
	}
};

template<output_stream Ohandler,typename Buf>
[[nodiscard]] inline constexpr auto obuffer_begin(basic_obuf<Ohandler,Buf>& ob)
{
	return ob.obuffer.beg;
}

template<output_stream Ohandler,typename Buf>
[[nodiscard]] inline constexpr auto& obuffer_curr(basic_obuf<Ohandler,Buf>& ob)
{
	return ob.obuffer.curr;
}

template<output_stream Ohandler,typename Buf>
[[nodiscard]] inline constexpr auto obuffer_end(basic_obuf<Ohandler,Buf>& ob)
{
	return ob.obuffer.end;
}

template<output_stream Ohandler,typename Buf>
inline constexpr void obuffer_set_curr(basic_obuf<Ohandler,Buf>& ob,typename Ohandler::char_type* ptr)
{
	ob.obuffer.curr=ptr;
}

template<output_stream Ohandler,typename Buf>
inline constexpr void overflow(basic_obuf<Ohandler,Buf>& ob,typename Ohandler::char_type ch)
{
	if(ob.obuffer.beg)	//cold buffer
		write(ob.native_handle(),ob.obuffer.beg,ob.obuffer.end);
	else
	{
		ob.obuffer.init_space();
		ob.obuffer.end=ob.obuffer.beg+Buf::size;
	}
	*(ob.obuffer.curr=ob.obuffer.beg)=ch;
	++ob.obuffer.curr;
}

template<buffer_input_stream Ohandler,typename Buf>
[[nodiscard]] inline constexpr decltype(auto) underflow(basic_obuf<Ohandler,Buf>& ob)
{
	return underflow(ob.oh);
}

template<buffer_input_stream Ohandler,typename Buf>
[[nodiscard]] inline constexpr decltype(auto) ibuffer_begin(basic_obuf<Ohandler,Buf>& ob)
{
	return ibuffer_begin(ob.oh);
}

template<buffer_input_stream Ohandler,typename Buf>
[[nodiscard]] inline constexpr decltype(auto) ibuffer_curr(basic_obuf<Ohandler,Buf>& ob)
{
	return ibuffer_curr(ob.oh);
}

template<buffer_input_stream Ohandler,typename Buf>
[[nodiscard]] inline constexpr decltype(auto) ibuffer_end(basic_obuf<Ohandler,Buf>& ob)
{
	return ibuffer_end(ob.oh);
}

template<buffer_input_stream Ohandler,typename Buf>
inline constexpr decltype(auto) ibuffer_set_curr(basic_obuf<Ohandler,Buf>& ob,typename Ohandler::char_type* ptr)
{
	return ibuffer_set_curr(ob.oh,ptr);
}

namespace details
{

template<bool punning=false,typename T,typename Iter>
inline constexpr void obuf_write(T& ob,Iter cbegin,Iter cend)
{
	std::size_t const n(ob.obuffer.end-ob.obuffer.curr);
	std::size_t const diff(std::distance(cbegin,cend));
	if(n<diff)[[unlikely]]
	{
		if(ob.obuffer.end==nullptr)		//cold buffer
		{
			if(T::buffer_type::size<=diff)
			{
				write(ob.native_handle(),cbegin,cend);
				return;
			}
			ob.obuffer.init_space();
			ob.obuffer.end=(ob.obuffer.curr=ob.obuffer.beg)+T::buffer_type::size;
			if constexpr(punning)
				std::memcpy(ob.obuffer.curr,cbegin,diff);
			else
				std::copy_n(cbegin,diff,ob.obuffer.curr);
			ob.obuffer.curr+=diff;
			return;
		}
/*		if constexpr(punning)
			std::memcpy(ob.obuffer.curr,cbegin,n);
		else*/
			std::copy_n(cbegin,n,ob.obuffer.curr);		
		cbegin+=n;
		write(ob.native_handle(),ob.obuffer.beg,ob.obuffer.end);
		if(cbegin+(T::buffer_type::size)<cend)
		{
			write(ob.native_handle(),cbegin,cend);
			ob.obuffer.curr=ob.obuffer.beg;
		}
		else
		{
			std::size_t const df(cend-cbegin);
			if constexpr(punning)
				std::memcpy(ob.obuffer.beg,cbegin,df);
			else
				std::copy_n(cbegin,df,ob.obuffer.beg);
			ob.obuffer.curr=ob.obuffer.beg+df;
		}
		return;
	}
	if constexpr(punning)
		std::memcpy(ob.obuffer.curr,cbegin,diff);
	else
		std::copy_n(cbegin,diff,ob.obuffer.curr);
	ob.obuffer.curr+=diff;
}

}

template<output_stream Ohandler,typename Buf,std::contiguous_iterator Iter>
requires (write_read_punned_constraints<basic_obuf<Ohandler,Buf>,Iter>)
inline constexpr void write(basic_obuf<Ohandler,Buf>& ob,Iter cbegini,Iter cendi)
{
	using char_type = typename basic_obuf<Ohandler,Buf>::char_type;
	if constexpr(std::same_as<char_type,typename std::iterator_traits<Iter>::value_type>)
		details::obuf_write<false>(ob,std::to_address(cbegini),std::to_address(cendi));
	else
		details::obuf_write<true>(ob,reinterpret_cast<char const*>(std::to_address(cbegini)),
					reinterpret_cast<char const*>(std::to_address(cendi)));
}

template<output_stream Ohandler,typename Buf>
inline constexpr void flush(basic_obuf<Ohandler,Buf>& ob)
{
	if(ob.obuffer.beg==ob.obuffer.curr)
		return;
	write(ob.native_handle(),ob.obuffer.beg,ob.obuffer.curr);
	ob.obuffer.curr=ob.obuffer.beg;
//	flush(oh.native_handle());
}

template<output_stream Ohandler,typename Buf,typename... Args>
requires random_access_stream<Ohandler>
inline constexpr decltype(auto) seek(basic_obuf<Ohandler,Buf>& ob,Args&& ...args)
{
	if(ob.obuffer.beg!=ob.obuffer.curr)
	{
		write(ob.native_handle(),ob.obuffer.beg,ob.obuffer.curr);
		ob.obuffer.curr=ob.obuffer.beg;
	}
	return seek(ob.native_handle(),std::forward<Args>(args)...);
}

template<input_stream Ohandler,typename Buf,std::contiguous_iterator Iter>
inline constexpr decltype(auto) read(basic_obuf<Ohandler,Buf>& ob,Iter begin,Iter end)
{
	return read(ob.native_handle(),begin,end);
}

template<zero_copy_output_stream Ohandler,typename Buf>
inline constexpr decltype(auto) zero_copy_out_handle(basic_obuf<Ohandler,Buf>& ob)
{
	return zero_copy_out_handle(ob.native_handle());
}

template<zero_copy_input_stream Ohandler,typename Buf>
inline constexpr decltype(auto) zero_copy_in_handle(basic_obuf<Ohandler,Buf>& ob)
{
	return zero_copy_in_handle(ob.native_handle());
}

template<redirect_stream Ohandler,typename Buf>
inline constexpr decltype(auto) redirect_handle(basic_obuf<Ohandler,Buf>& ob)
{
	return redirect_handle(ob.native_handle());
}

template<memory_map_input_stream Ihandler,typename Buf>
inline constexpr decltype(auto) memory_map_in_handle(basic_obuf<Ihandler,Buf>& handle)
{
	return memory_map_in_handle(handle.native_handle());
}

template<io_stream ioh,typename bf=basic_buf_handler<typename ioh::char_type>>
using basic_iobuf=basic_obuf<basic_ibuf<ioh,bf>,bf>;

}