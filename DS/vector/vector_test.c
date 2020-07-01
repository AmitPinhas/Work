#include <stdio.h>
#include <stdlib.h>
#include "vector.h"
#include "vector_test.h"


/* --------------------------------------------------------------- Enum --------------------------------------------------------------------------- */
typedef enum { CREATE , DESTROY , APPEND , REMOVE , ITEMS_NUM , GET , SET , FOR_EACH }NameAPI ;

/*------------------------------------------------------------ local variables -------------------------------------------------------------------- */
static char s_pass[] = "Pass" ;
static char s_failed[] = "Failed" ;

/*------------------------------------------------------------ local function --------------------------------------------------------------------- */
static void NotNull(Vector *_vector , NameAPI _name);
static void TestNull(Vector *_vector , NameAPI _name);
static void VectorUnitializedError(VectorResult _result , NameAPI _name);
static void VectorIndex(Vector *_vector , VectorResult _result , NameAPI _name );
int CheckIfExists(void* _element, size_t _index, void* _context);

/* =============================================================== Tests ========================================================================== */

/* ----------------------------------------------------------- Vector Create ---------------------------------------------------------------------- */
void PositiveTestCreat1();
void PositiveTestCreat2();
void PositiveTestCreat3();
void NegativeTestCreat1();
/* ----------------------------------------------------------- Vector Destroy --------------------------------------------------------------------- */
void NegativeTestDestroy1();
void NegativeTestDestroy2();
/* ------------------------------------------------------------ Vector Append --------------------------------------------------------------------- */
void PositiveTestAppend1();
void PositiveTestAppend2();
void NegativeTestAppend1();
void NegativeTestAppend2();
void NegativeTestAppend3();
/* ----------------------------------------------------------- Vector Remove ---------------------------------------------------------------------- */
void PositiveTestRemove1();
void PositiveTestRemove2();
void NegativeTestRemove1();
void NegativeTestRemove2();
/* ------------------------------------------------------------ Vector Size ----------------------------------------------------------------------- */
void PositiveTestVectorSize1();
void NegativeTestVectorSize1();
void NegativeTestVectorSize2();
void NegativeTestVectorSize3();
/* ------------------------------------------------------------ Vector Get ------------------------------------------------------------------------ */
void PositiveTestGet1();
void NegativeTestGet1();
void NegativeTestGet2();
void NegativeTestGet3();
void NegativeTestGet4();
/* ------------------------------------------------------------ Vector Set ------------------------------------------------------------------------ */
void PositiveTestSet1();
void NegativeTestSet1();
void NegativeTestSet2();
void NegativeTestSet3();
/* --------------------------------------------------------- Vector capacity ---------------------------------------------------------------------- */
static void PositiveTestCapacity();
static void NegativeCapacity();

/* --------------------------------------------------------- Vector For Each ---------------------------------------------------------------------- */
static void PositiveTestForEach();


/* =============================================================== Main =========================================================================== */
int main()
{
	printf("Vector Create Test :\n");
     PositiveTestCreat1();
     PositiveTestCreat2();
     PositiveTestCreat3();
     NegativeTestCreat1();
	printf("Vector Destroy Test :\n");     
     NegativeTestDestroy1();
     NegativeTestDestroy2();
	printf("Vector Append Test :\n"); 
     PositiveTestAppend1();
     PositiveTestAppend2();
     NegativeTestAppend1();
     NegativeTestAppend2();
     NegativeTestAppend3();
	printf("Vector Remove Test :\n"); 
     PositiveTestRemove1();
     PositiveTestRemove2();
     NegativeTestRemove1();
     NegativeTestRemove2();
	printf("Vector Size Test :\n"); 
     PositiveTestVectorSize1();
     NegativeTestVectorSize1();
     NegativeTestVectorSize2();
     NegativeTestVectorSize3();
	printf("Vector Get Test :\n"); 
     PositiveTestGet1();
     NegativeTestGet1();
     NegativeTestGet2();
     NegativeTestGet3();
     NegativeTestGet4();
	printf("Vector Set Test :\n");
     PositiveTestSet1();
     NegativeTestSet1();
     NegativeTestSet2();
     NegativeTestSet3();
	printf("Vector capacity :\n");
	PositiveTestCapacity();
	NegativeCapacity();
	printf("Vector For Each :\n");	
     PositiveTestForEach();	
     return 1;
}

