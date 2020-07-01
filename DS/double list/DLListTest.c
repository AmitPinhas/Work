#include <stdio.h>
#include "DLList.h"
#include "list_itr.h"

/* ------------------------------------------------------- List Create -------------------------------------------------------------------------- */
void PositiveCreat();
void DestroyNull();
void DestroyDoubleFree();
void PositivePushHead1();
void PositivePushHead2();
void PushHeadNull();
void PositivePushTail1();
void PositivePushTail2();
void PushTailNull();
void PositivePophHead1();
void PositivePophHead2();
void PophHeadNull();
void PositivePophTail1();
void PositivePophTail2();
void PophTailNull();
void PositiveCount1();
void PositiveCount2();
void PositiveCount3();
void CountNull();
void PositiveEmpty1();
void PositiveEmpty2();
void EmptyNull();
void PositiveITRRemove();
void PositiveITRSet();

static char pass[]="pass";
static char failed[]="failed";

int main()
{
	printf("------------------------\n");
	printf("List Create :\n\n");
     PositiveCreat();
	printf("------------------------\n");     
	printf("List Destroy :\n\n");     
     DestroyNull();
     DestroyDoubleFree();
	printf("------------------------\n");     
	printf("List Push Head :\n\n");        
     PositivePushHead1();
     PositivePushHead2();
     PushHeadNull();
	printf("------------------------\n");        
	printf("List Push Tail :\n\n");       
     PositivePushTail1();
     PositivePushTail2();
     PushTailNull();
	printf("------------------------\n");        
	printf("List Pop Head :\n\n");       
     PositivePophHead1();
     PositivePophHead2();
     PophHeadNull();
	printf("------------------------\n");        
	printf("List Pop Tail :\n\n");     
     PositivePophTail1();
     PositivePophTail2();
     PophTailNull();
	printf("------------------------\n");        
	printf("List Size :\n\n");      
     PositiveCount1();
     PositiveCount2();
     PositiveCount3();
     CountNull();
	printf("------------------------\n");  
	printf("List Itr func :\n\n");       
	PositiveITRRemove();
	PositiveITRSet();
	
     return 1;
}

void PositiveCreat()
{
     List *ptrList;
     
     ptrList = ListCreate();
     
     if ( ptrList != NULL )
     {
          puts(pass);
     }
     else
     {
          puts(failed);   
     }
     
    ListDestroy(&ptrList , NULL); 
}

void DestroyNull()
{
     ListDestroy(NULL , NULL);
     puts(pass);
}

void DestroyDoubleFree()
{
     List *ptrList;     
     ptrList = ListCreate();
     ListDestroy(&ptrList , NULL); 
     ListDestroy(&ptrList, NULL); 
     puts(pass);     
}

void PositivePushHead1()
{
     List *ptrList;
     ListItr first ;
     int *data;
     int num=5;
     
     ptrList = ListCreate();   
     
     ListPushHead(ptrList , &num);  
     
     first = ListItrBegin(ptrList);
     
     data = ListItrGet(first);
     
     if ( 5 == *data )
     {
         puts(pass); 
     }
     else
     {
        puts(failed);   
     }     
     ListDestroy(&ptrList, NULL); 
}

void PositivePushHead2()
{ 
     List *ptrList;
     ListItr first ;
     ListItr next ;
     int *data1 ,*data2;
     int num1=5 , num2=4;
     
     ptrList = ListCreate();   
     
     ListPushHead(ptrList , &num1);  
     ListPushHead(ptrList , &num2);      
     first = ListItrBegin(ptrList);  
     next = ListItrNext(first);   
     data1 = ListItrGet(first);
     data2 = ListItrGet(next);    
     if ( 4 == *data1 && 5 == *data2 )
     {
         puts(pass); 
     }
     else
     {
        puts(failed);   
     }     
     ListDestroy(&ptrList, NULL); 
}

void PushHeadNull()
{
     ListResult result ;
     int num=5;
     
    if ( (result = ListPushHead(NULL , &num)) == LIST_UNINITIALIZED_ERROR )
    {
      puts(pass); 
    }
    else
    {
     puts(failed);   
    }     
}

void PositivePushTail1()
{
     List *ptrList;
     ListItr last ;
     int *data;
     int num=5;
     
     ptrList = ListCreate();   
     
     ListPushTail(ptrList , &num);  
     
     last = ListItrEnd(ptrList);
     last = ListItrPrev(last); 
          
     data = ListItrGet(last);
     
     if ( 5 == *data )
     {
         puts(pass); 
     }
     else
     {
        puts(failed);   
     }     
     ListDestroy(&ptrList, NULL); 
}

void PositivePushTail2()
{
     List *ptrList;
     ListItr last ;
     ListItr prev ;
     ListItr prev2 ;     
     int *data1 ,*data2;
     int num1=5 , num2=4;
     
     ptrList = ListCreate();   
     ListPushTail(ptrList , &num1);  
     ListPushTail(ptrList , &num2);      
     last = ListItrEnd(ptrList);
     prev = ListItrPrev(last);    
     prev2 = ListItrPrev(prev);   
     data1 = ListItrGet(prev);
     data2 = ListItrGet(prev2);    
     if ( 4 == *data1 && 5 == *data2 )
     {
         puts(pass); 
     }
     else
     {
        puts(failed);   
     }     
     ListDestroy(&ptrList, NULL); 
}

