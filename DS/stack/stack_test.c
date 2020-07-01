#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "ADTDefs.h"
#include "stack.h"
#include "stack_test.h"

#define MAGIC_NUMBER 28011993

int PositiveTestCreat1();
int PositiveTestCreat2();
int PositiveTestCreat3();
int NegativeTestCreat1();
int NegativeTestCreat2();
int NegativeTestDestroy1();
int NegativeTestDestroy2();
int PositiveTestPush1();
int PositiveTestPush2();
int NegativeTestPush1();
int NegativeTestPush2();
int NegativeTestPush3();
int PositiveTestPop1();
int NegativeTestPop1();
int NegativeTestPop2();
int PositiveTestTop1();
int NegativeTestTop1();
int NegativeTestTop2();
int NegativeTestTop3();
int NegativeTestTop4();
int PositiveTestEmpty1();
int PositiveTestEmpty2();
int NegativeTestEmpty1();


int main()
{
     
     PositiveTestCreat1();
     PositiveTestCreat2();
     PositiveTestCreat3();
     NegativeTestCreat1();
     NegativeTestCreat2();
     putchar('\n');
     NegativeTestDestroy1();
     NegativeTestDestroy2();
     putchar('\n');
     PositiveTestPush1();
     PositiveTestPush2();
     NegativeTestPush1();
     NegativeTestPush2();
     NegativeTestPush3();
     putchar('\n'); 
     PositiveTestPop1();
     NegativeTestPop1();
     NegativeTestPop2(); 
     putchar('\n');
     PositiveTestTop1();
     NegativeTestTop1();
     NegativeTestTop2();
     NegativeTestTop3();
     NegativeTestTop4();                  
     putchar('\n');
     PositiveTestEmpty1();
     PositiveTestEmpty2(); 
     NegativeTestEmpty1();
     putchar('\n');
             
     return 0;
}

int PositiveTestCreat1()
{
    size_t size_1=4 , blocksize_1=3 , original_size , size , block;
    Stack *ptr1=NULL ;
    int magic;
    
     /* test 1 : size>0 , blocksize>0 */
     
     if ((ptr1=StackCreate(size_1 , blocksize_1)) != NULL)
     {
          GetMagicStack(ptr1 , &magic);
          if(magic == MAGIC_NUMBER)
          {
          printf("pos test creat 1 PASS\n");
          }
          else
          {
               printf("pos test creat 1 FAILED\n");
          }
     }
     else
     {
          printf("pos test creat 1 FAILED\n");
     }
     
     StackDestroy(ptr1);
      
     return ERR_OK;  
}

int PositiveTestCreat2()
{
    size_t size_2=0 , blocksize_2=5;
    Stack *ptr2=NULL;
    
     /* test 2 : size=0 , blocksize>0 */
     
     if ((ptr2=StackCreate(size_2 , blocksize_2)) != NULL)
     {
          printf("pos test creat 2 PASS\n");
     }
     else
     {
          printf("pos test creat 2 FAILED\n");
     } 
     
     StackDestroy(ptr2);
     
     return ERR_OK;     
}
int PositiveTestCreat3()
{
     size_t size_3=6 , blocksize_3=0;
     Stack  *ptr3=NULL;
     
     /* test 3 : size>0 , blocksize=0 */
     
     if ((ptr3=StackCreate(size_3 , blocksize_3)) != NULL)
     {
          printf("pos test creat 3 PASS\n");
     }
     else
     {
          printf("pos test creat 3 FAILED\n");
     }
     
     StackDestroy(ptr3);       
     return ERR_OK;   
}

int NegativeTestCreat1()
{
     size_t size_1=0 , blocksize_1=0;
     Stack *ptr1=NULL ;
         
     /* test 1 : size=0 , blocksize=0 */
     
     if ((ptr1=StackCreate(size_1 , blocksize_1)) == NULL)
     {
          printf("neg test creat 1 PASS\n");
     }
     else
     {
          printf("neg test creat 1 FAILED\n");
     }
     
     StackDestroy(ptr1);     
     return ERR_OK;
}

