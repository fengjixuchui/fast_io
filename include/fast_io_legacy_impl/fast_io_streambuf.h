#pragma once

namespace fast_io
{

namespace details
{

template<buffer_output_stream output>
inline constexpr void call_overflow(output& out,typename output::char_type ch)
{
	overflow(out,ch);
}

}

template<stream stm,typename traits_tp = std::char_traits<typename stm::char_type>>
class fast_io_basic_streambuf final:public std::basic_streambuf<typename traits_tp::char_type,traits_tp>
{
public:
	using native_handle_type = stm;
	using traits_type = traits_tp;
	using char_type = typename traits_type::char_type;
private:
	native_handle_type sm;
	std::streamsize xsputn(char_type const* s, std::streamsize count) override
	{
		write_all(sm,s,s+count);
		return count;
	}
	typename traits_type::int_type overflow(typename traits_type::int_type ch) override
	{
		if constexpr(fast_io::buffer_output_stream<native_handle_type>)
		{
			auto i{obuffer_curr(sm)};
			if(i+1<=obuffer_end(sm))[[likely]]
			{
				*i=traits_type::to_char_type(ch);
				obuffer_set_curr(sm,i+1);
				return 0;
			}
			else
			{
//			else
				try
				{
					details::call_overflow(sm,traits_type::to_char_type(ch));
					return 0;
				}
				catch(...)
				{
					return traits_type::eof();
				}
			}
			
		}
		else
		{
			try
			{
				write(sm,std::addressof(ch),std::addressof(ch)+1);
				return 0;
			}
			catch(...)
			{
				return traits_type::eof();
			}
		}
	}
public:
	template<typename... Args>
	requires std::constructible_from<stm,Args...>
	fast_io_basic_streambuf(Args&& ...args):sm(std::forward<Args>(args)...){}
	constexpr auto& native_handle()
	{
		return sm;
	}
};

}