/* ----------------------------------------------------------- Vector Create ---------------------------------------------------------------------- */

void PositiveTestCreat1()
{
    size_t original_size , size , block;
    Vector *ptr1 ;
    int magic;
    size_t numElement;
     
     if ((ptr1=VectorCreate(4 , 3)) != NULL)
     {
          GetOriginalSize(ptr1 , &original_size);
          GetSize(ptr1 , &size);
          numElement = VectorSize(ptr1);
          GetBlock(ptr1 , &block);
          GetMagic(ptr1, &magic);
          if((original_size == 5) && (size == 5) && (numElement == 0) && (block == 3))
          {
          puts(s_pass);
          VectorDestroy(&ptr1 , NULL);
          }
     }
     else
     {
          printf("pos test creat 1 FAILED\n");
          puts(s_failed);
     }
 
}

void PositiveTestCreat2()
{
     Vector *ptr2 ;

	ptr2=VectorCreate(0 , 5);
	
     NotNull(ptr2 , CREATE); 
}
void PositiveTestCreat3()
{
     Vector *ptr3;
     
     ptr3=VectorCreate(6 , 0);
     
     NotNull(ptr3 , CREATE); 
}

void NegativeTestCreat1()
{
     Vector *ptr1 ;
     
     ptr1=VectorCreate(0 , 0);   

     TestNull(ptr1 , CREATE);
}

/* ----------------------------------------------------------- Vector Destroy --------------------------------------------------------------------- */
void NegativeTestDestroy1()
{
    VectorDestroy(NULL , NULL);
    puts(s_pass);
}

void NegativeTestDestroy2()
{
     Vector *ptr1 ;
     
     if ((ptr1=VectorCreate(1 ,1)) != NULL)
     {
          VectorDestroy(&ptr1 , NULL);
          VectorDestroy(&ptr1 , NULL);          
          puts(s_pass);
     }     
}
/* ------------------------------------------------------------ Vector Append --------------------------------------------------------------------- */
void PositiveTestAppend1()
{
     Vector *ptr1 ;
     VectorResult result;
     size_t numElement;
     int number=5;


     /* test 1 : add without realloc */ 
     ptr1=VectorCreate(2 , 2);
     if((result=VectorAppend (ptr1 ,&number)) == VECTOR_SUCCESS)
     {
          numElement = VectorSize(ptr1);
          if(numElement == 1)
          {
          puts(s_pass);
          VectorDestroy(&ptr1 , NULL);          
          }
          else
          {
          printf("pos test add 1 FAILED\n");          
          }
     }
     else
     {
     printf("pos test add 1 FAILED\n");       
     }        
}
void PositiveTestAppend2()
{
     Vector *ptr2 ;
     VectorResult result;
     size_t numElement;
     int number=5;

     /* test 2 : add with realloc */ 
     ptr2=VectorCreate(0 , 2);
     if((result=VectorAppend (ptr2 ,&number)) == VECTOR_SUCCESS)
     {
          numElement = VectorSize(ptr2);
          if(numElement == 1)
          {
          puts(s_pass);
          VectorDestroy(&ptr2 , NULL);          
          }
          else
          {
          printf("pos test add 2 FAILED\n");          
          }
     }
     else
     {
     printf("pos test add 2 FAILED\n");       
     }    
}

void NegativeTestAppend1()
{
     VectorResult result;
     int number = 5 ;
     
     result=VectorAppend (NULL ,&number);
     
     VectorUnitializedError(result , APPEND);     
}

void NegativeTestAppend2()
{
     Vector *ptr2 ;
     VectorResult result;
     int number=5;
     int number2=6;

     /* test 2 : overflow */ 
     ptr2=VectorCreate(1 , 0);
     VectorAppend (ptr2 ,&number);     
     VectorAppend (ptr2 ,&number);
     if((result=VectorAppend (ptr2 ,&number2)) == VECTOR_OVERFLOW_ERROR)
     {
          puts(s_pass);
          VectorDestroy(&ptr2 , NULL);          
     }
     else
     {
     printf("neg test add 2 FAILED\n");       
     }    

}