int NegativeTestCreat2()
{
     size_t size_2=-1 , blocksize_2=4;
     Stack *ptr2=NULL ;
     
     
     /* test 2 : size=-1 , blocksize>0 */
     
     if ((ptr2=StackCreate(size_2 , blocksize_2)) == NULL)
     {
          printf("neg test creat 2 PASS\n");
     }
     else
     {
          printf("neg test creat 2 FAILED\n");         
     }
     
     StackDestroy(ptr2);
     return ERR_OK;
}


int NegativeTestDestroy1()
{
    /* test 1 : ptr vector = NULL */ 
    StackDestroy(NULL);
    printf("neg test destroy 1 PASS\n");
    
    return ERR_OK;
}

int NegativeTestDestroy2()
{
     Stack *ptr1 ;
     
     /* double destroy */ 
     if ((ptr1=StackCreate(1 ,1)) != NULL)
     {
          StackDestroy(ptr1);
          StackDestroy(ptr1);
          printf("neg test destroy 2 PASS\n");
     }     
     
     return ERR_OK;
}

int PositiveTestPush1()
{
     Stack *ptr1=NULL ;
     ADTErr result;
     int numElement , item;

     /* test 1 : add without realloc */ 
     ptr1=StackCreate(2 , 2);
     if((result=StackPush (ptr1 ,5)) == ERR_OK)
     {
          StackTop(ptr1 , &item);
          if(item == 5)
          {
          printf("pos test push 1 PASS\n");
          }
          else
          {
            printf("pos test push 1 FAILED\n"); 
          }
     }         
     else
     {
     printf("pos test push 1 FAILED\n");       
     }    
     
     StackDestroy(ptr1);
     return ERR_OK; 
}
int PositiveTestPush2()
{
     Stack *ptr2=NULL ;
     ADTErr result;
     int numElement;

     /* test 2 : add with realloc */ 
     ptr2=StackCreate(0 , 2);
     if((result=StackPush (ptr2 ,5)) == ERR_OK)
     {
          StackItemsNum(ptr2 , &numElement);
          if(numElement == 1)
          {
          printf("pos test push 2 PASS\n");       
          }
          else
          {
          printf("pos test push 2 FAILED\n");          
          }
     }
     else
     {
     printf("pos test push 2 FAILED\n");       
     }    
     
     StackDestroy(ptr2); 
     return ERR_OK;  

}
int NegativeTestPush1()
{
     ADTErr result;
     
     /* stack = NULL */
     if((result=StackPush (NULL ,5)) == ERR_NOT_INITIALIZED) 
     {
          printf("neg test push 1 PASS\n");          
     }
     else
     {
          printf("neg test push 1 FAILED\n");        
     }
     
     return ERR_OK;
}
int NegativeTestPush2()
{
     Stack *ptr2 ;
     ADTErr result;

     /* test 2 : overflow */ 
     ptr2=StackCreate(1 , 0);
     StackPush (ptr2 ,5);
     if((result=StackPush (ptr2 ,6)) == ERR_OVERFLOW)
     {
          printf("neg test push 2 PASS\n");          
     }
     else
     {
     printf("neg test push 2 FAILED\n");       
     }    
     
     StackDestroy(ptr2);
     return ERR_OK; 
}
int NegativeTestPush3()
{
     Stack *ptr3 ;
     ADTErr result;

     /* test 2 : realloc failed */ 
     ptr3=StackCreate(0 , -1);
     if((result=StackPush (ptr3 ,6)) == ERR_REALLOCATION_FAILED)
     {
          printf("neg test push 3 PASS\n");          
     }
     else
     {
     printf("neg test push 3 FAILED\n");       
     }    
     
     StackDestroy(ptr3); 
     return ERR_OK;  
}

int PositiveTestPop1()
{
     Stack *ptr1 ;
     ADTErr result;
     int num , numElement;

     /* test 1 : delete without realloc */ 
     ptr1=StackCreate(1 , 2);
     StackPush (ptr1 ,5);
     if((result=StackPop (ptr1 ,&num)) == ERR_OK)
     {
          StackItemsNum(ptr1 , &numElement);
          if(num == 5 && numElement == 0)
          {
          printf("pos test pop 1 PASS\n");         
          }
          else
          {
          printf("pos test pop 1 FAILED\n");          
          }
     }
     else
     {
     printf("pos test pop 1 FAILED\n");      
     }    
     
     StackDestroy(ptr1);
     return ERR_OK;
}

