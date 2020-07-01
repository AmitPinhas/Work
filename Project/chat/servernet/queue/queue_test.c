#include <stdio.h>
#include <stdlib.h> /* size_t */
#include "../ADTDefs/ADTDefs.h"
#include "queue.h"
#include "queue_test.h"
#define MAGIC_NUMBER 28011993

int QueuePrint(void* _element, size_t _index, void* _context);
int PositiveTestCreat1();
int NegativeTestCreat1();
int NegativeTestCreat2();
int NegativeTestDestroy1();
int NegativeTestDestroy2();
int PositiveTestInsert1();
int NegativeTestInsert1();
int NegativeTestInsert2();
int PositiveTestRemove1();
int NegativeTestRemove1();
int NegativeTestRemove2();
int NegativeTestRemove3();
int PositiveTestEmpty1();
int PositiveTestEmpty2();
int NegativeTestEmpty1();
int printQueue();

int main()
{
     PositiveTestCreat1();
     NegativeTestCreat1();
     NegativeTestCreat2();
     putchar('\n');
     NegativeTestDestroy1();
     NegativeTestDestroy2();  
     putchar('\n');        
     PositiveTestInsert1(); 
     NegativeTestInsert1();
     NegativeTestInsert2(); 
     putchar('\n');
     PositiveTestRemove1();
     NegativeTestRemove1();
     NegativeTestRemove2();
     NegativeTestRemove3();
     putchar('\n');  
     PositiveTestEmpty1(); 
     PositiveTestEmpty2();  
     NegativeTestEmpty1(); 
     putchar('\n');
     printQueue();
     putchar('\n');
               
     return 1;
}

int PositiveTestCreat1()
{
    size_t size_1=4 , size , numElement , head , tail ;
    Queue *ptr ;
    int magic;
    
     /*  size>0  */
     
     if ((ptr=QueueCreate(size_1)) != NULL)
     {
          GetSizeQueue(ptr , &size);
          GetHead(ptr , &head);
          GetTail(ptr , &tail);
          GetNumOfItems(ptr , &numElement);
          GetMagic(ptr , &magic);
          if( (size == size_1) && (head == 0) && (tail == 0) && (numElement == 0) && (magic==MAGIC_NUMBER) )
          {
          printf("pos test creat 1 PASS\n");
          QueueDestroy(ptr , NULL);
          }
     }
     else
     {
          printf("pos test creat 1 FAILED\n");
     }
      
     return ERR_OK;  
}

int NegativeTestCreat1()
{
    Queue *ptr ;
    
    /* size = 0 */
    
     if((ptr=QueueCreate(0)) == NULL) 
     {
        printf("neg test creat 1 PASS\n");  
     }
     else
     {
        printf("neg test creat 1 FAILED\n");
     }             
     
     return ERR_OK;
}
int NegativeTestCreat2()
{
    Queue *ptr ;
    
    /* size = -1 , allocation failed */
    
     if((ptr=QueueCreate(-1)) == NULL) 
     {
        printf("neg test creat 2 PASS\n");  
     }
     else
     {
        printf("neg test creat 2 FAILED\n");
     }             
     
     return ERR_OK;
}

int NegativeTestDestroy1()
{
    /*  ptr queue = NULL */ 
    QueueDestroy(NULL , NULL);
    printf("neg test destroy 1 PASS\n");
    
    return ERR_OK;
}

int NegativeTestDestroy2()
{
     Queue *ptr;
     
     /* double free */ 
     if ((ptr=QueueCreate(1)) != NULL)
     {
          QueueDestroy(ptr , NULL);
          QueueDestroy(ptr , NULL);          
          printf("neg test destroy 2 PASS\n");
     }     
     
     return ERR_OK;
}

int PositiveTestInsert1()
{
     Queue *ptr;
     ADTErr result;
     int num5=5;
     
     /* size = 1 , num items = 0 */
     ptr=QueueCreate(1);
     
     if( (result=QueueInsert(ptr , &num5)) == ERR_OK)
     {
        printf("pos test insert 1 PASS\n");  
     }
     else
     {
        printf("pos test insert 1 FAILED\n");    
     }
     
     QueueDestroy(ptr , NULL);
     return ERR_OK;
}

int NegativeTestInsert1()
{
     Queue *ptr;
     ADTErr result;
     int num5=5;
     
     /* size = 1 , num items = 1 , check overflow */
     ptr=QueueCreate(1);
     QueueInsert(ptr , &num5);
     
     if( (result=QueueInsert(ptr , &num5)) == ERR_OVERFLOW)
     {
        printf("neg test insert 1 PASS\n");  
     }
     else
     {
        printf("neg test insert 1 FAILED\n");    
     }
     
     QueueDestroy(ptr , NULL);
     return ERR_OK;
}

