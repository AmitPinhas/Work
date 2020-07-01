#include <stdio.h> /* NULL */
#include "ADTDefs.h"
#include "pointerFunc.h"

#define SWAP(x,y,t)     \
        {               \
          t temp = x ;  \
          x = y ;       \
          y = temp ;    \
        }

ADTErr BubbleSort(SortingType _func , int *_array , size_t _arrSize)
{
    register int  index ;
    register int  index2 ;
    register int  change=1 ;
    
    if ( NULL == _func || NULL == _array )
    {
      return ERR_NOT_INITIALIZED;
    }
    
     
     while(change)
     {
       for(index = 0 , index2 = index+1 , change=0; index2 < _arrSize ; index++ , index2++)
       {
          if(_func(_array[index],_array[index2]))
          {
              SWAP(_array[index],_array[index2],int);
              change=1;
          }
       }        
       _arrSize -- ; 
     }
     return ERR_OK;
}
