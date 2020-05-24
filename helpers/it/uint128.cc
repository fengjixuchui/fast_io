#include"../../include/fast_io.h"

template<std::contiguous_iterator Iter>
inline void output_unsigned_partial(Iter str,std::uint64_t value)
{
	using ch_type = std::remove_cvref_t<decltype(*str)>;
	constexpr std::size_t bytes4{4*sizeof(ch_type)};
	std::uint64_t v4{value/10000000000000000ULL};
	std::uint64_t remains3{value-v4*10000000000000000ULL};
	std::uint64_t temp3(remains3/1000000000000ULL);
	std::uint64_t remains2
	{remains3-temp3*1000000000000ULL};
	remains3=temp3;
	std::uint64_t temp2{remains2};
	std::uint64_t remains0{remains2/10000};
	std::uint64_t remains1{remains2/100000000};
	remains2 = remains1;
	remains1 = remains0 - remains1*10000;
	remains0 = temp2 - remains0*10000;
	using namespace fast_io::details::jiaendu;
	memcpy(str,static_tables<ch_type>::table4[v4].data()+1,3*sizeof(ch_type));
	memcpy(str + 3,static_tables<ch_type>::table4[remains3].data(),bytes4);
	memcpy(str + 7,static_tables<ch_type>::table4[remains2].data(),bytes4);
	memcpy(str + 11,static_tables<ch_type>::table4[remains1].data(),bytes4);
	memcpy(str + 15,static_tables<ch_type>::table4[remains0].data(),bytes4);
}

template<std::contiguous_iterator Iter,typename U>
requires (sizeof(U)==16)
inline std::size_t uint128_t_output(Iter str,U value)
{
	using ch_type = std::remove_cvref_t<decltype(*str)>;
	constexpr std::size_t bytes4{4*sizeof(ch_type)};
	constexpr auto zero39{fast_io::details::compile_pow10<U,38>()};
	using namespace fast_io::details::jiaendu;
	if(value>=zero39)
	{
		auto v3{value/zero39};
		auto remain3{value-v3*zero39};
		auto v2{remain3/10000000000000000000ULL};
		std::uint64_t remain{static_cast<std::uint64_t>(remain3-v2*10000000000000000000ULL)};
		*str=static_cast<char8_t>(v3)+u8'0';
		output_unsigned_partial(str+1,static_cast<std::uint64_t>(v2));
		output_unsigned_partial(str+20,remain);
		return 39;
	}
	else if(value>=10000000000000000000ULL)
	{
		auto v2{value/10000000000000000000ULL};
		std::uint64_t remain{static_cast<std::uint64_t>(value-v2*10000000000000000000ULL)};
		auto offset{output_unsigned(str,static_cast<std::uint64_t>(v2))};
		output_unsigned_partial(str+offset,remain);
		return offset+19;
	}
	else
		return output_unsigned(str,static_cast<std::uint64_t>(value));
}

int main()
{
	std::array<char,1000> buffer;
	std::size_t pos{uint128_t_output(buffer.data(),(static_cast<__uint128_t>(10000000000000000000ULL)))};
	buffer[pos]=u8'\n';
	write(fast_io::out,buffer.data(),buffer.data()+pos+1);
}