void NegativeTestAppend3()
{
     Vector *ptr3 ;
     VectorResult result;
     int number=5;

     /* test 2 : realloc failed */ 
     ptr3=VectorCreate(0 , -1);
     VectorAppend (ptr3 ,&number);
     if((result=VectorAppend (ptr3 ,&number)) == VECTOR_ALLOCATION_ERROR)
     {
          puts(s_pass);
          VectorDestroy(&ptr3 , NULL);          
     }
     else
     {
     printf("neg test add 3 FAILED\n");       
     }      
}
/* ----------------------------------------------------------- Vector Remove ---------------------------------------------------------------------- */
void PositiveTestRemove1()
{
     Vector *ptr1 ;
     VectorResult result;
     int *num ;
     int number=5;
     size_t numElement ;

     /* test 1 : delete without realloc */ 
     ptr1=VectorCreate(1 , 2);
     VectorAppend (ptr1 ,&number);
     if((result=VectorRemove (ptr1 ,(void**)&num)) == VECTOR_SUCCESS)
     {
          numElement = VectorSize(ptr1);
          if( *num == 5 && numElement == 0)
          {
          puts(s_pass);
          VectorDestroy(&ptr1 , NULL);          
          }
          else
          {
          printf("pos test delete 1 FAILED\n");          
          }
     }
     else
     {
     printf("pos test delete 1 FAILED\n");       
     }    

}
void PositiveTestRemove2()
{
     Vector *ptr2 ;
     VectorResult result;
     int *num ;
     size_t size;
     int number=5;
     size_t numElement;

     /* test 1 : delete with realloc */ 
     ptr2=VectorCreate(0 , 1);
     VectorAppend (ptr2 ,&number);
     VectorAppend (ptr2 ,&number);     
     VectorRemove (ptr2 ,(void**)&num);
     if((result=VectorRemove (ptr2 ,(void**)&num)) == VECTOR_SUCCESS)
     {
          GetSize(ptr2 , &size);
          numElement = VectorSize(ptr2);
          if(size == 1 && numElement == 0)
          {
          puts(s_pass);
          VectorDestroy(&ptr2 , NULL);          
          }
          else
          {
          printf("pos test delete 2 FAILED\n");          
          }
     }
     else
     {
     printf("pos test delete 2 FAILED\n");       
     }    

}
void NegativeTestRemove1()
{
     Vector *ptr1 ;
     VectorResult result;
     int *num;

     /* test 1 : num of element = 0  */ 
     ptr1=VectorCreate(1 , 2);
     if((result=VectorRemove (ptr1 ,(void**)&num)) == VECTOR_UNDERFLOW_ERROR)
     {
          puts(s_pass);
          VectorDestroy(&ptr1 , NULL);          
     }
     else
     {
     printf("neg test delete 1 FAILED\n");       
     }    

}
void NegativeTestRemove2()
{
     VectorResult result;
     int num;

     result=VectorRemove (NULL ,(void**)&num);
     
	VectorUnitializedError(result , REMOVE) ;       

}
/* ---------------------------------------------------------- Vector Size ------------------------------------------------------------------------- */
void PositiveTestVectorSize1()
{
     Vector *ptr;
     size_t numElement;
     
     ptr=VectorCreate(1 , 2);
     
     if( (numElement=VectorSize(ptr)) == 0)
     {
         puts(s_pass);
         VectorDestroy(&ptr , NULL); 
     }
     else
     {
         printf("pos test ItemsNum 1 FAILED\n");   
     }

}
void NegativeTestVectorSize1()
{
     size_t numElement;   
     
     if( (numElement=VectorSize(NULL)) == 0)
     {
        puts(s_pass);
     }
     else
     {
        printf("neg test ItemsNum 1 FAILED\n");    
     }

}
void NegativeTestVectorSize2()
{
     Vector *ptr;
     size_t numElement;   
     
     ptr=VectorCreate(1 , 2);
     
     if( (numElement=VectorSize(ptr)) == 0)
     {
        puts(s_pass);
     }
     else
     {
        printf("neg test ItemsNum 2 FAILED\n");    
     }
     
     VectorDestroy(&ptr , NULL);
}
void NegativeTestVectorSize3()
{
     size_t numElement;   
     	    
     if( (numElement=VectorSize(NULL)) == 0)
     {
        puts(s_pass);
     }
     else
     {
        printf("neg test ItemsNum 3 FAILED\n");    
     }

}
/* -------------------------------------------------------- Vector Get ---------------------------------------------------------------------------- */
void PositiveTestGet1()
{
     int *item;
     Vector *ptr;
     VectorResult result;
     int number=2;
     
     ptr=VectorCreate(1 , 2);
     VectorAppend(ptr ,&number);
     
     if((result=VectorGet(ptr, 1 ,(void**)&item)) == VECTOR_SUCCESS)
     {
          if(*item == 2)
          {
               puts(s_pass);
               VectorDestroy(&ptr , NULL); 
          }
          else
          {
               printf("pos test Get 1 FAILED\n");
          }
     }
     else
     {
        printf("pos test Get 1 FAILED\n");  
     }          

}
void NegativeTestGet1()
{
     int item;
     VectorResult result;
     
     result=VectorGet(NULL, 1 ,(void**)&item);
     
	VectorUnitializedError(result , GET) ;       

}
void NegativeTestGet2()
{
     Vector *ptr;
     VectorResult result;
     int number=2;
     
     ptr=VectorCreate(1 , 2);
     VectorAppend(ptr ,&number);
     
     if((result=VectorGet(ptr, 1 ,NULL)) == VECTOR_UNITIALIZED_ERROR)
     {
                puts(s_pass);
               VectorDestroy(&ptr , NULL); 
     }
     else
     {
        printf("neg test Get 2 FAILED\n");  
     }          

}
void NegativeTestGet3()
{
     VectorResult result;
     
	result=VectorGet(NULL, 1 ,NULL);
	
	VectorUnitializedError(result , GET) ; 
	       
}
void NegativeTestGet4()
{
     int *item;
     Vector *ptr;
     VectorResult result;
     int number=2;
     
     ptr=VectorCreate(1 , 2);
     VectorAppend(ptr ,&number);
	result=VectorGet(ptr, 3 ,(void**)&item);
	
	VectorIndex(ptr , result , GET );     
}

