#include<stdio.h>
int main()
{
	int a;
	char *s;
	a = 0;
	s = "hello";
	printf("%b",a); // wrong format: unknown format specifier %b
	printf("%d",s); // wrong format: wrong argument
	// type ’char *’ expected ’int’
	printf("%d %d",a); // wrong format: wrong argument count
}