#include<iostream>
#include<stdlib.h>

int main()
{
	std::cout.exceptions(std::ios::failbit|std::ios::badbit);
	std::cout<<"Hello World\n";
}

// gcc -o cout cout.cc -Ofast -flto -Ofast -DNDEBUG
// no static linking
//binary size: 15kb