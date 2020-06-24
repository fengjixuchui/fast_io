#include"../../include/fast_io.h"

extern "C" int f2s_buffered_n(float f, char* result);

int main()
{
	std::array<char,100> array;
/*	int n=f2s_buffered_n(6381.5723f,array.data());
	array[n++]='\n';
	write(fast_io::out(),array.data(),array.data()+n);
	print("\n\n\n\n");
	println("my result:",6381.5723f);*/
	int n=f2s_buffered_n(8.999999E9f,array.data());
	array[n++]='\n';
	write(fast_io::out(),array.data(),array.data()+n);
	print("\n\n\n\n");
	println("my result:",8.999999E9f);

}