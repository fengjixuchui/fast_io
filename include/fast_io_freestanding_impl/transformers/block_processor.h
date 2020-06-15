#pragma once

namespace fast_io
{

template<std::integral ch_type,typename Func>
class basic_block_processor
{
public:
	using char_type = ch_type;
	using function_type = Func;
	function_type& function;
	inline static constexpr std::size_t block_size = function_type::block_size;
	std::array<std::byte,block_size> temporary_buffer{};
	std::size_t current_position{};
	basic_block_processor(function_type& func):function(func)
	{
		if constexpr(requires(Func& func)
		{
			func.block_init(temporary_buffer);
		})
			current_position+=func.block_init(temporary_buffer);
	}
	basic_block_processor(basic_block_processor const&)=delete;
	basic_block_processor& operator=(basic_block_processor const&)=delete;
	~basic_block_processor()
	{
		function.digest(std::as_bytes(std::span<std::byte const>{temporary_buffer.data(),current_position}));
	}
};

namespace details::block_processor
{

template<std::integral ch_type,typename Func,std::contiguous_iterator Iter>
requires (std::same_as<std::iter_value_t<Iter>,ch_type>||std::same_as<ch_type,char>)
inline constexpr void write_cold_path(basic_block_processor<ch_type,Func>& out,Iter begin,Iter end)
{
	out.function(std::as_bytes(std::span{out.temporary_buffer}));
	for(;begin+Func::block_size<=end;begin+=Func::block_size)
		out.function(std::as_bytes(std::span<char const,Func::block_size>{std::to_address(begin),Func::block_size}));
	std::size_t const to_copy(end-begin);
	memcpy(out.temporary_buffer.data(),std::to_address(begin),to_copy);
	out.current_position=to_copy;
}

}

template<std::integral ch_type,typename Func,std::contiguous_iterator Iter>
requires (std::same_as<std::iter_value_t<Iter>,ch_type>||std::same_as<ch_type,char>)
inline void write(basic_block_processor<ch_type,Func>& out,Iter begin,Iter end)
{
	if(std::same_as<std::iter_value_t<Iter>,char>)
	{
		std::size_t const bytes(end-begin);
		std::size_t to_copy{Func::block_size-out.current_position};
		if(bytes<to_copy)[[likely]]
		{
			to_copy=bytes;
			memcpy(out.temporary_buffer.data()+out.current_position,std::to_address(begin),to_copy);
			out.current_position+=to_copy;
			return;
		}
		memcpy(out.temporary_buffer.data()+out.current_position,std::to_address(begin),to_copy);
		details::block_processor::write_cold_path(out,begin+to_copy,end);
	}
	else
		write(out,reinterpret_cast<char const*>(std::to_address(begin)),reinterpret_cast<char const*>(std::to_address(end)));
}
template<typename Func>
class block_processor:public basic_block_processor<char,Func>
{
public:
	using basic_block_processor<char,Func>::char_type;
	using basic_block_processor<char,Func>::function_type;
	using basic_block_processor<char,Func>::block_size;
	constexpr block_processor(Func& func):basic_block_processor<char,Func>(func){}
};

template<typename Func>
block_processor(Func& func)->block_processor<Func>;

}