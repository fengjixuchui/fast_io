#include<stdio.h>
int main(){
char str[10];
gets(str); // unbounded input causing an overflow.
}