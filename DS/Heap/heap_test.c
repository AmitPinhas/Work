#include <stdio.h>
#include "ADTDefs.h"
#include "heap.h"
#include "vector.h"

/* ----------------------- Static variables ------------------------ */

static char s_pass[]="pass";
static char s_failed[]="failed";


/* ----------------------- HeapBuild tests ------------------------- */

static void HeapBuildTestNormal();
static void HeapBuildTestNull();
static void HeapBuildTestEmptyVector();
static void HeapBuildTestOneItem();
static void HeapBuildTestTwoItems();
static void HeapBuildTestThreeItemsRightBig();
static void HeapBuildTestThreeItemsLeftBig();
static void HeapBuildTestAlreadyHeap();
static void HeapBuildTestAllParentsSmall();

/* ----------------------- HeapPrint tests -------------------------- */

static void HeapPrintNull();

/* ----------------------- HeapDestroy tests ------------------------ */

static void HeapDestroyNull();
static void HeapDestroyDoubleFree();


/* ----------------------- HeapItemsNum tests ----------------------- */

static void HeapItemsNumNull();
static void HeapItemsNumEmpty();
static void HeapItemsOneItem();
static void HeapItemsManyItems();
static void HeapItemsAfterInsert();
static void HeapItemsAfterExtract();
static void HeapItemsAfterTwoInsert();
static void HeapItemsAfterTwoExtract();

/* ----------------------- HeapInsert tests ------------------------- */

static void HeapInsertNormal();
static void HeapInsertNull();
static void HeapInsertToEmpty();
static void HeapInsertTwoValues();
static void HeapInsertSmallValue();
static void HeapInsertSameValue();
static void HeapInsertMiddleValue();


/* ----------------------- HeapMax tests ----------------------- */

static void HeapMaxNormal();
static void HeapMaxNullHeap();
static void HeapMaxNullPointerData();
static void HeapMaxEmptyHeap();
static void HeapMaxOneValue();


/* ----------------------- HeapExtractMax tests ----------------------- */

static void HeapExtractMaxNormal();
static void HeapExtractMaxNullHeap();
static void HeapExtractMaxNullPointerData();
static void HeapExtractMaxNullTwoPointer();
static void HeapExtractMaxEmptyHeap();
static void HeapExtractMaxOneItem();
static void HeapExtractMaxTwoItems();
static void HeapExtractMaxTwoActions();
static void HeapExtractMaxThreeActions();


/* ----------------------- Main ----------------------------------- */

int main()
{

	printf("=====================HeapBuild tests============================\n\n");
	HeapBuildTestNormal();
	HeapBuildTestNull();
	HeapBuildTestEmptyVector();
	HeapBuildTestOneItem();
	HeapBuildTestTwoItems(); 
	HeapBuildTestThreeItemsRightBig();
	HeapBuildTestThreeItemsLeftBig();
	HeapBuildTestAlreadyHeap();
	HeapBuildTestAllParentsSmall();
	
	printf("\n=====================HeapPrint tests==========================\n\n");	
	HeapPrintNull();
	
	printf("\n=====================HeapDestroy tests========================\n\n");	
	HeapDestroyNull();
	HeapDestroyDoubleFree();
	
	printf("\n=====================HeapItemsNum tests=======================\n\n");		
	HeapItemsNumNull();
	HeapItemsNumEmpty();
	HeapItemsOneItem();
	HeapItemsManyItems();
	HeapItemsAfterInsert();
	HeapItemsAfterExtract();
	HeapItemsAfterTwoInsert();
     HeapItemsAfterTwoExtract();	
	
	printf("\n=====================HeapInsert tests=========================\n\n");		
	HeapInsertNormal();
	HeapInsertNull();
	HeapInsertToEmpty();
	HeapInsertTwoValues();
	HeapInsertSmallValue();
	HeapInsertSameValue();
	HeapInsertMiddleValue();
	
	printf("\n=====================HeapMax tests============================\n\n");		
     HeapMaxNormal();
	HeapMaxNullHeap();
	HeapMaxNullPointerData();
	HeapMaxEmptyHeap();
	HeapMaxOneValue();
	
	printf("\n=====================HeapExtractMax tests=====================\n\n");			
	HeapExtractMaxNormal();
	HeapExtractMaxNullHeap();
	HeapExtractMaxNullPointerData();
	HeapExtractMaxNullTwoPointer();
	HeapExtractMaxEmptyHeap();
	HeapExtractMaxOneItem();
     HeapExtractMaxTwoItems();
     HeapExtractMaxTwoActions();
     HeapExtractMaxThreeActions();
     
	return 1;
}



/* ----------------------- HeapBuild tests ------------------------- */

