#include<stdio.h>
int main()
{
	char str[60];
	fgets(str,59,stdin); // input func: fgest, stream: stdin.
	printf(str); // vuln : ’str’ is controlled by
	// an external agent
}