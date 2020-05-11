#pragma once
#ifdef __clang__
#include<chrono>
#include<cstdio>
#include<string_view>
#else
#include"../include/fast_io.h"
#endif
namespace fast_io
{

class timer
{
	std::string_view s;
	std::chrono::high_resolution_clock::time_point t0;
public:
	template<typename ...Args>
#ifndef __clang__
	requires std::constructible_from<std::string_view,Args...>
#endif
	timer(Args&& ...args):s(std::forward<Args>(args)...),t0(std::chrono::high_resolution_clock::now()){}
	timer(const timer&) = delete;
	timer& operator=(const timer&) = delete;
	~timer()
	{
#ifdef __clang__
		fprintf(stderr,"%s:%.17g\n",s.data(),std::chrono::duration_cast<std::chrono::duration<double>>(std::chrono::high_resolution_clock::now()-t0).count());
#else
		println(fast_io::err,s,u8":\t",std::chrono::high_resolution_clock::now()-t0);
#endif
	}
};

}
