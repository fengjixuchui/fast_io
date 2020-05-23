#pragma once

namespace fast_io
{

template<typename Func>
class block_processor
{
public:
	using function_type = Func;
	function_type function;
	inline static constexpr std::size_t block_size = function_type::block_size;

	template<typename ...Args>
	requires std::constructible_from<function_type, Args...>
	block_processor(Args&&... args):function(std::forward<Args>(args)...){}

	template<output_stream output, std::contiguous_iterator Iter>
	requires (sizeof(typename output::char_type)==1)
	Iter write_proxy(output& out,Iter b, Iter e)
	{
		std::span be(std::as_writable_bytes(std::span<char>(std::to_address(b),std::to_address(e))));
		auto b_s(be.data());
		for(;block_size<=be.size();)
		{
			function(std::span<std::byte,block_size>(be.data(),block_size));
			be=be.subspan(block_size);
		}
		write(out,b_s,be.data());
		return e - be.size() / sizeof(*b);
	}
	template<output_stream output, std::contiguous_iterator Iter>
	requires (sizeof(typename output::char_type)==1)
	void flush_proxy(output& out,Iter begin, Iter end)
		requires requires()
		{
			function.digest(std::span<std::byte const>{});
		}
	{
		begin = write_proxy(out, begin, end);
		std::span be(std::as_bytes(std::span<char const>(std::to_address(begin),std::to_address(end))));
		if constexpr(requires()
		{
			{function.digest(be)}->std::same_as<void>;
		})
			function.digest(be);
		else
		{
			auto ret(function.digest(be));
			write(out,ret);
		}
	}
	template<buffer_input_stream input, std::contiguous_iterator Iter>
	requires (sizeof(typename input::char_type)==1)
	Iter read_proxy(input& in,Iter b, Iter e)
	{
		auto be(std::as_writable_bytes(std::span<std::remove_reference_t<decltype(*b)>>(b, e)));
		for(;block_size<=be.size();in += block_size)
		{
			if (!ireserve(in, block_size))
				break;
			std::span<std::byte, block_size> s(reinterpret_cast<std::byte*>(std::to_address(begin(in))), block_size);
			function(s);
			details::my_copy_n(s.data(), block_size, be.data());
			be = be.subspan(block_size);
		}
		return e - be.size() / sizeof(*b);
	}
};

}