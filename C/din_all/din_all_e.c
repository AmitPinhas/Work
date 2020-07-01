#include <stdio.h>
#include <stdlib.h>
#include "din_all_e.h"

int Positive_Test_Creat();
int Negative_Test_Creat();
int Positive_Test_Insert();
int Negative_Test_Insert();
int Positive_Test_Delete();
int Negative_Test_Delete(); 

int main()
{


     Positive_Test_Creat(); 
     Negative_Test_Creat(); 
     
     Positive_Test_Insert();
     Negative_Test_Insert(); 
     
     Positive_Test_Delete(); 
     Negative_Test_Delete();  
     
     return OK;
}

int Positive_Test_Creat()
{
     int size_1=4 , blocksize_1=3;
     int size_2=0 , blocksize_2=5;
     int size_3=6 , blocksize_3=0;
     DynamicArray *ptr1 , *ptr2 , *ptr3;
     
     printf("Positive_Test_Creat:\n");
     
     /* test 1 : size>0 , blocksize>0 */
     
     if ((ptr1=DynamicArrayCreat(size_1 , blocksize_1)) != NULL)
     {
          printf("pos test 1 PASS\n");
     }
     else
     {
          printf("pos test 1 FAILED\n");
     }
     DynamicArrayDestroy(ptr1);
     
     /* test 2 : size=0 , blocksize>0 */
     
     if ((ptr2=DynamicArrayCreat(size_2 , blocksize_2)) != NULL)
     {
          printf("pos test 2 PASS\n");
     } 
     else
     {
          printf("pos test 2 FAILED\n");
     }    
     
     DynamicArrayDestroy(ptr2);

     /* test 3 : size>0 , blocksize=0 */
     
     if ((ptr3=DynamicArrayCreat(size_3 , blocksize_3)) != NULL)
     {
          printf("pos test 3 PASS\n");
     }
     else
     {
          printf("pos test 3 FAILED\n");
     }
     
     DynamicArrayDestroy(ptr3);     
   
     return OK;
}

int Negative_Test_Creat()
{
     int size_1=-4 , blocksize_1=3;
     int size_2=0 , blocksize_2=-4;
     int size_3=0 , blocksize_3=0;
     int size_4=-4 , blocksize_4=-2;
     DynamicArray *ptr1 , *ptr2 , *ptr3 , *ptr4;
     
     printf("Negative_Test_Creat:\n");
     
     /* test 1 : size<0 , blocksize>0 */
     
     if ((ptr1=DynamicArrayCreat(size_1 , blocksize_1)) == NULL)
     {
          printf("neg test 1 PASS\n");
     }
     else
     {
          printf("neg test 1 FAILED\n");
     }
     
     /* test 2 : size=0 , blocksize<0 */
     
     if ((ptr2=DynamicArrayCreat(size_2 , blocksize_2)) == NULL)
     {
          printf("neg test 2 PASS\n");
     } 
     else
     {
          printf("neg test 2 FAILED\n");
     }    

     /* test 3 : size=0 , blocksize=0 */
     
     if ((ptr3=DynamicArrayCreat(size_3 , blocksize_3)) == NULL)
     {
          printf("neg test 3 PASS\n");
     }  
     else
     {
          printf("neg test 3 FAILED\n");
     }
     
     /* test 4 : size<0 , blocksize<0 */
     
     if ((ptr4=DynamicArrayCreat(size_4 , blocksize_4)) == NULL)
     {
          printf("neg test 4 PASS\n");
     } 
     else
     {
          printf("neg test 4 FAILED\n");
     }
     
     return OK;
}