/* -------------------------------------------------------- Vector Set ---------------------------------------------------------------------------- */
void PositiveTestSet1()
{
     int item=10;
     int* itemPtr;
     Vector *ptr;
     VectorResult result;
     int number2=8;
     
     ptr=VectorCreate(1 , 2);
     VectorAppend(ptr ,&item);
          
     if((result=VectorSet(ptr, 1 , &number2)) == VECTOR_SUCCESS)
     {
          VectorGet(ptr, 1 ,(void**)&itemPtr);
          if( *itemPtr == 8)
          {
                puts(s_pass);
               VectorDestroy(&ptr , NULL); 
          }
          else
          {
               printf("pos test Set 1 FAILED\n");
          }
     } 
     else
     {
        printf("pos test Set 1 FAILED\n");  
     }         
}

void NegativeTestSet1()
{
     VectorResult result;
     int number=8;
     
     result=VectorSet(NULL, 1 , &number);
     
     VectorUnitializedError(result , SET);             
}

void NegativeTestSet2()
{
     Vector *ptr;
     VectorResult result;
     int number=2;
     int number2=8;
     
     ptr=VectorCreate(1 , 2);
     VectorAppend(ptr ,&number);
     result=VectorSet(ptr, 6 , &number2);
     
     VectorIndex(ptr , result , SET ) ;          
}

void NegativeTestSet3()
{
     VectorResult result;
     int number=8;
     
     result=VectorSet(NULL, 6 , &number);
          
     VectorUnitializedError(result , SET);         
}

/* --------------------------------------------------------- Vector capacity ---------------------------------------------------------------------- */
static void PositiveTestCapacity()
{
	Vector *ptrVector;
	size_t capacitiy;
	
	ptrVector = VectorCreate (10, 5);
	
	capacitiy = VectorCapacity(ptrVector);
	
	if ( capacitiy == 11 )
	{
		puts(s_pass);
	}
	else
	{
		puts(s_failed);
	}
	
	VectorDestroy(&ptrVector , NULL);
}

static void NegativeCapacity()
{
	size_t capacitiy;
	
	capacitiy = VectorCapacity(NULL);
	
	if ( capacitiy == 0 )
	{
		puts(s_pass);
	}
	else
	{
		puts(s_failed);
	}	
}

/* --------------------------------------------------------- Vector For Each ---------------------------------------------------------------------- */
static void PositiveTestForEach()
{
	Vector *ptrVector;
	int number1=4;
	int number2=5;
	int number3=7;
	size_t result;
	
	ptrVector = VectorCreate(5 , 2);
	
	VectorAppend(ptrVector , &number1);  
	VectorAppend(ptrVector , &number2);  
	VectorAppend(ptrVector , &number3); 
	
	result = VectorForEach(ptrVector, CheckIfExists , &number2); 
	
	if ( result ==  1 )
	{
		puts(s_pass);
	}
	else
	{
		puts(s_failed);
	}
	
	VectorDestroy(&ptrVector , NULL);
}