int NegativeTestInsert2()
{
     ADTErr result;
     int num5=5;
     
     /* pointer null  */
     
     if( (result=QueueInsert(NULL , &num5)) == ERR_NOT_INITIALIZED)
     {
        printf("neg test insert 2 PASS\n");  
     }
     else
     {
        printf("neg test insert 2 FAILED\n");    
     }
     
     return ERR_OK;
}

int PositiveTestRemove1()
{
     Queue *ptr;
     ADTErr result;
     int *item , num5=5;
     
     /* num of item = 1 */
     ptr=QueueCreate(1);
     QueueInsert(ptr , &num5);
     
     if( (result=QueueRemove(ptr , (void**)&item)) == ERR_OK && *item == 5)
     {
        printf("pos test remove 1 PASS\n");  
     }
     else
     {
        printf("pos test remove 1 FAILED\n");    
     }
     
     QueueDestroy(ptr , NULL);
     return ERR_OK;
}
int NegativeTestRemove1()
{
     Queue *ptr;
     ADTErr result;
     int *item;
     
     /* queue is empty */
     ptr=QueueCreate(1);
     
     if( (result=QueueRemove(ptr , (void**)&item)) == ERR_UNDERFLOW )
     {
        printf("neg test remove 1 PASS\n");  
     }
     else
     {
        printf("neg test remove 1 FAILED\n");    
     }
     
     QueueDestroy(ptr , NULL);
     return ERR_OK;
}
int NegativeTestRemove2()
{
     Queue *ptr;
     ADTErr result;
     
     /* int pointer null */
     ptr=QueueCreate(1);
     
     if( (result=QueueRemove(ptr , NULL)) == ERR_NOT_INITIALIZED )
     {
        printf("neg test remove 2 PASS\n");  
     }
     else
     {
        printf("neg test remove 2 FAILED\n");    
     }
     
     QueueDestroy(ptr , NULL);
     return ERR_OK;
}
int NegativeTestRemove3()
{
     int *item;
     ADTErr result;
     
     /* queue pointer null */
     
     if( (result=QueueRemove(NULL , (void**)&item)) == ERR_NOT_INITIALIZED )
     {
        printf("neg test remove 3 PASS\n");  
     }
     else
     {
        printf("neg test remove 3 FAILED\n");    
     }
     
     return ERR_OK;
}

int PositiveTestEmpty1()
{
     Queue *ptr;
     int result;
     
     /* queue empty */
     
     ptr=QueueCreate(1);
     
     if( (result=QueueIsEmpty(ptr)) == TRUE)
     {
        printf("pos test empty 1 PASS\n");  
     }
     else
     {
        printf("pos test empty 1 FAILED\n");
     }
     
     QueueDestroy(ptr , NULL);
     return ERR_OK;     
}
int PositiveTestEmpty2()
{
     Queue *ptr;
     int result , num5;
     
     /* queue not empty */
     
     ptr=QueueCreate(1);
     QueueInsert(ptr , &num5);
     
     if( (result=QueueIsEmpty(ptr)) == FALSE)
     {
        printf("pos test empty 2 PASS\n");  
     }
     else
     {
        printf("pos test empty 2 FAILED\n");
     }
     
     QueueDestroy(ptr , NULL);
     return ERR_OK;    
}
int NegativeTestEmpty1()
{
     int result;
     
     /* pointer null */
     
     if( (result=QueueIsEmpty(NULL)) == TRUE)
     {
        printf("neg test empty 1 PASS\n");  
     }
     else
     {
        printf("neg test empty 1 FAILED\n");
     }
     
     return ERR_OK;    
}

int printQueue()
{
	Queue *queue;
	int num4=4 , num6=6 , num2=2 , num8=8 , num9=9;
	queue = QueueCreate (5);
	QueueInsert(queue , &num4);
	QueueInsert(queue , &num6);
	QueueInsert(queue , &num2);
	QueueInsert(queue , &num8);
	QueueInsert(queue , &num9);				
	putchar('\n');
	QueueForEach(queue, QueuePrint , NULL);
	putchar('\n');	
	QueueDestroy(queue , NULL);
	return 0;
}


int QueuePrint(void* _element, size_t _index, void* _context)
{
    printf("%d " ,  (*((int*)_element)) ); 
    
    return 1; 
}

