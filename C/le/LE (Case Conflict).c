#include <stdio.h>
#include <stdarg.h>
#include <string.h>

#define TRUE 1
#define FALSE 0
void swap(char *x, char *y) {
	char t = *x; *x = *y; *y = t;
}

char* reverse(char *buffer, int i, int j)
{
	while (i < j)
		swap(&buffer[i++], &buffer[j--]);
	return buffer;
}

/* Iterative function to implement itoa() function in C*/
char* itoa(int value, char* buffer, int base)
{
	int n = abs(value);
	int i = 0;
	/* invalid input*/
	if (base < 2 || base > 32)
		return buffer;
	/* consider absolute value of number*/
	while (n)
	{
		int r = n % base;
		if (r >= 10)
			buffer[i++] = 65 + (r - 10);
		else
			buffer[i++] = 48 + r;
		n = n / base;
	}
	if (i == 0)
		buffer[i++] = '0';
	if (value < 0 && base == 10)
		buffer[i++] = '-';
	buffer[i] = '\0';
	return reverse(buffer, 0, i - 1);
}

double ave(int n, ...){
	double ave=0;
	int i;
	va_list ap;
	va_start(ap,n);
	for(i=0;i<n;++i)
	{
		ave += va_arg(ap,int);
	}
	va_end(ap);
	return ave/n;
}
void minprintf(char* str, ...)
{
	int i=0,count=0,temp;
	char ptr[50],ch;
	va_list ap;
	va_start(ap,str);
	i=0;
	while(str[i]){
		if(str[i]=='%' && str[i+1]=='d')
		{
			temp=va_arg(ap,int);
			itoa(temp,ptr,10);
			fputs(ptr,stdout);
			i++;
		}
		else 
		{
			if(str[i]=='%' && str[i+1]=='s')
				{
					strcpy(ptr,va_arg(ap,char*));
					fputs(ptr,stdout);
					i++;
				}
		   	else
		   	{ 
				if(str[i]=='%' && str[i+1]=='c'){
					ch=va_arg(ap,int);
					putchar(ch);
					i++;
				}
				else
				{ 
				putchar(str[i]);
				}
			}
		}
		++i; 
	}
	va_end(ap);	
}
int IsLe(){
	int i=1;
	char *ptr=(char*)&i;
	return (*ptr==1)?TRUE:FALSE;
}

int main(){
	char ch='-';
	char str[]="amit poz";
	printf("%d =LE\n",IsLe());
	printf("ave 1 = %f\n",ave(3,1,2,3));
	minprintf("my int is %d",3);
	printf("\n");
	minprintf("my int is %s",str);
	minprintf("my int is %c",ch);
}