/*------------------------------------------------------------ local function --------------------------------------------------------------------- */
static void NotNull(Vector *_vector , NameAPI _name)
{
     if ( _vector != NULL)
     {
          puts(s_pass);
          VectorDestroy(&_vector , NULL);
     }
     else
     {
          switch ( _name )
          {
          	case CREATE     : printf("create : ");
          	                  break;
          	case DESTROY    : printf("destroy : ");
          	                  break; 
          	case APPEND     : printf("append : ");
          	                  break;
          	case REMOVE     : printf("remove : ");
          	                  break;
          	case ITEMS_NUM  : printf("items num : ");
          	                  break;
          	case GET        : printf("get : ");
          	                  break;
          	case SET        : printf("set : ");
          	                  break;  
          	case FOR_EACH   : printf("for each : ");
          	                  break;
          	     default    :  
          	                  break;          	                          	                        	                        	                        	                        	                       	              
          }
          puts(s_failed);
     }
}


/*--------------------------------------------------------------------------------------------------------------------------------------------------*/
static void TestNull(Vector *_vector , NameAPI _name)
{
     if ( _vector == NULL)
     {
          puts(s_pass);
          VectorDestroy(&_vector , NULL);
     }
     else
     {
          switch ( _name )
          {
          	case CREATE     : printf("create : ");
          	                  break;
          	case DESTROY    : printf("destroy : ");
          	                  break; 
          	case APPEND     : printf("append : ");
          	                  break;
          	case REMOVE     : printf("remove : ");
          	                  break;
          	case ITEMS_NUM  : printf("items num : ");
          	                  break;
          	case GET        : printf("get : ");
          	                  break;
          	case SET        : printf("set : ");
          	                  break; 
          	case FOR_EACH   : printf("for each : ");
          	                  break;
          	     default    :  
          	                  break;          	                           	                        	                        	                        	                        	                       	              
          }
          puts(s_failed);
     }
}

/*--------------------------------------------------------------------------------------------------------------------------------------------------*/
static void VectorUnitializedError(VectorResult _result , NameAPI _name)
{
     if ( _result == VECTOR_UNITIALIZED_ERROR )
     {
          puts(s_pass);
     }
     else
     {
          switch ( _name )
          {
          	case CREATE     : printf("create : ");
          	                  break;
          	case DESTROY    : printf("destroy : ");
          	                  break; 
          	case APPEND     : printf("append : ");
          	                  break;
          	case REMOVE     : printf("remove : ");
          	                  break;
          	case ITEMS_NUM  : printf("items num : ");
          	                  break;
          	case GET        : printf("get : ");
          	                  break;
          	case SET        : printf("set : ");
          	                  break;   
          	case FOR_EACH   : printf("for each : ");
          	                  break;
          	     default    :  
          	                  break;          	                         	                        	                        	                        	                        	                       	              
          }
          puts(s_failed);
     }
}

/*--------------------------------------------------------------------------------------------------------------------------------------------------*/
static void VectorIndex(Vector *_vector , VectorResult _result , NameAPI _name )
{
     if ( _result == VECTOR_INDEX_OUT_OF_BOUNDS_ERROR )
     {
          puts(s_pass);
          VectorDestroy(&_vector , NULL);
     }
     else
     {
          switch ( _name )
          {
          	case CREATE     : printf("create : ");
          	                  break;
          	case DESTROY    : printf("destroy : ");
          	                  break; 
          	case APPEND     : printf("append : ");
          	                  break;
          	case REMOVE     : printf("remove : ");
          	                  break;
          	case ITEMS_NUM  : printf("items num : ");
          	                  break;
          	case GET        : printf("get : ");
          	                  break;
          	case SET        : printf("set : ");
          	                  break; 
          	case FOR_EACH   : printf("for each : ");
          	                  break;
          	     default    :  
          	                  break;                                 	                        	                        	                        	                        	                       	              
          }
          puts(s_failed);
     }	
}

/*--------------------------------------------------------------------------------------------------------------------------------------------------*/
int CheckIfExists(void* _element, size_t _index, void* _context)
{
	if ( _element == _context )
	{
		return 0 ;
	}
	
	return _index;
}