static void HeapBuildTestNormal()
{
	Vector *ptrVector;
	Heap *ptrHeap;	
	
	printf("HeapBuildTestNormal:\n");
	
	ptrVector = VectorCreate (5, 3);
	
	VectorAdd (ptrVector ,65);
	VectorAdd (ptrVector ,45); 
	VectorAdd (ptrVector ,15); 
	VectorAdd (ptrVector ,78); 
	VectorAdd (ptrVector ,100); 
	VectorAdd (ptrVector ,2); 
	VectorAdd (ptrVector ,4); 
	VectorAdd (ptrVector ,3); 
	VectorAdd (ptrVector ,12);  
	
	VectorPrint(ptrVector);
	putchar('\n');
	ptrHeap = HeapBuild(ptrVector);
	
	HeapPrint(ptrHeap);
	putchar('\n');	
	
	if ( ptrHeap != NULL )
     {
	  puts(s_pass);    
     }
     else
     {
       puts(s_failed);   
     }	
	
	VectorDestroy(ptrVector);
	HeapDestroy(ptrHeap);
}

static void HeapBuildTestNull()
{
     printf("HeapBuildTestNull: ");
	if ( HeapBuild(NULL) == NULL )
	{
		puts(s_pass);	
	}
	else
	{
		puts(s_failed);	
	}
}

static void HeapBuildTestEmptyVector()
{
	Vector *ptrVector;
	Heap *ptrHeap;
	
	printf("HeapBuildTestEmptyVector:\n");
	
	ptrVector = VectorCreate (5, 3); 
	
	VectorPrint(ptrVector);
	putchar('\n');
	if ( (ptrHeap = HeapBuild(ptrVector)) != NULL )
	{
		puts(s_pass);
	}
	else
	{
	     puts(s_failed);
	}
	
	HeapPrint(ptrHeap);
	putchar('\n');	
	VectorDestroy(ptrVector);
	HeapDestroy(ptrHeap);
}

static void HeapBuildTestOneItem()
{
	Vector *ptrVector;
	Heap *ptrHeap;
	
	printf("HeapBuildTestOneItem:\n");
	
	ptrVector = VectorCreate (5, 3);
	
	VectorAdd (ptrVector ,65);
	
	VectorPrint(ptrVector);
	putchar('\n');
	ptrHeap = HeapBuild(ptrVector);
	
	HeapPrint(ptrHeap);
	putchar('\n');	
	
	if ( ptrHeap != NULL )
     {
	  puts(s_pass);    
     }
     else
     {
       puts(s_failed);   
     }	
	
	VectorDestroy(ptrVector);
	HeapDestroy(ptrHeap);
}

static void HeapBuildTestTwoItems()
{
	Vector *ptrVector;
	Heap *ptrHeap;
	
	printf("HeapBuildTestTwoItems:\n");

	ptrVector = VectorCreate (5, 3);
	VectorAdd (ptrVector ,65);
	VectorAdd (ptrVector ,100);   
	
	VectorPrint(ptrVector);
 	putchar('\n');

	ptrHeap = HeapBuild(ptrVector);

	HeapPrint(ptrHeap); 
	putchar('\n');	

	if ( ptrHeap != NULL )
     {
	  puts(s_pass);    
     }
     else
     {
       puts(s_failed);   
     }	
	
	VectorDestroy(ptrVector);
	HeapDestroy(ptrHeap);
}

static void HeapBuildTestThreeItemsRightBig()
{
	Vector *ptrVector;
	Heap *ptrHeap;
	
	printf("HeapBuildTestThreeItemsRightBig:\n");
	
	ptrVector = VectorCreate (5, 3);
	
	VectorAdd (ptrVector ,65);
	VectorAdd (ptrVector ,75); 
	VectorAdd (ptrVector ,85);   
	
	VectorPrint(ptrVector);
	putchar('\n');
	ptrHeap = HeapBuild(ptrVector);
	
	HeapPrint(ptrHeap);
	putchar('\n');	

	if ( ptrHeap != NULL )
     {
	  puts(s_pass);    
     }
     else
     {
       puts(s_failed);   
     }	
	
	VectorDestroy(ptrVector);
	HeapDestroy(ptrHeap);

}

static void HeapBuildTestThreeItemsLeftBig()
{
	Vector *ptrVector;
	Heap *ptrHeap;
	
	printf("HeapBuildTestThreeItemsLeftBig:\n");
	
	ptrVector = VectorCreate (5, 3);
	
	VectorAdd (ptrVector ,65);
	VectorAdd (ptrVector ,175); 
	VectorAdd (ptrVector ,85);   
	
	VectorPrint(ptrVector);
	putchar('\n');
	ptrHeap = HeapBuild(ptrVector);
	
	HeapPrint(ptrHeap);
	putchar('\n');	

	if ( ptrHeap != NULL )
     {
	  puts(s_pass);    
     }
     else
     {
       puts(s_failed);   
     }	
	
	VectorDestroy(ptrVector);
	HeapDestroy(ptrHeap);

}

