#include <stdio.h>
#include <string.h>
#include "e_string.h"

int Positive_Convert_Bin_Dec();

int main()
{
    char str[]="0" ,  str2[]="-21" , ch = 'b' , ch2 = 'd' , str_3[]="3" , str_result[100] , str_result2[100] , str_result3[100] , str_result4[100] , str_result5[100] , str_result6[100]  , str_4[]="101" , str_5[]="0" ;
    int result=0 , number=65743;
    
/*    printf("original str --> ");
    puts(str);
	
    Reverse_String(str);
    
    printf("reverse str --> ");
	puts(str);
    
    Is_Palindrome(str);
    
    printf("str atoi --> ");
    puts(str2);
    My_Atoi(str2 , &result);
    printf("%d\n",result);
    
    My_Itoa(str_result , number);
    puts(str_result); */
    
    Positive_Convert_Bin_Dec();
    
    
     /* test Convert_Bin_Dec 3 : ch = 'd' , str= -21 */

   if((result= Convert_Bin_Dec(ch2 ,str2 , str_result3)) != OK)
   {
     printf("ERROR\n");
   }
   else
   {
     printf("PASS\n");
     puts(str_result3);
   }     
    
    /* test Convert_Bin_Dec 4 : ch = 'b' , str= 101 */
   if((result= Convert_Bin_Dec(ch ,str_4 , str_result4)) != OK)
   {
     printf("ERROR\n");
   }
   else
   {
     printf("PASS\n");
     puts(str_result4);
   } 

    /* test Convert_Bin_Dec 5 : ch = 'b' , str= 0 */

   if((result= Convert_Bin_Dec(ch ,str_5 , str_result5)) != OK)
   {
     printf("ERROR\n");
   }
   else
   {
     printf("PASS\n");
     puts(str_result5);
   }     

    
	return OK;
}

int Positive_Convert_Bin_Dec()
{
    char ch='d' , str[]="3" , str_result[200] , str2[]="0" , str_result2[200];     
     
   /* test Convert_Bin_Dec 1 : ch = 'd' , str= 3 */
    
   if((result= Convert_Bin_Dec(ch ,str , str_result)) != OK)
   {
     printf("ERROR\n");
   }
   else
   {
     printf("PASS\n");
     puts(str_result);
   } 
   
   /* test Convert_Bin_Dec 2 : ch = 'd' , str= 0 */
    
   if((result= Convert_Bin_Dec(ch ,str2 , str_result2)) != OK)
   {
     printf("ERROR\n");
   }
   else
   {
     printf("PASS\n");
     puts(str_result2);
   } 
     
     return OK;
}

/* Name: Amit Pinhas */
