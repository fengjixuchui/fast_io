#pragma once
#include<variant>

namespace fast_io
{

struct ipv4
{
	std::array<unsigned char, 4> storage{};
};


namespace details
{
template<character_input_stream input>
inline constexpr void ipv4_scan_sep(input& in)
{
	auto ig{igenerator(in)};
	auto bg{begin(ig)},ed{end(ig)};
	if(bg==ed||*bg!=u8'.')
#ifdef __cpp_exceptions
		throw posix_error(EIO);
#else
		fast_terminate();
#endif
	++bg;
}
}

template<character_input_stream input>
inline constexpr void space_scan_define(input& in,ipv4& v4)
{
	space_scan_define(in,v4.storage[0]);
	details::ipv4_scan_sep(in);
	space_scan_define(in,v4.storage[1]);
	details::ipv4_scan_sep(in);
	space_scan_define(in,v4.storage[2]);
	details::ipv4_scan_sep(in);
	space_scan_define(in,v4.storage[3]);
}

inline constexpr std::size_t native_socket_address_size(ipv4 const&)
{
	return sizeof(sockaddr_in);
}

inline constexpr auto family(ipv4 const&)
{
	return sock::family::ipv4;
}


struct socket_address_storage
{
	sockaddr sock;
	std::array<std::byte,sizeof(sockaddr_storage)<sizeof(sockaddr)?0x0:sizeof(sockaddr_storage)-sizeof(sockaddr)> storage;
};


//use memcpy is THE only way to do correct ip address punning
template<std::integral U>
inline constexpr auto to_socket_address_storage(ipv4 const& add,U port)
{
	sockaddr_in v4st{};
	v4st.sin_family=static_cast<sock::details::address_family>(fast_io::sock::family::ipv4);
	v4st.sin_port=details::big_endian(static_cast<std::uint16_t>(port));
	std::memcpy(std::addressof(v4st.sin_addr),add.storage.data(),sizeof(add.storage));
	socket_address_storage stor{};
	std::memcpy(std::addressof(stor),std::addressof(v4st),sizeof(sockaddr_in));
	return stor;
}

constexpr std::size_t print_reserve_size(io_reserve_type_t<ipv4>)
{
	return 15;
}

template<std::random_access_iterator Iter>
constexpr Iter print_reserve_define(io_reserve_type_t<ipv4>,Iter it,ipv4 const& v4)
{
	*(it=print_reserve_define(io_reserve_type<char unsigned>,it,v4.storage.front()))=u8'.';
	*(it=print_reserve_define(io_reserve_type<char unsigned>,++it,v4.storage[1]))=u8'.';
	*(it=print_reserve_define(io_reserve_type<char unsigned>,++it,v4.storage[2]))=u8'.';
	return print_reserve_define(io_reserve_type<char unsigned>,++it,v4.storage[3]);
}

struct ipv6
{
	std::array<std::uint16_t, 8> storage{};
};
inline constexpr std::size_t native_socket_address_size(ipv6 const&)
{
	return sizeof(sockaddr_in6);
}

inline constexpr auto family(ipv6 const&)
{
	return sock::family::ipv6;
}

template<character_input_stream input>
inline constexpr void space_scan_define(input& in,ipv6& v6)
{
/*	constexpr auto npos(static_cast<std::size_t>(-1));
	std::basic_string<typename input::char_type> str;
	scan(in,str);
	if(str.size()<2)
		throw fast_io_text_error(reinterpret_cast<char const*>(u8"ipv6 address too short"));
	else if(39<str.size())
		throw fast_io_text_error(reinterpret_cast<char const*>(u8"ipv6 address too long"));
	std::size_t colons(0),position(npos);
	if(str.front()!=0x3a)
		++colons;
	if(str.back()!=0x3a)
		++colons;
	for(std::size_t i(0);i!=str.size();++i)
		if(str[i]==0x3a)
		{
			++colons;
			if(i+1!=str.size()&&str[i+1]==0x3a)
			{
				position=i;
				++i;
			}
		}
	if(7<colons)
		throw fast_io_text_error(reinterpret_cast<char const*>(u8"too many : for ipv6 address"));
	if(position!=npos)
	{
		std::u8string tempstr(1,0x20);
		for(std::size_t i(9-colons);i--;)
			tempstr.append(u8"0 ",2);
		str.insert(position,tempstr);
	}
	fast_io::basic_istring_view<std::basic_string_view<typename input::char_type>> istrbuf(str);
	std::uint16_t temp{};
	for(auto i(v6.storage.begin()),e(v6.storage.end());i!=e;++i)
	{
		fast_io::scan(istrbuf,fast_io::hex(temp));
		*i=static_cast<std::byte>(temp>>8);
		*++i=static_cast<std::byte>(temp&255);
	}*/
}

template<std::integral U>
inline constexpr auto to_socket_address_storage(ipv6 add,U port)
{
	sockaddr_in6 v6st{};
	v6st.sin6_family=static_cast<sock::details::address_family>(fast_io::sock::family::ipv6);
	v6st.sin6_port=details::big_endian(static_cast<std::uint16_t>(port));
	if constexpr(std::endian::little==std::endian::native)
		for(auto& e : add.storage)
			e=details::byte_swap(e);
	std::memcpy(std::addressof(v6st.sin6_addr),add.storage.data(),sizeof(add.storage));
	socket_address_storage stor{};
	std::memcpy(std::addressof(stor),std::addressof(v6st),sizeof(sockaddr_in6));
	return stor;
}

constexpr std::size_t print_reserve_size(io_reserve_type_t<ipv6>)
{
	return 39;
}

namespace details
{

template<bool uppercase=false,char8_t base=16,std::random_access_iterator Iter>
constexpr Iter print_ipv6(Iter it,ipv6 const& v6)
{
	std::size_t max_zero_start{std::numeric_limits<std::size_t>::max()},max_zero_len{};
	std::size_t zero_start{std::numeric_limits<std::size_t>::max()},zero_len{};
	for(std::size_t i{};i!=v6.storage.size();++i)
	{
		if(v6.storage[i])
		{
			if(max_zero_len<zero_len)
			{
				max_zero_len=zero_len;
				max_zero_start=zero_start;
				zero_len=0;
				zero_start=std::numeric_limits<std::size_t>::max();
			}
		}
		else
		{
			++zero_len;
			if(!i||v6.storage[i-1])
				zero_start=i;
		}
	}
	if(max_zero_len<zero_len)
	{
		max_zero_start=zero_start;
		max_zero_len=zero_len;
	}
	if(max_zero_len<2)
	{
		for(std::size_t i{};i!=v6.storage.size();++i)
		{
			if(i)
			{
				*it=u8':';
				++it;
			}
			it=details::process_integer_output<base,uppercase>(it,v6.storage[i]);
		}
	}
	else
	{
		std::size_t i{};
		for(;i!=max_zero_start;++i)
		{
			if(i)
			{
				*it=u8':';
				++it;
			}
			it=details::process_integer_output<base,uppercase>(it,v6.storage[i]);
		}
		non_overlapped_copy_n(u8"::",2,it);
		i+=max_zero_len;
		it+=2;
		if(i!=8)
		{
			it=details::process_integer_output<base,uppercase>(it,v6.storage[i]);
			for(++i;i!=8;++i)
			{
				*it=u8':';
				it=details::process_integer_output<base,uppercase>(++it,v6.storage[i]);
			}
		}
	}
	return it;
}

}

template<std::random_access_iterator Iter>
constexpr Iter print_reserve_define(io_reserve_type_t<ipv6>,Iter it,ipv6 const& v6)
{
	return details::print_ipv6(it,v6);
}


class address
{
public:
	using variant_type = std::variant<ipv4, ipv6>;
	variant_type var;
	template<typename... Args>
	requires std::constructible_from<variant_type, Args...>
	explicit constexpr address(Args &&... args) :var(std::forward<Args>(args)...){}

	constexpr auto& variant() { return var; }
	constexpr auto& variant() const { return var; }
};

template<std::integral U>
inline constexpr auto to_socket_address_storage(address const& v,U port)
{
	return std::visit([port](auto const &arg) {
		return to_socket_address_storage(arg,port);
	}, v.variant());
}

inline constexpr std::size_t native_socket_address_size(address const& v)
{
	return std::visit([](auto const &arg) {
		return native_socket_address_size(arg);
	}, v.variant());
}


inline constexpr auto family(address const& v)
{
	return std::visit([](auto const &arg) {
		return family(arg);
	}, v.variant());
}

constexpr std::size_t print_reserve_size(io_reserve_type_t<address>)
{
	return 39;
}


template<std::random_access_iterator Iter>
constexpr Iter print_reserve_define(io_reserve_type_t<address>,Iter it,address const& v)
{
	return std::visit([&](auto&& arg) {
		return print_reserve_define(io_reserve_type<std::decay_t<decltype(arg)>>,it,arg);
	}, v.variant());
}

}