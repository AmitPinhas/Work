#include <stdio.h>
#include "generic.h"


#define SIZE_ARRAY 5


/* ------------------------------------------- local func ---------------------------------------- */
static int SmallToBig(void* _left , void* _right);

static int BigToSmall(void* _left , void* _right);

static int EvenFirst(void* _left , void* _right);

static int OddFirst(void* _left , void* _right);

static void PrintArray(int **_array);


int main()
{
     int* array[SIZE_ARRAY] ;   
     int num=1 , num2=43 , num3=1333 , num4=2 , num5=4652 ;
     
	array[0] = &num;
	array[1] = &num2;	
	array[2] = &num3;
	array[3] = &num4;
	array[4] = &num5;
     
     PrintArray(array); 
     
     GBubbleSort(SmallToBig,(void**)&array,SIZE_ARRAY);   
     
     PrintArray(array);        
     
     GBubbleSort(BigToSmall,(void**)&array,SIZE_ARRAY);       

     PrintArray(array);  

     GBubbleSort(EvenFirst,(void**)&array,SIZE_ARRAY);       

     PrintArray(array);   

     GBubbleSort(OddFirst,(void**)&array,SIZE_ARRAY);       

     PrintArray(array);  

     return 1;
}  

/*-----------------------------------------------------------------------------------------*/
static int SmallToBig(void* _left , void* _right)
{
     return (*(int*)_left) > (*(int*)_right) ;
}
/*-----------------------------------------------------------------------------------------*/
static int BigToSmall(void* _left , void* _right)
{
     return (*(int*)_left) < (*(int*)_right) ;
}
/*-----------------------------------------------------------------------------------------*/
static int EvenFirst(void* _left , void* _right)
{
    return ( (*(int*)_left%2 == 1) && (*(int*)_right%2 ==0) );
}
/*-----------------------------------------------------------------------------------------*/
static int OddFirst(void* _left , void* _right)
{
    return ( (*(int*)_left%2 == 0) && (*(int*)_right%2 ==1) );
}
/*-----------------------------------------------------------------------------------------*/
static void PrintArray(int **_array)
{
     int index;

     for ( index = 0 ; index< SIZE_ARRAY ; index++)
     {
          printf("%d " , *_array[index]);
     } 
     putchar('\n'); 
}  
/*-----------------------------------------------------------------------------------------*/  
