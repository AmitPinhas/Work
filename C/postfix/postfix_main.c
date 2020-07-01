#include <stdio.h>
#include <string.h> /* strlen */
#include <stdlib.h> /* malloc */
#include "ADTDefs.h"
#include "stack.h"

/*
    Description: Takes a complex exercise and returns its result.
    Input: pointer to infix and pointer to the result.
    Output: ERR_OK / FALSE .
    ERROR: ERR_OK - The exercise is resolved successfully, the answer is stored in the result pointer.
           ERR_NOT_INITIALIZED - pointer to infix = null or pointer to result = null.
*/
ADTErr InfixToPostfixToInt(char *_exercise , int *_result);
ADTErr InfixToPostfix(char *_exercise , char *_postfix  , Stack *_stack);
ADTErr PostfixToInt(char *_postfix , Stack *_stack , int *_result); 
ADTErr CheckAction(char *_exercise , int _index , Stack *_stack , int *_index2 , char *_postfix);
ADTErr CheckActionTwo(int _index , char *_postfix , Stack *_stack , int *_result);


int main()
{
     char  str[]="2*3+4", str2[]="2*(3+4)" , str3[]="7";
     
     int result , result2 , result3;
     
     InfixToPostfixToInt(str , &result);     
     printf("%d\n" , result);
     
     InfixToPostfixToInt(str2 , &result2);     
     printf("%d\n" , result2); 
     
     InfixToPostfixToInt(str3 , &result3);     
     printf("%d\n" , result3);          
          
     return 1;
}


ADTErr InfixToPostfixToInt(char *_exercise , int *_result)
{
     int  size ;     
     char *postfix;     
     Stack *stack;
     *_result = 0;
     
     if (NULL == _exercise || NULL == _result)
     {
          return ERR_NOT_INITIALIZED;
     }
             
     size = strlen(_exercise);
     stack=StackCreate(size , 0); 
     postfix = (char*)malloc((size+1) * sizeof(char)); /* +1 for '\0' */ 
     
     if( NULL == postfix )
     {
          return ERR_NOT_INITIALIZED;
     }
     
     InfixToPostfix(_exercise , postfix  , stack); 
     
     PostfixToInt(postfix , stack , _result);  
     
     StackDestroy(stack);
     free(postfix);
     
     return ERR_OK;
}


ADTErr InfixToPostfix(char *_exercise , char *_postfix  , Stack *_stack)
{
     int index, index2=0 , num;

     for(index=0 ; _exercise[index] != '\0' ; index++ )
     {
          if(isdigit(_exercise[index]))
          {
               _postfix[index2] = _exercise[index];
               index2++ ;
          }
          else
          {
               CheckAction(_exercise , index , _stack , &index2 , _postfix);               
          }
          
     }
     
      while(!(StackIsEmpty(_stack)))
      { 
          StackPop(_stack , &num);
          _postfix[index2] = num;  
          index2++;
      }       
     
     _postfix[index2] = '\0';
     
     return ERR_OK;
}


ADTErr PostfixToInt(char *_postfix , Stack *_stack , int *_result)
{
     int index , num1;

     for(index=0 ; _postfix[index] != '\0' ; index++)
     {
          if(isdigit(_postfix[index]))
          {
               StackPush(_stack ,_postfix[index]);  
          } 
          else
          {       
          CheckActionTwo(index , _postfix , _stack , _result);                     
          }  
     }
     
     StackPop(_stack , &num1);
     *_result = num1-'0';
     
     return ERR_OK;
}


ADTErr CheckAction(char *_exercise , int _index , Stack *_stack , int *_index2 , char *_postfix)
{
     int item , num;
     
     switch(_exercise[_index])
     {
          case '+':
          case '-':
                    if(!(StackIsEmpty(_stack)))
                    {
                    StackTop(_stack , &item);
                    while( !(StackIsEmpty(_stack)) && item != '(' )
                    {
                         StackPop(_stack , &num);
                         _postfix[*_index2] = num;
                         *_index2 +=1;
                         StackTop(_stack , &item);
                    }
                    }
                    StackPush(_stack , _exercise[_index]);
                    
                    break;
           case '*':
           case '/':
           
                    if(!(StackIsEmpty(_stack)))
                    {                    
                    StackTop(_stack , &item);
                    
                    while( (!(StackIsEmpty(_stack))) && (item != '(') && (item != '+') && (item != '-'))
                    {
                         StackPop(_stack , &num);
                         _postfix[*_index2] = num;
                         *_index2 +=1;
                         StackTop(_stack , &item);

                    }
                    }
                    StackPush(_stack , _exercise[_index]);
                    
                    break;                                            
               
             case '(':
                         StackPush(_stack , _exercise[_index]); 
                         break;
                         
             case ')':
             
                    if(!(StackIsEmpty(_stack)))
                    {               
                    StackTop(_stack , &item);
                    
                    while( !(StackIsEmpty(_stack)) && item != '(' )
                    {
                         StackPop(_stack , &num);
                         _postfix[*_index2] = num;
                         *_index2 +=1;
                         StackTop(_stack , &item);
                    }  
                    if( item == '(')
                    {
                     StackPop(_stack , &num); 
                    }
                    }  
                    break;                                     
             
          default:
               break;
     }
     
     return ERR_OK;
}

ADTErr CheckActionTwo(int _index , char *_postfix , Stack *_stack , int *_result)
{
     int num1 , num2 ;

      switch(_postfix[_index])
      {
          case '+' :
          
             StackPop(_stack , &num1); 
             StackPop(_stack , &num2);
             *_result= (num2-'0') + (num1-'0') ;             
             StackPush(_stack , (*_result+'0')); 
             break;  
             
          case '-' :
                    
             StackPop(_stack , &num1); 
             StackPop(_stack , &num2);
             *_result= (num2-'0') - (num1-'0') ;            
             StackPush(_stack , (*_result+'0')) ;   
             break;                                     
      
          case '*' :
          
             StackPop(_stack , &num1); 
             StackPop(_stack , &num2);
             *_result= (num2-'0') * (num1-'0') ;             
             StackPush(_stack , (*_result+'0')) ; 
             break;                         
          
           case '/' :
           
             StackPop(_stack , &num1); 
             StackPop(_stack , &num2);
             *_result= (num2-'0') / (num1-'0') ;              
             StackPush(_stack , (*_result+'0')) ;     
             break;      
          
          default:
               break;      
      }
     
     return ERR_OK;
}

