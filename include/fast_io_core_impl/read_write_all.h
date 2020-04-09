#pragma once

namespace fast_io
{

template<bool report_eof=false,input_stream input,std::input_iterator Iter>
inline constexpr std::conditional_t<report_eof,bool,void> read_all(input& inp,Iter begin,Iter end)
{
	for(Iter iter{begin};(iter = read(inp,begin,end))!=end;begin = iter)
		if(iter==begin)[[unlikely]]
		{
			if constexpr(report_eof)
				return false;
			else
#ifdef __cpp_exceptions
				throw fast_io::eof();
#else
				fast_terminate();
#endif
		}
	if constexpr(report_eof)
		return true;
}

template<output_stream output,std::input_iterator Iter>
inline constexpr void write_all(output& outp,Iter begin,Iter end)
{
	if constexpr(std::same_as<decltype(write(outp,begin,end)),void>)
	{
		write(outp,begin,end);
	}
	else
		for(Iter iter{begin};(iter = write(outp,begin,end))!=end;begin=iter);
}

}