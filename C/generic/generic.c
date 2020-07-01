#include <stdio.h> /* NULL */
#include "generic.h"

#define SWAP(x,y,t)     \
        {               \
          t temp = x ;  \
          x = y ;       \
          y = temp ;    \
        }

int GBubbleSort(CompareFunc _less ,  void* _array[] , size_t _arrSize)
{
    register int  index , change=1 ;
    
    if ( NULL == _less || NULL == _array )
    {
      return FALSE;
    }
         
    while(change)
    {
       for(index = 0 , change=0 ; index+1 < _arrSize ; index++ )
       {
          if( _less(_array[index] ,_array[index+1] ) )
          {
              SWAP(_array[index] ,_array[index+1] ,void* );
              change=1;
          }
       }              
       _arrSize -- ; 
    }
    
    return TRUE;
}