static void HeapBuildTestAlreadyHeap()
{
	Vector *ptrVector;
	Heap *ptrHeap;
	
	printf("HeapBuildTestAlreadyHeap:\n");
	
	ptrVector = VectorCreate (5, 3);
	
	VectorAdd (ptrVector ,200);
	VectorAdd (ptrVector ,100); 
	VectorAdd (ptrVector ,50); 
	VectorAdd (ptrVector ,78); 
	VectorAdd (ptrVector ,90); 
	VectorAdd (ptrVector ,2); 
	VectorAdd (ptrVector ,4); 
	VectorAdd (ptrVector ,3); 
	VectorAdd (ptrVector ,12);  
	
	VectorPrint(ptrVector);
	putchar('\n');
	ptrHeap = HeapBuild(ptrVector);
	
	HeapPrint(ptrHeap);
	putchar('\n');	

	if ( ptrHeap != NULL )
     {
	  puts(s_pass);    
     }
     else
     {
       puts(s_failed);   
     }	
	
	VectorDestroy(ptrVector);
	HeapDestroy(ptrHeap);

}

static void HeapBuildTestAllParentsSmall()
{
	Vector *ptrVector;
	Heap *ptrHeap;
	
	printf("HeapBuildTestAllParentsSmall:\n");
	
	ptrVector = VectorCreate (5, 3);
	
	VectorAdd (ptrVector ,1);
	VectorAdd (ptrVector ,50); 
	VectorAdd (ptrVector ,70); 
	VectorAdd (ptrVector ,55); 
	VectorAdd (ptrVector ,74); 
	VectorAdd (ptrVector ,80); 
	VectorAdd (ptrVector ,93); 
	VectorAdd (ptrVector ,200); 
	VectorAdd (ptrVector ,334);  
	
	VectorPrint(ptrVector);
	putchar('\n');
	ptrHeap = HeapBuild(ptrVector);
	
	HeapPrint(ptrHeap);
	putchar('\n');	

	if ( ptrHeap != NULL )
     {
	  puts(s_pass);    
     }
     else
     {
       puts(s_failed);   
     }	
	
	VectorDestroy(ptrVector);
	HeapDestroy(ptrHeap);

}

/* ----------------------- HeapPrint tests -------------------------- */

static void HeapPrintNull()
{
	printf("HeapPrintNull:\n");
	printf("\t\t\t");		
	HeapPrint(NULL);
	puts(s_pass);	
}

/* ----------------------- HeapDestroy tests ------------------------ */

static void HeapDestroyNull()
{
	printf("HeapDestroyNull:\n");
	HeapDestroy(NULL);
	printf("\t\t\t");
	puts(s_pass);		
}

static void HeapDestroyDoubleFree()
{
	Vector *ptrVector;
	Heap *ptrHeap;
	
	printf("HeapDestroyDoubleFree:\n");
	
	ptrVector = VectorCreate (5, 3);
	
	VectorAdd (ptrVector ,1);
	VectorAdd (ptrVector ,50); 
	VectorAdd (ptrVector ,70); 
	VectorAdd (ptrVector ,55); 
	VectorAdd (ptrVector ,74); 
	VectorAdd (ptrVector ,80); 
	VectorAdd (ptrVector ,93); 
	VectorAdd (ptrVector ,200); 
	VectorAdd (ptrVector ,334);  
	
	ptrHeap = HeapBuild(ptrVector);
	
	VectorDestroy(ptrVector);
	HeapDestroy(ptrHeap);
	HeapDestroy(ptrHeap);
	printf("\t\t\t");	
	puts(s_pass);
}

/* ----------------------- HeapItemsNum tests ----------------------- */

static void HeapItemsNumNull()
{
	printf("HeapItemsNumNull:\n");
	printf("\t\t\t");		
    if ( HeapItemsNum(NULL) == ERR_PTR_NULL)
    {
    
	 puts(s_pass);    
    }
    else
    {
    	 puts(s_failed);   
    }
}

static void HeapItemsNumEmpty()
{
	Vector *ptrVector;
	Heap *ptrHeap;
	
	printf("HeapItemsNumEmpty:\n");
	printf("\t\t\t");	
	ptrVector = VectorCreate (5, 3); 
	
	ptrHeap = HeapBuild(ptrVector) ;

	if ( HeapItemsNum(ptrHeap) == 0 )
     {
	  puts(s_pass);    
     }
     else
     {
       puts(s_failed);   
     }
	
	VectorDestroy(ptrVector);
	HeapDestroy(ptrHeap);
}

static void HeapItemsOneItem()
{
	Vector *ptrVector;
	Heap *ptrHeap;
	
	printf("HeapItemsOneItem:\n");
	printf("\t\t\t");		
	ptrVector = VectorCreate (5, 3); 
	VectorAdd (ptrVector ,1);
		
	ptrHeap = HeapBuild(ptrVector) ;

	if ( HeapItemsNum(ptrHeap) == 1 )
     {
	  puts(s_pass);    
     }
     else
     {
       puts(s_failed);   
     }
	
	VectorDestroy(ptrVector);
	HeapDestroy(ptrHeap);
}

