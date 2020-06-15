#pragma once

namespace fast_io
{

enum class operating_system
{
	win32,
	posix,
#if defined(__WINNT__) || defined(_MSC_VER)
	native=win32,
#else
	native=posix
#endif
};

template<bool sys=false>
class binary_to_text
{
public:
template<buffer_output_stream output,std::contiguous_iterator Iter>
inline constexpr Iter write_proxy(output& out,Iter begin,Iter end)
{
	if constexpr(!sys||operating_system::native==operating_system::win32)
		for(auto iter(begin);iter!=end;++iter)
			if(*iter==u8'\n')
			{
				write(out,begin,iter);
				put(out,u8'\r');
				begin=iter;
			}
	write(out,begin,end);
	return end;
}
};

template<bool sys=false>
class text_to_binary
{
public:
template<character_input_stream input,std::contiguous_iterator Iter>
inline constexpr Iter read_proxy(input& inp,Iter ib,Iter ie)
{
	if constexpr(!sys||operating_system::native==operating_system::win32)
	{
		auto ig{igenerator(inp)};
		auto b{begin(ig)};
		auto e{end(ig)};
		for(;b!=e&&ib!=ie;++b)
		{
			if(*b==u8'\r')[[unlikely]]
			{
				if(++b==e)[[unlikely]]
				{
					*ib=u8'\r';
					return ++ib;
				}
				else if(*b==u8'\n')
					*ib=u8'\n';
				else
				{
					*ib=u8'\r';
					if(++ib==ie)[[unlikely]]
						return ie;
					*ib=*b;
				}
			}
			else
				*ib=*b;
			++ib;
		}
		return ib;
	}
	else
		return read(inp,ib,ie);
}
};

template<buffer_output_stream T,std::integral ch_type=typename T::char_type,std::size_t sz=4096>
using obinary_to_text=otransform_function_default_construct<T,binary_to_text<false>,ch_type,sz>;
template<buffer_output_stream T,std::integral ch_type=typename T::char_type,std::size_t sz=4096>
using obinary_to_native_text=otransform_function_default_construct<T,binary_to_text<true>,ch_type,sz>;

template<buffer_input_stream T,std::integral ch_type=typename T::char_type,std::size_t sz=4096>
using itext_to_binary=itransform_function_default_construct<T,text_to_binary<false>,ch_type,sz>;
template<buffer_input_stream T,std::integral ch_type=typename T::char_type,std::size_t sz=4096>
using inative_text_to_binary=itransform_function_default_construct<T,text_to_binary<true>,ch_type,sz>;
}
