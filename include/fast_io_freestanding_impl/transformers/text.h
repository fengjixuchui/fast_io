#pragma once

namespace fast_io
{

namespace transforms
{

enum class eol
{
lf,
crlf,
#if defined(__WINNT__) || defined(_MSC_VER)
native=crlf,
#else
native=lf
#endif
};

template<eol el=eol::native>
struct text_to_binary
{
	template<output_stream opstm,std::contiguous_iterator Iter>
	requires std::same_as<typename opstm::char_type,std::iter_value_t<Iter>>
	constexpr auto operator()(opstm& obuf,Iter begin,Iter end)
	{
		if constexpr(el==eol::crlf)
		{
			reserve_write(obuf,(end-begin),[&](auto ptr)
			{
				for(;begin!=end;++begin)
				{
					if(*begin==u8'\r')
					{
						if(begin+1==end)[[unlikely]]
							break;
						else if(begin[1]==u8'\n')[[likely]]
							++begin;
					}
					*ptr=*begin;
					++ptr;
				}
				return ptr;
			});
			return begin;
		}
		else
			write(obuf,begin,end);
	}
};

template<eol el=eol::native>
struct binary_to_text
{
	template<output_stream opstm,std::contiguous_iterator Iter>
	requires std::same_as<typename opstm::char_type,std::iter_value_t<Iter>>
	constexpr void operator()(opstm& obuf,Iter begin,Iter end)
	{
		if constexpr(el==eol::crlf)
		{
			reserve_write(obuf,(end-begin)<<1,[&](auto ptr)
			{
				for(;begin!=end;++begin)
				{
					if(*begin==u8'\n')[[unlikely]]
					{
						if constexpr(sizeof(std::iter_value_t<Iter>)==1)
							memcpy(ptr,u8"\r\n",2);
						else
						{
							*ptr=u8'\r';
							ptr[1]=u8'\n';
						}
						ptr+=2;
						continue;
					}
					*ptr=*begin;
					++ptr;
				}
				return ptr;
			});
		}
		else
			write(obuf,begin,end);
	}
};

}

}