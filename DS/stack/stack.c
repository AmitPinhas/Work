#include <stdio.h>
#include <stdlib.h> /* size_t , memory allocation */
#include "../ADTDefs/ADTDefs.h"
#include "../vector/vector.h"
#include "stack.h"
#include "stack_test.h"
#define MAGIC_NUMBER 28011993
#define TRUE 1
#define FALSE 0

struct Stack
{
     Vector *m_vector;
     int m_magicNum;
};   

Stack* StackCreate(size_t _size , size_t _blockSize)
{
     Stack *ptrStack;
     
     ptrStack = (Stack*)malloc(sizeof(Stack));    
     if ( NULL == ptrStack)
     {
          return NULL;
     } 
     
     ptrStack->m_vector = VectorCreate(_size, _blockSize);       
     if( NULL == ptrStack->m_vector)
     {
          free(ptrStack);
          return NULL;
     }       

     ptrStack->m_magicNum = MAGIC_NUMBER;     
     return ptrStack;     
}

void StackDestroy(Stack *_stack)
{
     if(_stack != NULL && _stack->m_magicNum == MAGIC_NUMBER)
     {          
       _stack->m_magicNum =0;   
       VectorDestroy(_stack->m_vector);   
       free(_stack);
     }     
}

ADTErr StackPush(Stack *_stack , int _item)
{      
     if( NULL == _stack)
     {
         return ERR_NOT_INITIALIZED;
     }
     
    return VectorAdd (_stack->m_vector ,_item);  
}

ADTErr StackPop(Stack *_stack , int *_item)
{     
     if( NULL == _stack || NULL == _item)
     {
         return ERR_NOT_INITIALIZED;
     }   
        
    return VectorDelete(_stack->m_vector ,_item); 
}

ADTErr StackTop(Stack *_stack , int *_item)
{
     int numElement;
     
     if( NULL == _stack || NULL == _item)
     {
         return ERR_NOT_INITIALIZED;
     } 
     
   VectorItemsNum(_stack->m_vector , &numElement) ;
   
    if( 0 == numElement)
    {
     return STACK_EMPTY;
    }

    return VectorGet(_stack->m_vector, numElement-1 ,_item); 
}

void GetMagicStack(Stack *_stack , int *_m_magicNum)
{
     *_m_magicNum = _stack->m_magicNum;
}

int StackIsEmpty(Stack *_stack)
{
     int numElement;     
     
     if(NULL == _stack)
     {
          return TRUE;
     }
     
     VectorItemsNum(_stack->m_vector , &numElement);
     
     if( numElement > 0)
     {
          return FALSE;
     }
     else
     {
          return TRUE;
     }
}

void StackPrint(Stack *_stack)
{
     VectorPrint(_stack->m_vector);
}

void StackItemsNum(Stack *_stack , int* _numOfItems)
{
      VectorItemsNum(_stack->m_vector , _numOfItems);
}


