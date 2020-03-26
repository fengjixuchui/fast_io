#pragma once

namespace fast_io::details::jiaendu
{

inline constexpr auto calculate_offset()
{
	std::array<char8_t,1000> gen{};
	for(std::size_t i(0);i!=10;++i)
		gen[i]=1;
	for(std::size_t i(10);i!=100;++i)
		gen[i]=2;
	for(std::size_t i(100);i!=1000;++i)
		gen[i]=3;
	return gen;
}
/*
template<typename T>
inline constexpr auto calculate_table1()
{
	std::array<std::array<T,4>,10> gen{};
	for(char8_t i(0);i!=gen.size();++i)
		gen[i].front()=i+u8'0';
	return gen;
}
*/

template<typename T>
inline constexpr auto calculate_table2()
{
	std::array<std::array<T,2>,100> gen{};
	for(char8_t i(0);i!=10;++i)
		for(char8_t j(0);j!=10;++j)
		{
			auto& ele(gen[static_cast<std::size_t>(i)*10+
			static_cast<std::size_t>(j)]);
			ele.front()=i+u8'0';
			ele[1]=j+u8'0';
		}
	return gen;
}
template<typename T>
inline constexpr auto calculate_table3()
{
	std::array<std::array<T,4>,1000> gen{};
	for(char8_t i(0);i!=10;++i)
		for(char8_t j(0);j!=10;++j)
			for(char8_t k(0);k!=10;++k)
			{
				std::size_t pos(static_cast<std::size_t>(i)*100+
					static_cast<std::size_t>(j)*10+
					static_cast<std::size_t>(k));
				auto& ele(gen[pos]);
				ele.front()=i+u8'0';
				ele[1]=j+u8'0';
				ele[2]=k+u8'0';
			}
	return gen;
}
template<typename T>
inline constexpr auto calculate_table4()
{
	std::array<std::array<T,4>,10000> gen{};
	for(char8_t i(0);i!=10;++i)
		for(char8_t j(0);j!=10;++j)
			for(char8_t k(0);k!=10;++k)
				for(char8_t m(0);m!=10;++m)
				{
					auto& ele(gen[static_cast<std::size_t>(i)*1000+
						static_cast<std::size_t>(j)*100+
						static_cast<std::size_t>(k)*10+
						static_cast<std::size_t>(m)]);
					ele.front()=i+u8'0';
					ele[1]=j+u8'0';
					ele[2]=k+u8'0';
					ele[3]=m+u8'0';
				}
	return gen;
}
template<typename T>
inline constexpr auto calculate_table5()
{
	std::array<std::array<T,4>,1000> gen{};
	for(char8_t i(0);i!=10;++i)
		gen[i].front()=i+u8'0';
	for(char8_t i(1);i!=10;++i)
		for(char8_t j(0);j!=10;++j)
		{
			auto& ele(gen[static_cast<std::size_t>(i)*10+
			static_cast<std::size_t>(j)]);
			ele.front()=i+u8'0';
			ele[1]=j+u8'0';
		}
	for(char8_t i(1);i!=10;++i)
		for(char8_t j(0);j!=10;++j)
			for(char8_t k(0);k!=10;++k)
			{
				std::size_t pos(static_cast<std::size_t>(i)*100+
					static_cast<std::size_t>(j)*10+
					static_cast<std::size_t>(k));
				auto& ele(gen[pos]);
				ele.front()=i+u8'0';
				ele[1]=j+u8'0';
				ele[2]=k+u8'0';
			}
	return gen;
}
template<bool controller=false>
class static_offset
{
public:
	inline static constexpr auto offset{calculate_offset()};
};

template<std::integral ch_type = char8_t>
class static_tables
{
public:
//Is table 1 useless??
	using type = std::conditional_t<sizeof(ch_type)==1,char8_t,
		std::conditional_t<sizeof(ch_type)==2,char16_t,
		std::conditional_t<sizeof(ch_type)==4,char32_t,ch_type>>>;
	inline static constexpr auto table2{calculate_table2<type>()};
	inline static constexpr auto table3{calculate_table3<type>()};
	inline static constexpr auto table4{calculate_table4<type>()};
	inline static constexpr auto table5{calculate_table5<type>()};
};

}