static void HeapItemsManyItems()
{
	Vector *ptrVector;
	Heap *ptrHeap;
	
	printf("HeapItemsManyItems:\n");
	printf("\t\t\t");		
	ptrVector = VectorCreate (5, 3);
	
	VectorAdd (ptrVector ,1);
	VectorAdd (ptrVector ,50); 
	VectorAdd (ptrVector ,70); 
	VectorAdd (ptrVector ,55); 
	VectorAdd (ptrVector ,74); 
	VectorAdd (ptrVector ,80); 
	VectorAdd (ptrVector ,93); 
	VectorAdd (ptrVector ,200); 
	VectorAdd (ptrVector ,334); 
		
	ptrHeap = HeapBuild(ptrVector) ;

	if ( HeapItemsNum(ptrHeap) == 9 )
     {
	  puts(s_pass);    
     }
     else
     {
       puts(s_failed);   
     }
	
	VectorDestroy(ptrVector);
	HeapDestroy(ptrHeap);
}

static void HeapItemsAfterInsert()
{
	Vector *ptrVector;
	Heap *ptrHeap;
	
	printf("HeapItemsAfterInsert:\n");
	printf("\t\t\t");		
	ptrVector = VectorCreate (5, 3);
	
	VectorAdd (ptrVector ,1);
	VectorAdd (ptrVector ,50); 
	VectorAdd (ptrVector ,70); 
	VectorAdd (ptrVector ,55); 
	VectorAdd (ptrVector ,74); 
	VectorAdd (ptrVector ,80); 
	VectorAdd (ptrVector ,93); 
	VectorAdd (ptrVector ,200); 
	VectorAdd (ptrVector ,334); 
		
	ptrHeap = HeapBuild(ptrVector) ;
	
	HeapInsert(ptrHeap , 579);
	
	if ( HeapItemsNum(ptrHeap) == 10 )
     {
	  puts(s_pass);    
     }
     else
     {
       puts(s_failed);   
     }
	
	VectorDestroy(ptrVector);
	HeapDestroy(ptrHeap);
}

static void HeapItemsAfterExtract()
{
	Vector *ptrVector;
	Heap *ptrHeap;
	int max;
	
	printf("HeapItemsAfterExtract:\n");
	printf("\t\t\t");		
	ptrVector = VectorCreate (5, 3);
	
	VectorAdd (ptrVector ,1);
	VectorAdd (ptrVector ,50); 
	VectorAdd (ptrVector ,70); 
	VectorAdd (ptrVector ,55); 
	VectorAdd (ptrVector ,74); 
	VectorAdd (ptrVector ,80); 
	VectorAdd (ptrVector ,93); 
	VectorAdd (ptrVector ,200); 
	VectorAdd (ptrVector ,334); 
		
	ptrHeap = HeapBuild(ptrVector) ;
	
	HeapExtractMax(ptrHeap , &max);
	
	if ( HeapItemsNum(ptrHeap) == 8 )
     {
	  puts(s_pass);    
     }
     else
     {
       puts(s_failed);   
     }
	
	VectorDestroy(ptrVector);
	HeapDestroy(ptrHeap);
}

static void HeapItemsAfterTwoInsert()
{
	Vector *ptrVector;
	Heap *ptrHeap;
	
	printf("HeapItemsAfterTwoInsert:\n");
	printf("\t\t\t");		
	ptrVector = VectorCreate (5, 3);
	
	VectorAdd (ptrVector ,1);
	VectorAdd (ptrVector ,50); 
	VectorAdd (ptrVector ,70); 
	VectorAdd (ptrVector ,55); 
	VectorAdd (ptrVector ,74); 
	VectorAdd (ptrVector ,80); 
	VectorAdd (ptrVector ,93); 
	VectorAdd (ptrVector ,200); 
	VectorAdd (ptrVector ,334); 
		
	ptrHeap = HeapBuild(ptrVector) ;
	
	HeapInsert(ptrHeap , 579);
	HeapInsert(ptrHeap , 578);
	
	if ( HeapItemsNum(ptrHeap) == 11 )
     {
	  puts(s_pass);    
     }
     else
     {
       puts(s_failed);   
     }
	
	VectorDestroy(ptrVector);
	HeapDestroy(ptrHeap);
}

static void HeapItemsAfterTwoExtract()
{
	Vector *ptrVector;
	Heap *ptrHeap;
	int max;
	
	printf("HeapItemsAfterTwoExtract:\n");
	printf("\t\t\t");		
	ptrVector = VectorCreate (5, 3);
	
	VectorAdd (ptrVector ,1);
	VectorAdd (ptrVector ,50); 
	VectorAdd (ptrVector ,70); 
	VectorAdd (ptrVector ,55); 
	VectorAdd (ptrVector ,74); 
	VectorAdd (ptrVector ,80); 
	VectorAdd (ptrVector ,93); 
	VectorAdd (ptrVector ,200); 
	VectorAdd (ptrVector ,334); 
		
	ptrHeap = HeapBuild(ptrVector) ;
	
	HeapExtractMax(ptrHeap , &max);
	HeapExtractMax(ptrHeap , &max);
	
	if ( HeapItemsNum(ptrHeap) == 7 )
     {
	  puts(s_pass);    
     }
     else
     {
       puts(s_failed);   
     }
	
	VectorDestroy(ptrVector);
	HeapDestroy(ptrHeap);
}

