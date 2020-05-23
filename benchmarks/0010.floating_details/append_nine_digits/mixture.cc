#include"../../../include/fast_io.h"
#include"../../../include/fast_io_device.h"
#include"../../timer.h"
#include<random>
template<std::random_access_iterator Iter>
inline constexpr void append_nine_digits_dummy(Iter str,std::uint32_t value)
{
	using char_type = std::iter_value_t<Iter>;
	str+=9;
	for(std::size_t i{};i!=9;++i)
	{
		std::uint32_t const temp(value/10);
		char_type const res(value%10);
		*--str=u8'0'+res;
		value = temp;
	}
}

template<std::random_access_iterator Iter>
inline constexpr void append_nine_digits(Iter str,std::uint32_t value)
{
	using char_type = std::iter_value_t<Iter>;
#ifndef FAST_IO_OPTIMIZE_SIZE
	if(std::is_constant_evaluated())
#endif
		append_nine_digits_dummy(str,value);
#ifndef FAST_IO_OPTIMIZE_SIZE
	else
	{
	#if (_WIN64 || __x86_64__ || __ppc64__)
		std::uint64_t remains0{(static_cast<std::uint64_t>(value) *
		static_cast<std::uint64_t>(3518437209)) >> 45};
		std::uint64_t remains1{static_cast<std::uint64_t>(value) * 
		static_cast<std::uint64_t>((2882303762)) >> 58};
	#else
		std::uint32_t remains0{value/10000};
		std::uint32_t remains1{value/100000000};
	#endif
		auto v2(remains1);
		remains1 = remains0 - remains1*10000;
		remains0 = value - remains0*10000;
		*str = static_cast<char8_t>(v2)+u8'0';
		fast_io::details::my_copy_n(fast_io::details::jiaendu::static_tables<char_type>::table4[remains1].data(),4,++str);
		fast_io::details::my_copy_n(fast_io::details::jiaendu::static_tables<char_type>::table4[remains0].data(),4,str += 4);
	}
#endif
}

int main()
{
	constexpr std::size_t N{10000000};
	std::vector<std::uint32_t> vec;
	vec.reserve(N);
	std::mt19937_64 eng;
	std::uniform_int_distribution dis(0,999999999);
	for(std::size_t i(0);i!=N;++i)
		vec.emplace_back(dis(eng));
	{
		fast_io::timer tm("output");
		fast_io::obuf_file obf("jiaendu.txt");
		for(std::size_t i{};i!=N;++i)
		{
			auto ptr{oreserve(obf,10)};
			if(ptr)[[likely]]
			{
				ptr[9]=u8'\n';
				append_nine_digits(ptr,vec[i]);
				orelease(obf,ptr+10);
			}
			else
			{
				std::array<char,10> tembuf;
				tembuf.back()=u8'\n';
				append_nine_digits(tembuf.data(),vec[i]);
				write(obf,tembuf.data(),tembuf.data()+tembuf.size());
			}
		}
	}
}