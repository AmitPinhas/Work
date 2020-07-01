#include <stdio.h>
#include "e3_e4.h"

int count_digits(unsigned int _number);
int Get_Left_Digit(int _count ,unsigned int _number);
int Get_divide(int _count);

int Check_Ascending_Order(unsigned int _number)
{
    int small_num , big_num , count;
    
    count=count_digits(_number);
    
    while (count>1)
    {
        big_num = _number%10;
        _number /=10;
        count--;
        small_num = _number%10;
        
        if(small_num>big_num)
        {
            return ERROR;
        }
    }
    return OK;
}


int Check_Palindrome(unsigned int _number)
{
    int count , left_digit , right_digit , divide ;
    
    count=count_digits(_number);
    
    while(count > 1)
    {
       right_digit=_number%10;
       left_digit=Get_Left_Digit(count , _number);
       if(left_digit != right_digit)
       {
        return ERROR;
       }
       else
       {
         divide=Get_divide(count);
         _number %=divide;
         count -=2;
        _number /=10;
        
       }
    }
    
    return OK;
}

int count_digits(unsigned int _number)
{
    int count=0;
    
    while(_number)
    {
        count++;
        _number /=10;
    }
    
    return count;
    
}

int Get_Left_Digit(int _count ,unsigned int _number)
{
    int left_digit , divide;
    
    divide=Get_divide(_count);
    
    left_digit= _number/divide;
    
    return left_digit;
}

int Get_divide(int _count)
{
    int divide=1 , tmp;
    
    for(tmp=1 ; tmp<_count ; tmp++)
    {
        divide *=10;
    }
    
    return divide;
}
unsigned int Get_Number()
{
	unsigned int number;
	
	printf("Please enter number --> ");
	scanf("%u",&number);
	
	return number;

}