/* ----------------------- HeapInsert tests ------------------------- */

static void HeapInsertNormal()
{
	Vector *ptrVector;
	Heap *ptrHeap;
	ADTErr result ;	
	
	printf("HeapInsertNormal:\n");
	
	ptrVector = VectorCreate (5, 3);
	
	VectorAdd (ptrVector ,65);
	VectorAdd (ptrVector ,45); 
	VectorAdd (ptrVector ,15); 
	VectorAdd (ptrVector ,78); 
	VectorAdd (ptrVector ,100); 
	VectorAdd (ptrVector ,2); 
	VectorAdd (ptrVector ,4); 
	VectorAdd (ptrVector ,3); 
	VectorAdd (ptrVector ,12);  
	
	VectorPrint(ptrVector);
	putchar('\n');
	ptrHeap = HeapBuild(ptrVector);
	
	HeapPrint(ptrHeap);
	putchar('\n');	
	
	result = HeapInsert(ptrHeap , 579);
	
	HeapPrint(ptrHeap);
	putchar('\n');	
		
	if ( result == ERR_OK )
     {
	  puts(s_pass);    
     }
     else
     {
       puts(s_failed);   
     }	
	
	VectorDestroy(ptrVector);
	HeapDestroy(ptrHeap);
}

static void HeapInsertNull()
{
	ADTErr result ;
	
	printf("HeapInsertNull: ");
	
	if ( (result = HeapInsert(NULL , 579)) == ERR_NOT_INITIALIZED )
     {
	  puts(s_pass);    
     }
     else
     {
       puts(s_failed);   
     }
}

static void HeapInsertToEmpty()
{
	Vector *ptrVector;
	Heap *ptrHeap;
	ADTErr result ;
		
	printf("HeapInsertToEmpty:\n");
	
	ptrVector = VectorCreate (5, 3);  

	ptrHeap = HeapBuild(ptrVector);
	
	HeapPrint(ptrHeap);
	putchar('\n');	
	
	result = HeapInsert(ptrHeap , 579);
	
	HeapPrint(ptrHeap);
	putchar('\n');	
		
	if ( result == ERR_OK )
     {
	  puts(s_pass);    
     }
     else
     {
       puts(s_failed);   
     }	
	
	VectorDestroy(ptrVector);
	HeapDestroy(ptrHeap);
}

static void HeapInsertTwoValues()
{
	Vector *ptrVector;
	Heap *ptrHeap;
	ADTErr result , result2 ;
		
	printf("HeapInsertTwoValues:\n");
	
	ptrVector = VectorCreate (5, 3);  

	ptrHeap = HeapBuild(ptrVector);
	
	HeapPrint(ptrHeap);
	putchar('\n');	
	
	result = HeapInsert(ptrHeap , 79);
	result2 = HeapInsert(ptrHeap , 85);
		
	HeapPrint(ptrHeap);
	putchar('\n');	
		
	if ( (result == ERR_OK) && (result2 == ERR_OK) )
     {
	  puts(s_pass);    
     }
     else
     {
       puts(s_failed);   
     }
     
	VectorDestroy(ptrVector);
	HeapDestroy(ptrHeap);     	
}

static void HeapInsertSmallValue()
{
	Vector *ptrVector;
	Heap *ptrHeap;
	ADTErr result ;
		
	printf("HeapInsertSmallValue:\n");
	
	ptrVector = VectorCreate (5, 3);
	
	VectorAdd (ptrVector ,65);
	VectorAdd (ptrVector ,45); 
	VectorAdd (ptrVector ,15); 
	VectorAdd (ptrVector ,78); 
	VectorAdd (ptrVector ,100); 
	VectorAdd (ptrVector ,2); 
	VectorAdd (ptrVector ,4); 
	VectorAdd (ptrVector ,3); 
	VectorAdd (ptrVector ,12);  
	
	VectorPrint(ptrVector);
	putchar('\n');
	ptrHeap = HeapBuild(ptrVector);
	
	HeapPrint(ptrHeap);
	putchar('\n');	
	
	result = HeapInsert(ptrHeap , 1);
	
	HeapPrint(ptrHeap);
	putchar('\n');	
		
	if ( result == ERR_OK )
     {
	  puts(s_pass);    
     }
     else
     {
       puts(s_failed);   
     }	
	
	VectorDestroy(ptrVector);
	HeapDestroy(ptrHeap);
}

