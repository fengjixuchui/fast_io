#include<stdio.h>
int main()
{
	char str[10];
	sprintf(str,"%s","AAAAAAAAAAAAA"); // buffer overflow !
	// sizef(str) < sizeof (output) : 10 < 14.
}