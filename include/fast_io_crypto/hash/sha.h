#pragma once
#include"sha1.h"
#include"sha256.h"
#include"sha512.h"
namespace fast_io
{
template<typename T,bool endian_reverse=true>
class sha
{
public:
	using function_type = T;
	using digest_type = typename T::digest_type;
	digest_type digest_block = T::digest_initial_value;
	inline static constexpr std::size_t block_size = T::block_size;
	T function;
	std::uint64_t transform_counter{};

	void operator()(std::span<std::byte const,block_size> process_block)
	{
		function(digest_block,process_block);
		++transform_counter;
	}

	void operator()(std::span<std::byte const> process_blocks)//This is multiple blocks
	{
		function(digest_block,process_blocks);
		transform_counter+=process_blocks.size()/block_size;
	}

	void digest(std::span<std::byte const> final_block)//contracts: final_block.size()<block_size
	{
		std::uint64_t total_bits(static_cast<std::uint64_t>(transform_counter*block_size+final_block.size())*8);
		std::array<std::byte,block_size> blocks{};
		memcpy(blocks.data(),final_block.data(),final_block.size());
		blocks[final_block.size()]=std::byte{0x80};
		auto start{blocks.data()+blocks.size()-8};
		if(block_size<=final_block.size()+8)
		{
			function(digest_block,std::span<std::byte const,block_size>{blocks});
			blocks.fill({});
		}
		if constexpr(endian_reverse)
		{
			total_bits=details::byte_swap(total_bits);
			std::uint32_t bu3(static_cast<std::uint32_t>(total_bits));
			memcpy(start,std::addressof(bu3),4);
			std::uint32_t bu4(static_cast<std::uint32_t>(total_bits>>32));
			memcpy(start+4,std::addressof(bu4),4);
		}
		else
			memcpy(start,std::addressof(total_bits),8);
		function(digest_block,std::span<std::byte const,block_size>{blocks});
	}
};

using sha1
[[deprecated("SHA1 is no longer a secure algorithm. See wikipedia https://en.wikipedia.org/wiki/SHA-1")]]
= sha<sha1_function>;

using sha256 = sha<sha256_function>;

using sha512 = sha<sha512_function>;
using md5
[[deprecated("The weaknesses of MD5 have been exploited in the field, most infamously by the Flame malware in 2012. See wikipedia https://en.wikipedia.org/wiki/MD5")]]
= sha<md5_function,false>;

template<typename T,bool endian_reverse>
inline constexpr std::size_t print_reserve_size(print_reserve_type_t<sha<T,endian_reverse>>)
{
	return sizeof(typename T::digest_type)*8;
}

template<std::random_access_iterator caiter,typename T,bool endian_reverse>
inline constexpr caiter print_reserve_define(print_reserve_type_t<sha<T,endian_reverse>>,caiter iter,auto& i)
{
	constexpr std::size_t offset{sizeof(typename T::digest_type::value_type)*2};
	for(auto e : i.digest_block)
	{
		if constexpr(!endian_reverse)
			e=details::byte_swap(e);
		fast_io::details::optimize_size::output_unsigned_dummy<offset,16>(iter,e);
		iter+=offset;
	}
	return iter;
}
}