static void HeapInsertSameValue()
{
	Vector *ptrVector;
	Heap *ptrHeap;
	ADTErr result ;
		
	printf("HeapInsertSameValue:\n");
	
	ptrVector = VectorCreate (5, 3);
	
	VectorAdd (ptrVector ,65);
	VectorAdd (ptrVector ,45); 
	VectorAdd (ptrVector ,15); 
	VectorAdd (ptrVector ,78); 
	VectorAdd (ptrVector ,100); 
	VectorAdd (ptrVector ,2); 
	VectorAdd (ptrVector ,4); 
	VectorAdd (ptrVector ,3); 
	VectorAdd (ptrVector ,12);  
	
	VectorPrint(ptrVector);
	putchar('\n');
	ptrHeap = HeapBuild(ptrVector);
	
	HeapPrint(ptrHeap);
	putchar('\n');	
	
	result = HeapInsert(ptrHeap , 12);
	
	HeapPrint(ptrHeap);
	putchar('\n');	
		
	if ( result == ERR_OK )
     {
	  puts(s_pass);    
     }
     else
     {
       puts(s_failed);   
     }	
	
	VectorDestroy(ptrVector);
	HeapDestroy(ptrHeap);
}

static void HeapInsertMiddleValue()
{
	Vector *ptrVector;
	Heap *ptrHeap;
	ADTErr result ;
		
	printf("HeapInsertMiddleValue:\n");
	
	ptrVector = VectorCreate (5, 3);
	
	VectorAdd (ptrVector ,65);
	VectorAdd (ptrVector ,45); 
	VectorAdd (ptrVector ,15); 
	VectorAdd (ptrVector ,78); 
	VectorAdd (ptrVector ,100); 
	VectorAdd (ptrVector ,2); 
	VectorAdd (ptrVector ,4); 
	VectorAdd (ptrVector ,3); 
	VectorAdd (ptrVector ,12);  
	
	VectorPrint(ptrVector);
	putchar('\n');
	ptrHeap = HeapBuild(ptrVector);
	
	HeapPrint(ptrHeap);
	putchar('\n');	
	
	result = HeapInsert(ptrHeap , 95);
	
	HeapPrint(ptrHeap);
	putchar('\n');	
		
	if ( result == ERR_OK )
     {
	  puts(s_pass);    
     }
     else
     {
       puts(s_failed);   
     }	
	
	VectorDestroy(ptrVector);
	HeapDestroy(ptrHeap);
}

/* ----------------------- HeapMax tests ----------------------- */

static void HeapMaxNormal()
{
	Vector *ptrVector;
	Heap *ptrHeap;
	int max;
	ADTErr result ;
	
	printf("HeapMaxNormal:\n");
	printf("\t\t\t");		
	ptrVector = VectorCreate (5, 3);
	
	VectorAdd (ptrVector ,65);
	VectorAdd (ptrVector ,45); 
	VectorAdd (ptrVector ,15); 
	VectorAdd (ptrVector ,78); 
	VectorAdd (ptrVector ,100); 
	VectorAdd (ptrVector ,2); 
	VectorAdd (ptrVector ,4); 
	VectorAdd (ptrVector ,3); 
	VectorAdd (ptrVector ,12);  
	ptrHeap = HeapBuild(ptrVector);

	result = HeapMax(ptrHeap , &max);
	if ( (max == 100) && (result==ERR_OK) )
     {
	  puts(s_pass);    
     }
     else
     {
       puts(s_failed);   
     }
	
	VectorDestroy(ptrVector);
	HeapDestroy(ptrHeap);
}

static void HeapMaxNullHeap()
{
	int max;
	ADTErr result ;
	printf("HeapMaxNullHeap:\n");
	printf("\t\t\t");		
	result = HeapMax(NULL , &max);
	if ( result==ERR_NOT_INITIALIZED )
     {
	  puts(s_pass);    
     }
     else
     {
       puts(s_failed);   
     }
}

static void HeapMaxNullPointerData()
{
	Vector *ptrVector;
	Heap *ptrHeap;
	ADTErr result ;
	
	printf("HeapMaxNullPointerData:\n");
	printf("\t\t\t");		
	ptrVector = VectorCreate (5, 3);
	
	VectorAdd (ptrVector ,65);
	VectorAdd (ptrVector ,45); 
	VectorAdd (ptrVector ,15); 
	VectorAdd (ptrVector ,78); 
	VectorAdd (ptrVector ,100); 
	VectorAdd (ptrVector ,2); 
	VectorAdd (ptrVector ,4); 
	VectorAdd (ptrVector ,3); 
	VectorAdd (ptrVector ,12);  
	ptrHeap = HeapBuild(ptrVector);

	result = HeapMax(ptrHeap , NULL);
	if ( result==ERR_NOT_INITIALIZED )
     {
	  puts(s_pass);    
     }
     else
     {
       puts(s_failed);   
     }
	
	VectorDestroy(ptrVector);
	HeapDestroy(ptrHeap);
}

