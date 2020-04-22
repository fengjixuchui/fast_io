#include<stdio.h>
#include<stdlib.h>
int main(){
	unsigned size;
	scanf("%d",&size); // input func : scanf, input stream: stdin.
	void * buf = malloc(size);
	// vuln : allocation size in controlled
	// by an external attacker.
}