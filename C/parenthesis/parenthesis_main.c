#include <stdio.h>
#include <string.h> /* str_len */
#include "ADTDefs.h"
#include "stack.h"

int BalanceCheckParenthesisTest(char *_str); 
int CheckRightPar(char *_str ,int _index ,Stack *_stack ,int *_flag);

int main()
{
     char str[]="if(a+{2*max(A[],5)}>7)" , str2[]="if(a+{2*max(A[],5)}>7))" , str3[]="if((a+{2*max(A[],5)}>7)" , str4[]="csoivnvo" ;
     int result=-1 , result2=-1 , result3=-1 ,result4=-1;
     
     result=BalanceCheckParenthesisTest(str);
     printf("%d\n" , result);      

     result2=BalanceCheckParenthesisTest(str2);
     printf("%d\n" , result2); 
     
     result3=BalanceCheckParenthesisTest(str3);
     printf("%d\n" , result3);         
          
     result4=BalanceCheckParenthesisTest(str4);
     printf("%d\n" , result4);           
          
     return 1 ;
}

int BalanceCheckParenthesisTest(char *_str)
{
     int index , size , flag=1 ;
     Stack *stack;
     
     size = strlen(_str);
     stack=StackCreate(size , 0);
     
     for(index=0 ; _str[index] != '\0' ; index++)
     {   
          if((_str[index] == '(') || (_str[index] == '[') || (_str[index] == '{') && flag)
          {
              StackPush(stack , _str[index]);
          }
          
          if ((CheckRightPar(_str , index , stack , &flag)) == 0)
          {
               return 0;
          }                  
     }
     
     if(StackIsEmpty(stack))
     {
        return 1;
     }
     else
     {
        return 0;
     }     
}

int CheckRightPar(char *_str ,int _index ,Stack *_stack ,int *_flag)
{
     int num;
     
          if(_str[_index] == ')')
          {
          if(StackIsEmpty(_stack))
          {
               return 0;
          }
               StackPop (_stack ,&num);
               if( num != (int)'(')
               {
                    return 0;
               }
               *_flag=0 ;              
          }
          
          if(_str[_index] == ']')
          {
          if(StackIsEmpty(_stack))
          {
               return 0;
          }          
          StackPop (_stack ,&num);
           if( num != (int)'[')
            {
                return 0;
            }
               *_flag=0 ;          
          }
          
          if(_str[_index] == '}')
          {
          if(StackIsEmpty(_stack))
          {
               return 0;
          }          
          StackPop (_stack ,&num);
           if( num != (int)'{')
            {
                return 0;
            }
               *_flag=0 ;          
          }            
}