int Positive_Test_Insert()
{
     DynamicArray *ptr1 , *ptr2 , *ptr3;
     DynamicArrayError result_check , result_check2 , result_check3;
     
     printf("Positive_Test_Insert:\n");
     
     /* test 1 : size array=2 , element=0 , inc=2*/
     ptr1 = DynamicArrayCreat(2 , 2);
     if((result_check=DynamicArrayInsert(ptr1, 3)) == OK)
     {
          printf("pos test 1 PASS\n");
     }
     else
     {
          printf("pos test 1 FAILED\n");
     }
     
     DynamicArrayDestroy(ptr1);
     
     /* test 2 : size array=0 , element=0 , inc=2*/
     ptr2 = DynamicArrayCreat(0 , 2);
     if((result_check2=DynamicArrayInsert(ptr2, 3)) == OK)
     {
          printf("pos test 2 PASS\n");
     }
     else
     {
          printf("pos test 2 FAILED\n");
     }  
     
     DynamicArrayDestroy(ptr2);
     
     /* test 3 : size array=1 , element=0 , inc=0*/
     ptr3 = DynamicArrayCreat(1 , 0);
     if((result_check3=DynamicArrayInsert(ptr3, 3)) == OK)
     {
          printf("pos test 3 PASS\n");
     }
     else
     {
          printf("pos test 3 FAILED\n");
     }  
     
     DynamicArrayDestroy(ptr3);       
     
     return OK;
}

int Negative_Test_Insert()
{
     DynamicArray *ptr1=NULL , *ptr2;
     DynamicArrayError result_check , result_check2;
     
     printf("Negative_Test_Insert:\n");
     
     /* test 1 : ptr1 = NULL */
     if((result_check=DynamicArrayInsert(ptr1, 3)) == PTR_ERROR)
     {
          printf("neg test 1 PASS\n");
     }
     else
     {
          printf("neg test 1 FAILED\n");
     }
     
     /* test 2 : num of element = size and inc = 0 */
     ptr2 = DynamicArrayCreat(1 , 0);
     DynamicArrayInsert(ptr2, 3);
     if((result_check2=DynamicArrayInsert(ptr2, 3)) == ERROR_OVERFLOW)
     {
          printf("neg test 2 PASS\n");
          DynamicArrayDestroy(ptr2);
     }
     else
     {
          printf("neg test 2 FAILED\n");
     }     

     return OK;
}

int Positive_Test_Delete()
{
     DynamicArray *ptr1 ;
     int data;
     DynamicArrayError result_check;
     
     printf("Positive_Test_Delete:\n");
     
     /* test 1 */
     ptr1 = DynamicArrayCreat(1 , 0);
     DynamicArrayInsert(ptr1, 3);
     if((result_check=DynamicArrayDelete(ptr1, &data)) == OK)
     {
          printf("pos test 1 PASS\n");
          DynamicArrayDestroy(ptr1);
     }
     else
     {
          printf("pos test 1 FAILED\n");
     }          
     
     
     return OK;
}

int Negative_Test_Delete()
{
     DynamicArray *ptr1=NULL , *ptr2 , *ptr3 , *ptr4 ;
     int data1 , data4;
     DynamicArrayError result_check1 , result_check2 ,result_check3 , result_check4 ;
     
     printf("Negative_Test_Delete:\n");
     
     /* test 1 : ptr1 = NULL */
     if((result_check1=DynamicArrayDelete(ptr1, &data1)) == PTR_ERROR)
     {
          printf("neg test 1 PASS\n");
     }
     else
     {
          printf("neg test 1 FAILED\n");
     }  
     
     /* test 2 : data = NULL */
     ptr2 = DynamicArrayCreat(1 , 0);
     if((result_check2=DynamicArrayDelete(ptr2, NULL)) == PTR_ERROR)
     {
          printf("neg test 2 PASS\n");
          DynamicArrayDestroy(ptr2);
     }
     else
     {
          printf("neg test 2 FAILED\n");
     }      

     /* test 3 : ptr3 = NULL ,  data = NULL*/
     if((result_check3=DynamicArrayDelete(ptr3, NULL)) == PTR_ERROR)
     {
          printf("neg test 3 PASS\n");
     }
     else
     {
          printf("neg test 3 FAILED\n");
     }  
     
     /* test 4 : num of element = 0 */
     ptr4 = DynamicArrayCreat(1 , 0);
     if((result_check4=DynamicArrayDelete(ptr4, &data4)) == ERROR_NO_ELEMNTS)
     {
          printf("neg test 4 PASS\n");
     }
     else
     {
          printf("neg test 4 FAILED\n");
     }  
     
     DynamicArrayDestroy(ptr4);   

     return OK;
}

/* Name: Amit Pinhas */
