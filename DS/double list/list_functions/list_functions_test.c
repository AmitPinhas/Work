#include <stdio.h>
#include "list_functions.h"

static int SmallToBig(void* _left , void* _right);

int main()
{
     List *ptrList;
     int num1=47, num2=1, num3=98 , num4=6  ;
     ListItr begin , begin2 , begin3 , begin4 , end;
     int *data1 , *data2 , *data3 , *data4;
         
     ptrList = ListCreate(); 
     
     ListPushHead(ptrList , &num1);
     ListPushHead(ptrList , &num2);
     ListPushHead(ptrList , &num3);
     ListPushHead(ptrList , &num4);
     
     begin = ListItrBegin(ptrList);
     end = ListItrEnd(ptrList);

     ListItrBubbleSort(begin, end, SmallToBig);
     
     begin = ListItrBegin(ptrList);  
     
     data1 = ListItrGet(begin);  
     
     begin2 = ListItrNext(begin);
 
     data2 = ListItrGet(begin2);  

     begin3 = ListItrNext(begin2);

     data3 = ListItrGet(begin3);  

     begin4 = ListItrNext(begin3);

     data4 = ListItrGet(begin4); 

    printf("%d ", *data1);
    printf("%d ", *data2);     
    printf("%d ", *data3);
    printf("%d ", *data4);
    putchar('\n');

     ListDestroy(&ptrList, NULL); 
                        
	return 1;
}


/*-----------------------------------------------------------------------------------------*/
static int SmallToBig(void* _left , void* _right)
{
     return (*(int*)_left) > (*(int*)_right) ;
}
