#include <stdio.h>
#include "e1.h"

int main()
{
   int num_q , num1 , num2;
   char continued='Y' ;
   
   while(continued=='Y')
   {
   num_q=Get_Question();
   
   switch(num_q)
   {
        case 1:
           num1=GetNumber(); 
           num2=GetNumber();
           continued=Arithmetic1(num1 , num2);
           break;
        case 2:
        break;
        case 3:
        break;
        case 4:
        break;
        case 5:
        break;
        case 6: 
        break;
        case 7:
        
        default:
        break;
   }
   }

   return OK;
}