void PushTailNull()
{
     ListResult result ;
     int num=5;
     
    if ( (result = ListPushTail(NULL , &num)) == LIST_UNINITIALIZED_ERROR )
    {
      puts(pass); 
    }
    else
    {
     puts(failed);   
    } 
}

void PositivePophHead1()
{
     List *ptrList;
     int *data;
     int num=5;
     
     ptrList = ListCreate();   
     
     ListPushHead(ptrList , &num);  
     ListPopHead(ptrList ,(void**)&data);
     
     if ( 5 == *data )
     {
         puts(pass); 
     }
     else
     {
        puts(failed);   
     }     
     ListDestroy(&ptrList, NULL); 
}

void PositivePophHead2()
{
     List *ptrList;
     int *data;
     int num=5 , num2=4;
     
     ptrList = ListCreate();   
     
     ListPushHead(ptrList , &num);  
     ListPushHead(ptrList , &num2);     
     ListPopHead(ptrList ,(void**)&data);
     
     if ( 4 == *data )
     {
         puts(pass); 
     }
     else
     {
        puts(failed);   
     }     
     ListDestroy(&ptrList, NULL); 
}

void PophHeadNull()
{
     int *data;
     ListResult result ;
     
     if( (result=ListPopHead(NULL ,(void**)&data)) == LIST_UNINITIALIZED_ERROR) 
     {
         puts(pass); 
     }
     else
     {
        puts(failed);   
     }               
}

void PositivePophTail1()
{
     List *ptrList;
     int *data;
     int num=5;
     
     ptrList = ListCreate();   
     
     ListPushTail(ptrList , &num);  
     ListPopTail(ptrList ,(void**)&data);
     
     if ( 5 == *data )
     {
         puts(pass); 
     }
     else
     {
        puts(failed);   
     }     
     ListDestroy(&ptrList, NULL); 
}
void PositivePophTail2()
{
     List *ptrList;
     int *data;
     int num=5 , num2=4;
     
     ptrList = ListCreate();   
     
     ListPushTail(ptrList , &num);  
     ListPushTail(ptrList , &num2);     
     ListPopTail(ptrList ,(void**)&data);
     
     if ( 4 == *data )
     {
         puts(pass); 
     }
     else
     {
        puts(failed);   
     }     
     ListDestroy(&ptrList, NULL); 
}
void PophTailNull()
{
     int *data;
     ListResult result ;
     
     if( (result=ListPopTail(NULL ,(void**)&data)) == LIST_UNINITIALIZED_ERROR) 
     {
         puts(pass); 
     }
     else
     {
        puts(failed);   
     }   
}

void PositiveCount1()
{
     size_t size;
     List *ptrList;
     int num=5;
     
     ptrList = ListCreate();  
     ListPushTail(ptrList , &num); 
     
     size = ListSize(ptrList);
     
     if ( size == 1 )
     {
       puts(pass);    
     }  
     else
     {
       puts(failed); 
     } 
     ListDestroy(&ptrList, NULL);         
}
void PositiveCount2()
{
     size_t size;
     List *ptrList;
     int num=5 , num2=5;
     
     ptrList = ListCreate();  
     ListPushTail(ptrList , &num); 
     ListPushTail(ptrList , &num2); 
          
     size = ListSize(ptrList);
     
     if ( size == 2 )
     {
       puts(pass);    
     }  
     else
     {
       puts(failed); 
     } 
     ListDestroy(&ptrList, NULL); 
}
void PositiveCount3()
{
     size_t size;
     List *ptrList;
     
     ptrList = ListCreate();  
          
     size = ListSize(ptrList);
     
     if ( size == 0 )
     {
       puts(pass);    
     }  
     else
     {
       puts(failed); 
     } 
     ListDestroy(&ptrList, NULL); 
}

void CountNull()
{
     size_t size;
     size = ListSize(NULL);
     
     if ( size == 0 )
     {
       puts(pass);    
     }  
     else
     {
       puts(failed); 
     }      
}

void PositiveITRRemove()
{
     List *ptrList;	
     int num1=5 , num2=4;
     ListItr begin;
     int *dataFirst , *dataFirst2;
     
     ptrList = ListCreate();   
     
     ListPushHead(ptrList , &num1);  
     ListPushHead(ptrList , &num2); 
     
     begin = ListItrBegin(ptrList);
           
     dataFirst = ListItrRemove(begin);
     begin = ListItrBegin(ptrList);
     dataFirst2 = ListItrGet(begin);
     
     if ( (*dataFirst == 4) && (*dataFirst2 == 5) )
     {
     	puts(pass);
     }
     else
     {
     	puts(failed);
     }
     
     ListDestroy(&ptrList, NULL); 
}

void PositiveITRSet()
{
     List *ptrList;
     int num1=5, num2=1 , *numold , *numnew;     
     ListItr begin;
          
     ptrList = ListCreate();   
     
     ListPushHead(ptrList , &num1);  
     
     begin = ListItrBegin(ptrList);
     
     numold = ListItrSet(begin, &num2);  
     
     begin = ListItrBegin(ptrList);
     
     numnew = ListItrGet(begin); 
     
     if (  (*numold == 5) && ( *numnew ==  1) )
     {
     	puts(pass);
     }               
     else
     {
     	puts(failed);
     } 
     
     ListDestroy(&ptrList, NULL);      		
}



