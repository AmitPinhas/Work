#include <stdio.h>
#include "ADTDefs.h"
#include "pointerFunc.h"

#define SIZE_ARRAY 30

static int SmallToBig(int _left , int _right)
{
     return _left > _right ;
}

static int BigToSmall(int _left , int _right)
{
     return _left < _right ;
}

static int EvenFirst(int _left , int _right)
{
    return ( (_left%2 == 1) && (_right%2 ==0) );
}

static int OddFirst(int _left , int _right)
{
    return ( (_left%2 == 0) && (_right%2 ==1) );
}

static void PrintArray(int *_array)
{
     int index;

     for ( index = 0 ; index< SIZE_ARRAY ; index++)
     {
          printf("%d " , _array[index]);
     } 
     putchar('\n'); 
}


int main()
{
     int array[SIZE_ARRAY] ;   
     int index , index2;
     
     for(index=SIZE_ARRAY , index2=0 ; index2<SIZE_ARRAY ; index-- , index2++)
     {
       array[index2] = index;
     }
     
     PrintArray(array); 
     
     BubbleSort(SmallToBig,array,SIZE_ARRAY);   
     
     PrintArray(array);        
     
     BubbleSort(BigToSmall,array,SIZE_ARRAY);       

     PrintArray(array);  

     BubbleSort(EvenFirst,array,SIZE_ARRAY);       

     PrintArray(array);   

     BubbleSort(OddFirst,array,SIZE_ARRAY);       

     PrintArray(array);  

     return 1;
}  
         
