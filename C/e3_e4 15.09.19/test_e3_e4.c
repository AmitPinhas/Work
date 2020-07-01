#include <stdio.h>
#include "e3_e4.h"

int main()
{
   unsigned int number;
   int result;
    
    number=Get_Number();
    
    result=Check_Palindrome(number);
    
    printf("Palindrome--> %d\n" , result);
    
    number=Get_Number();
    
    result=Check_Ascending_Order(number);
    
    printf("Ascending order--> %d\n" , result);
    
    return OK;
}
