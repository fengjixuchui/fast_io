#pragma once

namespace fast_io
{

#ifdef __SSE4_2__
class crc32c
{
public:
	static inline constexpr std::size_t block_size = 8;
	std::uint32_t crc{0xffffffff};
	void operator()(std::span<std::byte const,block_size> process_block)
	{
		std::uint64_t v;
		memcpy(std::addressof(v),process_block.data(),block_size);
		crc = _mm_crc32_u64(crc,v);
	}
	void operator()(std::span<std::byte const> blocks)
	{
		for(auto block(blocks.data()),ed(blocks.data()+blocks.size());block!=ed;block+=block_size)
		{
			std::uint64_t v;
			memcpy(std::addressof(v),block,block_size);
			crc = _mm_crc32_u64(crc,v);
		}
	}
	void digest(std::span<std::byte const> final_block)//contracts: final_block.size()<8
	{
		switch(final_block.size())
		{
		case 7:
		{
			std::uint32_t fn;
			memcpy(std::addressof(fn),final_block.data(),4);
			crc = _mm_crc32_u32(crc,fn);
			std::uint16_t fn1;
			memcpy(std::addressof(fn1),final_block.data()+4,2);
			crc = _mm_crc32_u32(crc,fn1);
			crc = _mm_crc32_u8(crc,std::to_integer<char unsigned>(final_block[6]));
			break;
		}
		case 6:
		{
			std::uint32_t fn;
			memcpy(std::addressof(fn),final_block.data(),4);
			crc = _mm_crc32_u32(crc,fn);
			std::uint16_t fn1;
			memcpy(std::addressof(fn1),final_block.data()+4,2);
			crc = _mm_crc32_u32(crc,fn1);
			break;
		}
		case 5:
		{
			std::uint32_t fn;
			memcpy(std::addressof(fn),final_block.data(),4);
			crc = _mm_crc32_u32(crc,fn);
			crc = _mm_crc32_u8(crc,std::to_integer<char unsigned>(final_block[4]));
			break;
		}
		case 4:
		{
			std::uint32_t fn;
			memcpy(std::addressof(fn),final_block.data(),4);
			crc = _mm_crc32_u32(crc,fn);
			break;
		}
		case 3:
		{
			std::uint16_t fn;
			memcpy(std::addressof(fn),final_block.data(),2);
			crc = _mm_crc32_u16(crc,fn);
			crc = _mm_crc32_u8(crc,std::to_integer<char unsigned>(final_block[2]));
			break;
		}
		case 2:
		{
			std::uint16_t fn;
			memcpy(std::addressof(fn),final_block.data(),2);
			crc = _mm_crc32_u16(crc,fn);
			break;
		}
		case 1:
			crc = _mm_crc32_u8(crc,std::to_integer<char unsigned>(final_block.front()));
		break;
		};
		crc = ~crc;
	}
};

inline constexpr std::size_t print_reserve_size(print_reserve_type_t<crc32c>)
{
	return 8;
}

template<std::random_access_iterator caiter>
inline constexpr caiter print_reserve_define(print_reserve_type_t<crc32c>,caiter iter,auto i)
{
	fast_io::details::optimize_size::output_unsigned_dummy<8,16>(iter,i.crc);
	return iter+8;
}
#endif

}