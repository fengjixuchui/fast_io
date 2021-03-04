#pragma once

namespace fast_io::ossl
{

enum class sha_type
{
sha1,sha224,sha256,sha384,sha512
};

template<std::size_t N>
class sha_final_result
{
public:
	using digest_type = std::array<unsigned char,N>;
	digest_type digest_block;
};

template<std::integral char_type,std::size_t N>
inline constexpr std::size_t print_reserve_size(io_reserve_type_t<char_type,sha_final_result<N>>)
{
	return N*2;
}

template<std::integral char_type,std::random_access_iterator caiter,std::size_t N>
inline constexpr caiter print_reserve_define(io_reserve_type_t<char_type,sha_final_result<N>>,caiter iter,auto const& i)
{
	for(auto e : i.digest_block)
	{
		fast_io::details::optimize_size::output_unsigned_dummy<2,16>(iter,e);
		iter+=2;
	}
	return iter;
}

template<sha_type ctx_type>
class sha_context
{
public:
	using char_type = char;
	using native_handle_type = std::conditional_t<ctx_type==sha_type::sha1,SHA_CTX,std::conditional_t<ctx_type==sha_type::sha224||ctx_type==sha_type::sha256,SHA256_CTX,SHA512_CTX>>;
	native_handle_type ctx;
	sha_context()
	{
		if constexpr(ctx_type==sha_type::sha1)
		{
			if(!SHA_Init(std::addressof(ctx)))
				throw_openssl_error();
		}
		else if constexpr(ctx_type==sha_type::sha224)
		{
			if(!SHA224_Init(std::addressof(ctx)))
				throw_openssl_error();
		}
		else if constexpr(ctx_type==sha_type::sha256)
		{
			if(!SHA256_Init(std::addressof(ctx)))
				throw_openssl_error();
		}
		else if constexpr(ctx_type==sha_type::sha384)
		{
			if(!SHA384_Init(std::addressof(ctx)))
				throw_openssl_error();
		}
		else if constexpr(ctx_type==sha_type::sha512)
		{
			if(!SHA512_Init(std::addressof(ctx)))
				throw_openssl_error();
		}
	}
	[[nodiscard]] auto do_final()
	{
		if constexpr(ctx_type==sha_type::sha1)
		{
			sha_final_result<SHA_DIGEST_LENGTH> ret; 
			if(!SHA_Final(ret.digest_block.data(),std::addressof(ctx)))
				throw_openssl_error();
			return ret;
		}
		else if constexpr(ctx_type==sha_type::sha224)
		{
			sha_final_result<SHA224_DIGEST_LENGTH> ret; 
			if(!SHA224_Final(ret.digest_block.data(),std::addressof(ctx)))
				throw_openssl_error();
			return ret;
		}
		else if constexpr(ctx_type==sha_type::sha256)
		{
			sha_final_result<SHA256_DIGEST_LENGTH> ret; 
			if(!SHA256_Final(ret.digest_block.data(),std::addressof(ctx)))
				throw_openssl_error();
			return ret;
		}
		else if constexpr(ctx_type==sha_type::sha384)
		{
			sha_final_result<SHA384_DIGEST_LENGTH> ret; 
			if(!SHA384_Final(ret.digest_block.data(),std::addressof(ctx)))
				throw_openssl_error();
			return ret;
		}
		else if constexpr(ctx_type==sha_type::sha512)
		{
			sha_final_result<SHA512_DIGEST_LENGTH> ret; 
			if(!SHA512_Final(ret.digest_block.data(),std::addressof(ctx)))
				throw_openssl_error();
			return ret;
		}
	}
};

template<sha_type ctx_type,std::contiguous_iterator Iter>
inline void write(sha_context<ctx_type>& ctx,Iter begin,Iter end)
{
	if constexpr(ctx_type==sha_type::sha1)
	{
		if(!SHA_Update(std::addressof(ctx.ctx),std::to_address(begin),(std::to_address(end)-std::to_address(begin))*sizeof(*begin)))
			throw_openssl_error();	
	}
	else if constexpr(ctx_type==sha_type::sha224)
	{
		if(!SHA224_Update(std::addressof(ctx.ctx),std::to_address(begin),(std::to_address(end)-std::to_address(begin))*sizeof(*begin)))
			throw_openssl_error();
	}
	else if constexpr(ctx_type==sha_type::sha256)
	{
		if(!SHA256_Update(std::addressof(ctx.ctx),std::to_address(begin),(std::to_address(end)-std::to_address(begin))*sizeof(*begin)))
			throw_openssl_error();
	}
	else if constexpr(ctx_type==sha_type::sha384)
	{
		if(!SHA384_Update(std::addressof(ctx.ctx),std::to_address(begin),(std::to_address(end)-std::to_address(begin))*sizeof(*begin)))
			throw_openssl_error();
	}
	else if constexpr(ctx_type==sha_type::sha512)
	{
		if(!SHA512_Update(std::addressof(ctx.ctx),std::to_address(begin),(std::to_address(end)-std::to_address(begin))*sizeof(*begin)))
			throw_openssl_error();
	}
}

template<sha_type ctx_type>
inline std::size_t scatter_write(sha_context<ctx_type>& ctx,io_scatters_t sp)
{
	std::size_t sz{};
	for(std::size_t i{};i!=sp.len;++i)
	{
		auto e{sp.base[i]};
		write(ctx,reinterpret_cast<char const*>(e.base),reinterpret_cast<char const*>(e.base)+e.len);
		sz+=e.len;
	}
	return sz;
}

using sha1=sha_context<sha_type::sha1>;
using sha224=sha_context<sha_type::sha224>;
using sha256=sha_context<sha_type::sha256>;
using sha384=sha_context<sha_type::sha384>;
using sha512=sha_context<sha_type::sha512>;

}