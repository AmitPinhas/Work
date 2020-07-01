#include <stdio.h>

int foo2(long i)
{
	int yy = 0xFFFFBBBB;
	printf("\nim in foo2\n");
}

int foo1(long i , long i2 , long i3 , long i4 , long i5 , long i6 , long i7);


int main(void)
{
	long num1 = 0x000BEEF1 , num2 = 0x000BEEF2 , num3 = 0x000BEEF3 , num4 = 0x000BEEF4 , num5 = 0x000BEEF5 , num6 = 0x000BEEF6 , num7 = 0x000BEEF7  ;
	
	printf("I'm in main\n");
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpedantic"
	printf("address : %p main : %p foo2 : %p \n" , (void*)&num1 , (void*)&main , (void*)&foo2 );
	printf("value ox : %lx \n" , main );
	printf("value dec : %ld \n" , main );
#pragma GCC diagnostic pop		
	foo1(num1 , num2 , num3 , num4 , num5 , num6 , num7);
	printf("I'm back\n");
	
	return 1;
}


int foo1(long i , long i2 , long i3 , long i4 , long i5 , long i6 , long i7)
{
	long num10 = 0xa0a0a0a0a ,  in=0;
	
	printf("I'm in foo1\n");
	
	for ( in = 0 ; in<10 ; ++in)
	{
	
	printf("address : %-20p alue ox :0x%-20lx value dec : %-20ld\t\t  \n" , &num10-in , *(&num10-in) , *(&num10-in) );
	
	}
	
	putchar('\n');
	
	for ( in = 0 ; in<25 ; ++in)
	{
	
	printf("address : %-20p alue ox :0x%-20lx value dec : %-20ld  \n" , &num10+in , *(&num10+in) , *(&num10+in) );
	
	}	
	
	*(&num10+4) = &foo2 ;
	
	return i;	
}
