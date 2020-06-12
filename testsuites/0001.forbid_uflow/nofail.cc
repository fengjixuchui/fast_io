#include"../../include/fast_io.h"
#include"../../include/fast_io_legacy.h"
#include<iostream>

int main()
{
	std::ios::sync_with_stdio(false);
	fast_io::streambuf_io_observer ciniob{std::cin.rdbuf()};
	for(std::size_t val{};scan<true>(ciniob,val);println(val));
}

//this should not throw exceptions for libstdc++ because this bullshit is now a buffer_input_stream.
//iostream is cancer.
//Who designed this bullshit????