static void HeapMaxEmptyHeap()
{
	Vector *ptrVector;
	Heap *ptrHeap;
	int max;
	ADTErr result ;
	
	printf("HeapMaxEmptyHeap:\n");
	printf("\t\t\t");		
	ptrVector = VectorCreate (5, 3);
 
	ptrHeap = HeapBuild(ptrVector);

	result = HeapMax(ptrHeap , &max);
	if ( result==ERR_UNDERFLOW )
     {
	  puts(s_pass);    
     }
     else
     {
       puts(s_failed);   
     }
	
	VectorDestroy(ptrVector);
	HeapDestroy(ptrHeap);
}

static void HeapMaxOneValue()
{
	Vector *ptrVector;
	Heap *ptrHeap;
	int max;
	ADTErr result ;
	
	printf("HeapMaxOneValue:\n");
	printf("\t\t\t");		
	ptrVector = VectorCreate (5, 3);
	
	VectorAdd (ptrVector ,65);  
	ptrHeap = HeapBuild(ptrVector);

	result = HeapMax(ptrHeap , &max);
	if ( (max == 65) && (result==ERR_OK) )
     {
	  puts(s_pass);    
     }
     else
     {
       puts(s_failed);   
     }
	
	VectorDestroy(ptrVector);
	HeapDestroy(ptrHeap);
}

/* ----------------------- HeapExtractMax tests ----------------------- */

static void HeapExtractMaxNormal()
{
	Vector *ptrVector;
	Heap *ptrHeap;
	int max;
	ADTErr result ;
		
	printf("HeapExtractMaxNormal:\n");
	
	ptrVector = VectorCreate (5, 3);
	
	VectorAdd (ptrVector ,65);
	VectorAdd (ptrVector ,45); 
	VectorAdd (ptrVector ,15); 
	VectorAdd (ptrVector ,78); 
	VectorAdd (ptrVector ,100); 
	VectorAdd (ptrVector ,2); 
	VectorAdd (ptrVector ,4); 
	VectorAdd (ptrVector ,3); 
	VectorAdd (ptrVector ,12);  
	
	VectorPrint(ptrVector);
	putchar('\n');
	ptrHeap = HeapBuild(ptrVector);
	
	HeapPrint(ptrHeap);
	putchar('\n');	
	
	result = HeapExtractMax(ptrHeap , &max);
	
	HeapPrint(ptrHeap);
	putchar('\n');	
	
	if ( (result == ERR_OK) && (max == 100) )
     {
	  puts(s_pass);    
     }
     else
     {
       puts(s_failed);   
     }
	
	VectorDestroy(ptrVector);
	HeapDestroy(ptrHeap);
}

static void HeapExtractMaxNullHeap()
{
	int max;
	ADTErr result ;
		
	printf("HeapExtractMaxNullHeap: ");

	result = HeapExtractMax(NULL , &max);
	
	if ( result == ERR_NOT_INITIALIZED )
     {
	  puts(s_pass);    
     }
     else
     {
       puts(s_failed);   
     }
}

static void HeapExtractMaxNullPointerData()
{
	Vector *ptrVector;
	Heap *ptrHeap;
	ADTErr result ;
		
	printf("HeapExtractMaxNullPointerData:\n");
	
	ptrVector = VectorCreate (5, 3);
	
	VectorAdd (ptrVector ,65);
	VectorAdd (ptrVector ,45); 
	VectorAdd (ptrVector ,15); 
	VectorAdd (ptrVector ,78); 
	VectorAdd (ptrVector ,100); 
	VectorAdd (ptrVector ,2); 
	VectorAdd (ptrVector ,4); 
	VectorAdd (ptrVector ,3); 
	VectorAdd (ptrVector ,12);  
	
	VectorPrint(ptrVector);
	putchar('\n');
	ptrHeap = HeapBuild(ptrVector);
	
	HeapPrint(ptrHeap);
	putchar('\n');	
	
	result = HeapExtractMax(ptrHeap , NULL);
	
	HeapPrint(ptrHeap);
	putchar('\n');	
	
	if ( result == ERR_NOT_INITIALIZED )
     {
	  puts(s_pass);    
     }
     else
     {
       puts(s_failed);   
     }
	
	VectorDestroy(ptrVector);
	HeapDestroy(ptrHeap);
}

static void HeapExtractMaxNullTwoPointer()
{
	ADTErr result ;
		
	printf("HeapExtractMaxNullTwoPointer: ");

	result = HeapExtractMax(NULL , NULL);
	
	if ( result == ERR_NOT_INITIALIZED )
     {
	  puts(s_pass);    
     }
     else
     {
       puts(s_failed);   
     }
}

static void HeapExtractMaxEmptyHeap()
{
	Vector *ptrVector;
	Heap *ptrHeap;
	int max;
	ADTErr result ;
		
	printf("HeapExtractMaxEmptyHeap:\n");
	
	ptrVector = VectorCreate (5, 3); 
	
	VectorPrint(ptrVector);
	putchar('\n');
	ptrHeap = HeapBuild(ptrVector);
	
	HeapPrint(ptrHeap);
	putchar('\n');	
	
	result = HeapExtractMax(ptrHeap , &max);
	
	HeapPrint(ptrHeap);
	putchar('\n');	
	
	if ( result == ERR_UNDERFLOW )
     {
	  puts(s_pass);    
     }
     else
     {
       puts(s_failed);   
     }
	
	VectorDestroy(ptrVector);
	HeapDestroy(ptrHeap);
}