int NegativeTestPop1()
{
     Stack *ptr1 ;
     ADTErr result;
     int num;

     /* test 1 : num of element = 0  */ 
     ptr1=StackCreate(1 , 2);
     if((result=StackPop (ptr1 ,&num)) == ERR_UNDERFLOW)
     {
          printf("neg test pop 1 PASS\n");      
     }
     else
     {
     printf("neg test pop 1 FAILED\n");           
     }    
    
     StackDestroy(ptr1);   
     return ERR_OK;
}
int NegativeTestPop2()
{
     ADTErr result;
     int num;

     /* test 1 : ptr NULL */ 
     if((result=StackPop (NULL ,&num)) == ERR_NOT_INITIALIZED)
     {
       printf("neg test pop 2 PASS\n");
     }
     else
     {
       printf("neg test pop 2 FAILED\n");       
     }    
    
     return ERR_OK;
}

int PositiveTestTop1()
{
     int item;
     Stack *ptr;
     ADTErr result;
     
     ptr=StackCreate(1 , 2);
     StackPush(ptr ,2);
     
     if((result=StackTop(ptr,&item)) == ERR_OK)
     {
          if(item == 2)
          {
               printf("pos test top 1 PASS\n");
          }
          else
          {
               printf("pos test top 1 FAILED\n");              
          }
     }
     else
     {
        printf("pos test top 1 FAILED\n");          
     }          
     
     StackDestroy(ptr);
     return ERR_OK;
}
int NegativeTestTop1()
{
     int item;
     ADTErr result;
     
     /* ptr stack = null */
     if((result=StackTop(NULL ,&item)) == ERR_NOT_INITIALIZED)
     {
        printf("neg test top 1 PASS\n");
     }
     else
     {
        printf("neg test top 1 FAILED\n");  
     }          
     
     return ERR_OK;
}
int NegativeTestTop2()
{
     Stack *ptr;
     ADTErr result;
     
     /* ptr item = null */
     ptr=StackCreate(1 , 2);
     StackPush(ptr ,2);
     
     if((result=StackTop(ptr ,NULL)) == ERR_NOT_INITIALIZED)
     {
        printf("neg test top 2 PASS\n");
     }
     else
     {
        printf("neg test top 2 FAILED\n");          
     }          
     
     StackDestroy(ptr);
     return ERR_OK;
}
int NegativeTestTop3()
{
     ADTErr result;
     
     /* null , null */
     if((result=StackTop(NULL ,NULL)) == ERR_NOT_INITIALIZED)
     {
        printf("neg test top 3 PASS\n"); 
     }
     else
     {
        printf("neg test top 3 FAILED\n");  
     }          
     
     return ERR_OK;
}

int NegativeTestTop4()
{
     int item;
     Stack *ptr;
     ADTErr result;
     
     /* stack empty */
     ptr=StackCreate(1 , 2);
     
     if((result=StackTop(ptr,&item)) == STACK_EMPTY)
     {
         printf("neg test top 4 PASS\n");
     }
     else
     {
        printf("neg test top 4 FAILED\n");          
     }          
     
     StackDestroy(ptr);
     return ERR_OK;
}

int PositiveTestEmpty1()
{
     Stack *ptr;  
     int result;   
     
     /* stack empty */
     ptr=StackCreate(1 , 2);
     
     if((result=StackIsEmpty(ptr)) == 1)
     {
        printf("pos test empty 1 PASS\n");             
     }
     else
     {
        printf("pos test empty 1 FAILED\n");             
     }     
     
     StackDestroy(ptr); 
     return ERR_OK;     
}
int PositiveTestEmpty2()
{
     Stack *ptr;  
     int result; 
       
     /* stack not empty */
     ptr=StackCreate(1 , 2);
     StackPush(ptr ,2);     
     
     if((result=StackIsEmpty(ptr)) == 0)
     {
        printf("pos test empty 2 PASS\n");           
     }
     else
     {
        printf("pos test empty 2 FAILED\n");              
     }     
     
     StackDestroy(ptr); 
     return ERR_OK;   
}
int NegativeTestEmpty1()
{ 
     int result;   
     
     /* stack = null */
     if((result=StackIsEmpty(NULL)) == 1)
     {
        printf("neg test empty 1 PASS\n");            
     }
     else
     {
        printf("neg test empty 1 FAILED\n");               
     }     
     
     return ERR_OK; 
}

