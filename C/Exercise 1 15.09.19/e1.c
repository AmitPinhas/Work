#include <stdio.h>
#include "e1.h"

char Arithmetic1(int num1 ,int num2);
int GetNumber();
int Sum(int num1 ,int num2);
int Difference(int num1 , int num2);  
int Multiply(int num1 , int num2);
int Get_Question();

int Get_Question()
{
    int num;
	
	printf("Please enter the question number --> ");
	scanf("%d" , &num);
	
	return num;
}

char Arithmetic1(int num1 ,int num2)
{
    char con;    
    
    Sum(num1 , num2);
    Difference(num1 , num2);
    Multiply(num1 , num2);
    
    printf("continue(Y/N)? ")
    con=getchar();
    
    return con;
    
}

int GetNumber()
{
	int num;
	
	printf("Please enter integer number --> ");
	scanf("%d" , &num);
	
	return num;
}

int Sum(int num1 , int num2)
{
    int result;
    
    result=num1+num2;
    
    printf("%d + %d = %d\n" , num1 , num2 , result);
    
    return OK;
}

int Difference(int num1 , int num2)
{
    int result;
    
    result=num1-num2;
    
    printf("%d - %d = %d\n" , num1 , num2 , result);
    
    return OK;
}

int Multiply(int num1 , int num2)
{
    int result;
    
    result=num1*num2;
    
    printf("%d * %d = %d\n" , num1 , num2 , result);
    
    return OK;
}