static void HeapExtractMaxOneItem()
{
	Vector *ptrVector;
	Heap *ptrHeap;
	int max;
	ADTErr result ;
		
	printf("HeapExtractMaxOneItem:\n");
	
	ptrVector = VectorCreate (5, 3);
	
	VectorAdd (ptrVector ,65);  
	
	VectorPrint(ptrVector);
	putchar('\n');
	ptrHeap = HeapBuild(ptrVector);
	
	HeapPrint(ptrHeap);
	putchar('\n');	
	
	result = HeapExtractMax(ptrHeap , &max);
	
	HeapPrint(ptrHeap);
	putchar('\n');	
	
	if ( (result == ERR_OK) && (max == 65) )
     {
	  puts(s_pass);    
     }
     else
     {
       puts(s_failed);   
     }
	
	VectorDestroy(ptrVector);
	HeapDestroy(ptrHeap);
}

static void HeapExtractMaxTwoItems()
{
	Vector *ptrVector;
	Heap *ptrHeap;
	int max;
	ADTErr result ;
		
	printf("HeapExtractMaxTwoItems:\n");
	
	ptrVector = VectorCreate (5, 3);
	
	VectorAdd (ptrVector ,65);  
	VectorAdd (ptrVector ,75);  
	
	VectorPrint(ptrVector);
	putchar('\n');
	ptrHeap = HeapBuild(ptrVector);
	
	HeapPrint(ptrHeap);
	putchar('\n');	
	
	result = HeapExtractMax(ptrHeap , &max);
	
	HeapPrint(ptrHeap);
	putchar('\n');	
	
	if ( (result == ERR_OK) && (max == 75) )
     {
	  puts(s_pass);    
     }
     else
     {
       puts(s_failed);   
     }
	
	VectorDestroy(ptrVector);
	HeapDestroy(ptrHeap);
}

static void HeapExtractMaxTwoActions()
{
	Vector *ptrVector;
	Heap *ptrHeap;
	int max;
	ADTErr result ;
		
	printf("HeapExtractMaxTwoActions:\n");
	
	ptrVector = VectorCreate (5, 3);
	
	VectorAdd (ptrVector ,65);
	VectorAdd (ptrVector ,45); 
	VectorAdd (ptrVector ,15); 
	VectorAdd (ptrVector ,78); 
	VectorAdd (ptrVector ,100); 
	VectorAdd (ptrVector ,2); 
	VectorAdd (ptrVector ,4); 
	VectorAdd (ptrVector ,3); 
	VectorAdd (ptrVector ,12);  
	
	VectorPrint(ptrVector);
	putchar('\n');
	ptrHeap = HeapBuild(ptrVector);
	
	HeapPrint(ptrHeap);
	putchar('\n');	
	
	result = HeapExtractMax(ptrHeap , &max);
	result = HeapExtractMax(ptrHeap , &max);
	
	HeapPrint(ptrHeap);
	putchar('\n');	
	
	if ( (result == ERR_OK) && (max == 78) )
     {
	  puts(s_pass);    
     }
     else
     {
       puts(s_failed);   
     }
	
	VectorDestroy(ptrVector);
	HeapDestroy(ptrHeap);
}

static void HeapExtractMaxThreeActions()
{
	Vector *ptrVector;
	Heap *ptrHeap;
	int max;
	ADTErr result ;
		
	printf("HeapExtractMaxTwoActions:\n");
	
	ptrVector = VectorCreate (5, 3);
	
	VectorAdd (ptrVector ,132);
	VectorAdd (ptrVector ,45); 
	VectorAdd (ptrVector ,956); 
	VectorAdd (ptrVector ,78); 
	VectorAdd (ptrVector ,100); 
	VectorAdd (ptrVector ,2); 
	VectorAdd (ptrVector ,579); 
	VectorAdd (ptrVector ,334); 
	VectorAdd (ptrVector ,12);  
	
	VectorPrint(ptrVector);
	putchar('\n');
	ptrHeap = HeapBuild(ptrVector);
	
	HeapPrint(ptrHeap);
	putchar('\n');	
	
	result = HeapExtractMax(ptrHeap , &max);
	result = HeapExtractMax(ptrHeap , &max);
	result = HeapExtractMax(ptrHeap , &max);
		
	HeapPrint(ptrHeap);
	putchar('\n');	
	
	if ( (result == ERR_OK) && (max == 334) )
     {
	  puts(s_pass);    
     }
     else
     {
       puts(s_failed);   
     }
	
	VectorDestroy(ptrVector);
	HeapDestroy(ptrHeap);
}
