#pragma once

namespace fast_io
{
template<typename func>
struct hmac
{
	using function_type = func;
	using key_type = std::array<std::byte,func::block_size>;
	function_type function;
	key_type inner_key;
	key_type outer_key{};
	inline static constexpr std::size_t block_size = function_type::block_size;
	hmac(std::span<std::byte const> init_key)
	{
		if(block_size<init_key.size())
		{
			function_type temp;
			{
				block_processor processor(temp);
				write(processor,reinterpret_cast<char const*>(init_key.data()),
					reinterpret_cast<char const*>(init_key.data()+init_key.size()));
			}
			if constexpr(std::endian::native==std::endian::little)
				for(auto & e : temp.digest_block)
					e=details::byte_swap(e);
			memcpy(outer_key.data(),temp.digest_block.data(),temp.digest_block.size());
		}
		else
			memcpy(outer_key.data(),init_key.data(),init_key.size());
		for(std::size_t i{};i!=inner_key.size();++i)
			inner_key[i]=outer_key[i]^std::byte{0x36};
	}
	hmac(std::string_view key):hmac(std::as_bytes(std::span{key.data(),key.size()})){}
	std::size_t block_init(std::span<std::byte,block_size> sp)
	{
		memcpy(sp.data(),inner_key.data(),sizeof(key_type));
		return sizeof(key_type);
	}
	void operator()(std::span<std::byte const,block_size> process_block)
	{
		function(process_block);
	}
	void digest(std::span<std::byte const> final_block)
	{
		function.digest(final_block);
		for(auto & e : outer_key)
			e^=std::byte{0x5c};
		auto digest_block{function.digest_block};
		if constexpr(std::endian::native==std::endian::little)
			for(auto& e : digest_block)
				e=details::byte_swap(e);
		function={};
		{
			block_processor processor(function);
			write(processor,reinterpret_cast<char const*>(outer_key.data()),
				reinterpret_cast<char const*>(outer_key.data()+outer_key.size()));
			write(processor,reinterpret_cast<char const*>(digest_block.data()),
				reinterpret_cast<char const*>(digest_block.data()+digest_block.size()));
		}
	}
};


template<reserve_printable T>
inline constexpr std::size_t print_reserve_size(print_reserve_type_t<hmac<T>>)
{
	return print_reserve_size(print_reserve_type<T>);
}

template<reserve_printable T,std::random_access_iterator caiter>
inline constexpr caiter print_reserve_define(print_reserve_type_t<hmac<T>>,caiter iter,auto& i)
{
	return print_reserve_define(print_reserve_type<T>,iter,i.function);
}

using hmac_sha1=hmac<sha1>;
}