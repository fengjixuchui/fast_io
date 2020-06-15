#pragma once

namespace fast_io
{


template<input_stream input,typename func,std::integral ch_type = typename input::char_type,std::size_t buffer_size=4096,bool randomaccess=false>
class itransform
{
public:
	using native_handle_type = input; 
	using transform_function_type = func;
	using char_type = ch_type;
	std::pair<native_handle_type,transform_function_type> handle;
	std::size_t position{},position_end{};
	std::array<char_type,buffer_size> buffer;
	auto& native_handle()
	{
		return handle.first;
	}
	auto& transform_function()
	{
		return handle.second;
	}
public:
	template<typename... Args>
	requires std::constructible_from<std::pair<native_handle_type,transform_function_type>,Args...>
	constexpr itransform(Args&& ...args):handle(std::forward<Args>(args)...){}
};


template<buffer_input_stream input,typename func,std::integral ch_type = typename input::char_type,std::size_t sz=4096,bool rac=false>
requires std::is_default_constructible_v<func>
class itransform_function_default_construct:public itransform<input,func,ch_type,sz,rac>
{
public:
	using native_handle_type = input; 
	using transform_function_type = func;
	using char_type = ch_type;
	template<typename... Args>
	requires std::constructible_from<native_handle_type,Args...>
	itransform_function_default_construct(Args&& ...args):itransform<input,func>(std::piecewise_construct,
				std::forward_as_tuple(std::forward<Args>(args)...),std::forward_as_tuple()){}
};

template<buffer_input_stream input,typename func,std::integral ch_type,std::size_t sz,bool rac,std::contiguous_iterator Iter>
inline constexpr auto read(itransform<input,func,ch_type,sz,rac>& ob,Iter cbegin,Iter cend)
{
	// empty ob first
	std::size_t remain_length(ob.position_end - ob.position);
	std::size_t available_length(cend - cbegin);
	if (remain_length < available_length)
		available_length = remain_length;
	cbegin = std::copy_n(ob.buffer.data() + ob.position, available_length, cbegin);
	//std::copy_n(ob.buffer.data() + ob.position + available_length, ob.position - available_length, ob.buffer.data());
	ob.position += available_length;

	// if buffer is empty now
	if (ob.position == ob.position_end)
	{
		auto read_pos(ob.handle.second.read_proxy(ob.handle.first, ob.buffer.data(), ob.buffer.data() + ob.buffer.size()));
		ob.position_end = read_pos - ob.buffer.data();
		ob.position = 0;
		remain_length = ob.position_end;
		available_length = cend - cbegin;
		if (remain_length < available_length)
			available_length = remain_length;
		cbegin = std::copy_n(ob.buffer.data(), available_length, cbegin);
		//std::copy_n(ob.buffer.data() + available_length, ob.position - available_length, ob.buffer.data());
		ob.position += available_length;
	}
	return cbegin;
}

template<output_stream input,typename func,std::integral ch_type,std::size_t sz,bool rac,std::contiguous_iterator Iter>
inline constexpr auto write(itransform<input,func,ch_type,sz,rac>& ob,Iter cbegini,Iter cendi)
{
	return write(ob.handle.first,cbegini,cendi);
}

template<output_stream input,typename func,std::integral ch_type,std::size_t sz,bool rac>
inline constexpr void flush(itransform<input,func,ch_type,sz,rac>&)
{
//	flush(ob.handle.first);
}

template<buffer_input_stream input,typename func,std::integral ch_type,std::size_t sz,bool rac>
inline constexpr auto ibuffer_begin(itransform<input,func,ch_type,sz,rac>& ib) noexcept
{
	return ib.buffer.data();
}

template<buffer_input_stream input,typename func,std::integral ch_type,std::size_t sz,bool rac>
inline constexpr auto ibuffer_curr(itransform<input,func,ch_type,sz,rac>& ib) noexcept
{
	return ib.buffer.data()+ib.position; 
}

template<buffer_input_stream input,typename func,std::integral ch_type,std::size_t sz,bool rac>
inline constexpr auto ibuffer_end(itransform<input,func,ch_type,sz,rac>& ib) noexcept
{
	return ib.buffer.data()+ib.position_end;
}

template<buffer_input_stream input,typename func,std::integral ch_type,std::size_t sz,bool rac>
inline constexpr void ibuffer_set_curr(itransform<input,func,ch_type,sz,rac>& ib,ch_type* ptr) noexcept
{
	ib.position=ptr-ib.buffer.data();
}

template<buffer_input_stream input,typename func,std::integral ch_type,std::size_t sz,bool rac>
inline constexpr bool underflow(itransform<input,func,ch_type,sz,rac>& ob)
{
	//itransform_underflow_impl
	ob.position_end = ob.handle.second.read_proxy(ob.handle.first, ob.buffer.data(), ob.buffer.data() + ob.buffer.size())-ob.buffer.data();
	ob.position=0;
	return ob.position_end;
}

template<buffer_output_stream input,typename func,std::integral ch_type,std::size_t sz,bool rac>
inline constexpr decltype(auto) obuffer_begin(itransform<input,func,ch_type,sz,rac>& ib)
{
	return obuffer_begin(ib.handle.first);
}

template<buffer_output_stream input,typename func,std::integral ch_type,std::size_t sz,bool rac>
inline constexpr decltype(auto) obuffer_curr(itransform<input,func,ch_type,sz,rac>& ib)
{
	return obuffer_curr(ib.handle.first);
}

template<buffer_output_stream input,typename func,std::integral ch_type,std::size_t sz,bool rac>
inline constexpr decltype(auto) obuffer_end(itransform<input,func,ch_type,sz,rac>& ib)
{
	return obuffer_end(ib.handle.first);
}

template<buffer_output_stream input,typename func,std::integral ch_type,std::size_t sz,bool rac,typename U>
inline constexpr void obuffer_set_curr(itransform<input,func,ch_type,sz,rac>& ib,U ptr)
{
	obuffer_set_curr(ib.handle.first,ptr);
}

template<buffer_output_stream input,typename func,std::integral ch_type,std::size_t sz,bool rac>
inline constexpr void overflow(itransform<input,func,ch_type,sz,rac>& ib,typename input::char_type ch)
{
	overflow(ib.handle.first,ch);
}

template<buffer_input_stream input,typename func,std::integral ch_type,std::size_t sz,bool rac,typename... Args>
requires (random_access_stream<input>&&rac)
inline constexpr auto seek(itransform<input,func,ch_type,sz,rac>& in,Args&& ...args)
{
	in.position=in.position_end={};
	return in.seek_proxy(in.handle.first,std::forward<Args>(args)...);
}

template<redirect_stream input,typename func,std::integral ch_type,std::size_t sz,bool rac>
inline constexpr decltype(auto) redirect_handle(itransform<input,func,ch_type,sz,rac>& t)
{
	return redirect_handle(t.native_handle());
}
}
