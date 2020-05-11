#include<array>
#include<cctype>
#include<iostream>
#include"../timer.h"
#include<locale>
template<typename T>
inline constexpr bool misspace1(T const& e)
{
	return e==' '||e=='\t'||e=='\n'||e=='\v'||e=='\f'||e=='\r';
}

template<typename T>
inline constexpr bool misspace2(T const& t)
{
	std::make_unsigned_t<T> e(t);
	return e==' '||e=='\t'||e=='\n'||e=='\v'||e=='\f'||e=='\r';
}

template<typename T>
inline constexpr bool misspace3(T const& e)
{
	switch(e)
	{
		case ' ':case'\t':case '\n':case '\v':case '\f':case '\r': return true;
	}
	return false;
}

template<typename T>
inline constexpr bool misspace4(T const& t)
{
	std::make_unsigned_t<T> e(t);
	switch(e)
	{
		case ' ':case'\t':case '\n':case '\v':case '\f':case '\r': return true;
	}
	return false;
}

template<typename T>
inline constexpr bool fastisspace(T ch)
{
	return (9<=ch&&ch<=13)||ch==0x20;
}

template<typename T>
inline constexpr bool fastisspacerev(T ch)
{
	return ch==0x20||(9<=ch&&ch<=13);
}

template<typename T>
inline constexpr bool fastisspacerev2(T ch)
{
	if(ch==0x20)
		return true;
	std::make_unsigned_t<T> e(ch);
	e-=9;
	return e<5;
}

template<typename T>
inline constexpr bool fastisspacerev3(T ch)
{
	switch(ch)
	{
		case 20: return true;
		default:
			std::make_unsigned_t<T> e(ch);
			e-=9;
			return e<5;
	}
	
}

template<typename T>
inline constexpr bool fastisspacerev4(T ch)
{
	return ch==0x20|
	static_cast<std::make_unsigned_t<T>>(static_cast<std::make_unsigned_t<T>>(ch)-9)
	<static_cast<std::make_unsigned_t<T>>(5);
}

int main()
{
	std::array<char,4> a={'a',u8'e',u8'f',105};
	std::size_t constexpr N(200000000);
	std::size_t v(0);
	{
		fast_io::timer t("std::isspace");
		for(std::size_t i(0);i!=N;++i)
		{
			for(auto const& e : a)
				v+=std::isspace(e)|std::isspace(e+1)|std::isspace(e+2)|std::isspace(e+3);
		}
	}
	{
		std::locale loc;
		auto& f{std::use_facet<std::ctype<char>>(loc)};
		fast_io::timer t("std::ctype::is()");
		for(std::size_t i(0);i!=N;++i)
		{
			for(auto const& e : a)
				v+=f.std::ctype<char>::is(std::ctype<char>::space,e)|
				f.std::ctype<char>::is(std::ctype<char>::space,e+1)|
				f.std::ctype<char>::is(std::ctype<char>::space,e+2)|
				f.std::ctype<char>::is(std::ctype<char>::space,e+3);
		}
	}
	{
		fast_io::timer t("misspace1");
		for(std::size_t i(0);i!=N;++i)
		{
			for(auto const& e : a)
				v+=misspace1(e)|misspace1(e+1)|misspace1(e+2)|misspace1(e+3);
		}
	}
	{
		fast_io::timer t("misspace2");
		for(std::size_t i(0);i!=N;++i)
		{
			for(auto const& e : a)
				v+=misspace2(e)|misspace2(e+1)|misspace2(e+2)|misspace2(e+3);
		}
	}
	{
		fast_io::timer t("misspace3");
		for(std::size_t i(0);i!=N;++i)
		{
			for(auto const& e : a)
				v+=misspace3(e)|misspace3(e+1)|misspace3(e+2)|misspace3(e+3);
		}
	}
	{
		fast_io::timer t("misspace4");
		for(std::size_t i(0);i!=N;++i)
		{
			for(auto const& e : a)
				v+=misspace4(e)|misspace4(e+1)|misspace4(e+2)|misspace4(e+3);
		}
	}
	{
		fast_io::timer t("fastisspace");
		for(std::size_t i(0);i!=N;++i)
		{
			for(auto const& e : a)
				v+=fastisspace(e)|fastisspace(e+1)|fastisspace(e+2)|fastisspace(e+3);
		}
	}
	{
		fast_io::timer t("fastisspacerev");
		for(std::size_t i(0);i!=N;++i)
		{
			for(auto const& e : a)
				v+=fastisspacerev(e)|fastisspacerev(e+1)|fastisspacerev(e+2)|fastisspacerev(e+3);
		}
	}
	{
		fast_io::timer t("fastisspacerev2");
		for(std::size_t i(0);i!=N;++i)
		{
			for(auto const& e : a)
				v+=fastisspacerev2(e)|fastisspacerev2(e+1)|fastisspacerev2(e+2)|fastisspacerev2(e+3);
		}
	}
	{
		fast_io::timer t("fastisspacerev3");
		for(std::size_t i(0);i!=N;++i)
		{
			for(auto const& e : a)
				v+=fastisspacerev3(e)|fastisspacerev3(e+1)|fastisspacerev3(e+2)|fastisspacerev3(e+3);
		}
	}
	{
		fast_io::timer t("fastisspacerev4");
		for(std::size_t i(0);i!=N;++i)
		{
			for(auto const& e : a)
				v+=fastisspacerev4(e)|fastisspacerev4(e+1)|fastisspacerev4(e+2)|fastisspacerev4(e+3);
		}
	}
	std::cout<<v<<'\n';
}