#include <stdio.h>

struct S1{
	char ch;
	char ch2;	
	int i;
	float j;
};


int main()
{
	printf("%ld\n" , sizeof(struct S1));
	printf("%ld\n" , sizeof(int*));
	printf("%ld\n" , sizeof(float));	
	return 1;
}
