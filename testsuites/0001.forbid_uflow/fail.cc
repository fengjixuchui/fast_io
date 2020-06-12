#include"../../include/fast_io.h"
#include"../../include/fast_io_legacy.h"
#include<iostream>

int main()
{
	fast_io::streambuf_io_observer ciniob{std::cin.rdbuf()};
	for(std::size_t val{};scan<true>(ciniob,val);println(val));
}

//this should throw exceptions for libstdc++ because this bullshit is not a buffer_input_stream.
//iostream is cancer.
