#include<iostream>
#include<iomanip>

int main()
{
	double d;
	std::cin>>d;
	std::cout<<std::setprecision(0);
	std::cout<<std::defaultfloat<<d<<'\n';
	std::cout<<std::fixed<<d<<'\n';
	std::cout<<std::scientific<<d<<'\n';
	std::cout<<std::hexfloat<<d<<'\n';
}