#include <time.h>
#include <stdio.h>

#define SWAP(x,y,t)     \
        {               \
          t temp = x ;  \
          x = y ;       \
          y = temp ;    \
        }
#define SIZE_ARRAY 100       

void Swap(int *_a , int *_b);

int SortByFunc(int *_array)
{
    int index ;
    int  index2 ;
    int  change=1;
     
     while(change)
     {
     for(index = 0 , index2 = index+1 , change=0; index2 < SIZE_ARRAY ; index++ , index2++)
     {
          if(_array[index] > _array[index2])
          {
             Swap(&_array[index] , &_array[index2]);
               change=1;
          }
     }   
     }
     return 1;
}

int SortByMacro(int *_array)
{
    register int index ;
    register int  index2 ;
    register int  change=1;
    int size=SIZE_ARRAY ;

     while(change)
     {
     for(index = 0 , index2 = index+1 , change=0; index2 < size ; index++ , index2++)
     {
          if(_array[index] > _array[index2])
          {
              SWAP(_array[index],_array[index2],int);
               change=1;
          }
     }  
     size-- ; 
     }
     return 1;
}

void Swap(int *_a , int *_b)
{
     int temp ;
     temp = *_a;
     *_a = *_b;
     *_b = temp;
}

int main()
{
     int array[SIZE_ARRAY] ,array2[SIZE_ARRAY];
     int index , index2;
     clock_t start_t, end_t, total_t;
     
     for(index=SIZE_ARRAY , index2=0 ; index2<SIZE_ARRAY ; index-- , index2++)
     {
       array[index2] = index;
     }
     start_t = clock();

     SortByMacro(array);  
 
     putchar('\n');         
     for(index=0 ; index<SIZE_ARRAY ; index++ )
     {
       printf("%d ",array[index]);
     }     
     putchar('\n');    
     
     end_t = clock();
     total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC ;
     printf("Starting of the program, total_t macro = %ld\n", total_t);
     
     for(index=SIZE_ARRAY ,  index2=0 ; index2<SIZE_ARRAY ; index-- , index2++)
     {
       array2[index2] = index;
     }
     
     start_t = clock();    
     SortByFunc(array2);
     end_t = clock();
     total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC ;
     printf("Starting of the program, total_t func = %ld\n", total_t);
     return 1;
}        
