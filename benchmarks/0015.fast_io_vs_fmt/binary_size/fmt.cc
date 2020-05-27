#include<fmt/format.h>
#include<stdio.h>

int main()
{
	std::size_t value;
	scanf("%zu",&value);
	printf("%zu\n",fmt::format_int(value).str().size());
}