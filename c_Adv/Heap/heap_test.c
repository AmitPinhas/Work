#include <stdio.h>
#include "heap.h"


int PrintVector(void* _element, size_t _index, void* _context);
int	Comparator(const void *_left, const void *_right);
int	ActFunction(const void *_elem, void * _context);

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
static void HeapMaxEmptyHeap();
static void HeapMaxOneValue();

/* ----------------------- HeapExtractMax tests ----------------------- */

static void HeapExtractMaxNormal();
static void HeapExtractMaxNullHeap();
static void HeapExtractMaxEmptyHeap();
static void HeapExtractMaxOneItem();
static void HeapExtractMaxTwoItems();


/* ------------------------- Heap Sort ----------------------------- */
static void HeapSortPositive();


/* ----------------------- Main ----------------------------------- */

int main()
{

	printf("=====================HeapBuild tests============================\n");
	HeapBuildTestNormal();
	HeapBuildTestNull();
	HeapBuildTestEmptyVector();
	HeapBuildTestOneItem();
	HeapBuildTestTwoItems(); 
	HeapBuildTestThreeItemsRightBig();
	HeapBuildTestThreeItemsLeftBig();
	HeapBuildTestAlreadyHeap();
	HeapBuildTestAllParentsSmall();
	
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
	HeapMaxEmptyHeap();
	HeapMaxOneValue();
	
	printf("\n=====================HeapExtractMax tests=====================\n\n");			
	HeapExtractMaxNormal();
	HeapExtractMaxNullHeap();
	HeapExtractMaxEmptyHeap();
	HeapExtractMaxOneItem();
     HeapExtractMaxTwoItems();

	printf("\n=====================Heap Sort tests=====================\n\n");		
     HeapSortPositive(); 
       
	return 0;
}



/* ----------------------- HeapBuild tests ------------------------- */

static void HeapBuildTestNormal()
{
	Vector *ptrVector;
	Heap *ptrHeap;	
	int num65 = 65 , num45 = 45 , num15 = 15 , num78 = 78 , num100 = 100 , num2 = 2 , num4 = 4 , num3 = 3 , num12 =12 ;
	
	ptrVector = VectorCreate (5, 3);
	
	VectorAppend (ptrVector , &num65);
	VectorAppend (ptrVector , &num45); 
	VectorAppend (ptrVector , &num15); 
	VectorAppend (ptrVector , &num78); 
	VectorAppend (ptrVector , &num100); 
	VectorAppend (ptrVector , &num2); 
	VectorAppend (ptrVector , &num4); 
	VectorAppend (ptrVector , &num3); 
	VectorAppend (ptrVector , &num12);  
	
	VectorForEach(ptrVector , PrintVector , NULL);
	
	putchar('\n');
	ptrHeap = HeapBuild(ptrVector , Comparator);
	
	HeapForEach( ptrHeap , ActFunction , NULL);
	putchar('\n');	
	
	if ( ptrHeap != NULL )
     {
	  puts(s_pass);    
     }
     else
     {
       puts(s_failed);   
     }	
	
	VectorDestroy(&ptrVector , NULL);
	HeapDestroy(&ptrHeap);
}

static void HeapBuildTestNull()
{
	if ( HeapBuild(NULL , Comparator) == NULL )
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
	
	ptrVector = VectorCreate (5, 3); 
	
	VectorForEach(ptrVector , PrintVector , NULL);
	putchar('\n');
	
	if ( (ptrHeap = HeapBuild(ptrVector , Comparator)) != NULL )
	{
		puts(s_pass);
	}
	else
	{
	     puts(s_failed);
	}
	
	HeapForEach( ptrHeap , ActFunction , NULL);
	putchar('\n');	
	VectorDestroy(&ptrVector , NULL);
	HeapDestroy(&ptrHeap);
}

static void HeapBuildTestOneItem()
{
	Vector *ptrVector;
	Heap *ptrHeap;
	int num65 = 65;
	
	ptrVector = VectorCreate (5, 3);
	
	VectorAppend (ptrVector , &num65);
	
	VectorForEach(ptrVector , PrintVector , NULL);
	putchar('\n');
	ptrHeap = HeapBuild(ptrVector , Comparator);
	
	HeapForEach( ptrHeap , ActFunction , NULL);
	putchar('\n');	
	
	if ( ptrHeap != NULL )
     {
	  puts(s_pass);    
     }
     else
     {
       puts(s_failed);   
     }	
	
	VectorDestroy(&ptrVector , NULL);
	HeapDestroy(&ptrHeap);
}

static void HeapBuildTestTwoItems()
{
	Vector *ptrVector;
	Heap *ptrHeap;
	int num65 = 65 , num100 = 100 ;
	
	ptrVector = VectorCreate (5, 3);
	
	VectorAppend (ptrVector , &num65);
	VectorAppend (ptrVector , &num100);
	
	VectorForEach(ptrVector , PrintVector , NULL);
	putchar('\n');
	ptrHeap = HeapBuild(ptrVector , Comparator);
	
	HeapForEach( ptrHeap , ActFunction , NULL);
	putchar('\n');	
	
	if ( ptrHeap != NULL )
     {
	  puts(s_pass);    
     }
     else
     {
       puts(s_failed);   
     }	
	
	VectorDestroy(&ptrVector , NULL);
	HeapDestroy(&ptrHeap);
}

static void HeapBuildTestThreeItemsRightBig()
{
	Vector *ptrVector;
	Heap *ptrHeap;
	int num65 = 65 , num75 = 75 , num85 = 85 ;
	
	ptrVector = VectorCreate (5, 3);
	
	VectorAppend (ptrVector , &num65);
	VectorAppend (ptrVector , &num75);
	VectorAppend (ptrVector , &num85);
		
	VectorForEach(ptrVector , PrintVector , NULL);
	putchar('\n');
	ptrHeap = HeapBuild(ptrVector , Comparator);
	
	HeapForEach( ptrHeap , ActFunction , NULL);
	putchar('\n');	
	
	if ( ptrHeap != NULL )
     {
	  puts(s_pass);    
     }
     else
     {
       puts(s_failed);   
     }	
	
	VectorDestroy(&ptrVector , NULL);
	HeapDestroy(&ptrHeap);
}

static void HeapBuildTestThreeItemsLeftBig()
{
	Vector *ptrVector;
	Heap *ptrHeap;
	int num65 = 65 , num175 = 175 , num85 = 85 ;
	
	ptrVector = VectorCreate (5, 3);
	
	VectorAppend (ptrVector , &num65);
	VectorAppend (ptrVector , &num175);
	VectorAppend (ptrVector , &num85);
		
	VectorForEach(ptrVector , PrintVector , NULL);
	putchar('\n');
	ptrHeap = HeapBuild(ptrVector , Comparator);
	
	HeapForEach( ptrHeap , ActFunction , NULL);
	putchar('\n');	
	
	if ( ptrHeap != NULL )
     {
	  puts(s_pass);    
     }
     else
     {
       puts(s_failed);   
     }	
	
	VectorDestroy(&ptrVector , NULL);
	HeapDestroy(&ptrHeap);
}

static void HeapBuildTestAlreadyHeap()
{
	Vector *ptrVector;
	Heap *ptrHeap;
	int num200 = 200 , num100 = 100 , num185 = 185 , num50 = 50 , num80 = 80 ;
	
	ptrVector = VectorCreate (5, 3);
	
	VectorAppend (ptrVector , &num200);
	VectorAppend (ptrVector , &num100);
	VectorAppend (ptrVector , &num185);
	VectorAppend (ptrVector , &num50);
	VectorAppend (ptrVector , &num80);
				
	VectorForEach(ptrVector , PrintVector , NULL);
	putchar('\n');
	ptrHeap = HeapBuild(ptrVector , Comparator);
	
	HeapForEach( ptrHeap , ActFunction , NULL);
	putchar('\n');	
	
	if ( ptrHeap != NULL )
     {
	  puts(s_pass);    
     }
     else
     {
       puts(s_failed);   
     }	
	
	VectorDestroy(&ptrVector , NULL);
	HeapDestroy(&ptrHeap);
}

static void HeapBuildTestAllParentsSmall()
{
	Vector *ptrVector;
	Heap *ptrHeap;
	int num200 = 200 , num100 = 100 , num185 = 185 , num50 = 50 , num80 = 80 , num90 = 90 , num800 =800 ;
	
	ptrVector = VectorCreate (5, 3);

	VectorAppend (ptrVector , &num50);	
	VectorAppend (ptrVector , &num80);	
	VectorAppend (ptrVector , &num90);		
	VectorAppend (ptrVector , &num200);
	VectorAppend (ptrVector , &num100);
	VectorAppend (ptrVector , &num185);
	VectorAppend (ptrVector , &num800);
				
	VectorForEach(ptrVector , PrintVector , NULL);
	putchar('\n');
	ptrHeap = HeapBuild(ptrVector , Comparator);
	
	HeapForEach( ptrHeap , ActFunction , NULL);
	putchar('\n');	
	
	if ( ptrHeap != NULL )
     {
	  puts(s_pass);    
     }
     else
     {
       puts(s_failed);   
     }	
	
	VectorDestroy(&ptrVector , NULL);
	HeapDestroy(&ptrHeap);
}

/* ----------------------- HeapDestroy tests ------------------------ */

static void HeapDestroyNull()
{
	HeapDestroy(NULL);
	puts(s_pass);		
}

static void HeapDestroyDoubleFree()
{
	Vector *ptrVector;
	Heap *ptrHeap;
	int num200 = 200 , num100 = 100 , num185 = 185 , num50 = 50 , num80 = 80 , num90 = 90 , num800 =800 ;
		
	ptrVector = VectorCreate (5, 3);
	
	VectorAppend (ptrVector , &num50);	
	VectorAppend (ptrVector , &num80);	
	VectorAppend (ptrVector , &num90);		
	VectorAppend (ptrVector , &num200);
	VectorAppend (ptrVector , &num100);
	VectorAppend (ptrVector , &num185);
	VectorAppend (ptrVector , &num800);
	
	ptrHeap = HeapBuild(ptrVector , Comparator);
	
	VectorDestroy(&ptrVector , NULL);
	HeapDestroy(&ptrHeap);
	HeapDestroy(&ptrHeap);
	puts(s_pass);
}

/* ----------------------- HeapItemsNum tests ----------------------- */

static void HeapItemsNumNull()
{	
    if ( HeapSize(NULL) == 0 )
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

	ptrVector = VectorCreate (5, 3); 
	
	ptrHeap = HeapBuild(ptrVector , Comparator) ;

	if ( HeapSize(ptrHeap) == 0 )
     {
	  puts(s_pass);    
     }
     else
     {
       puts(s_failed);   
     }
	
	VectorDestroy(&ptrVector , NULL);
	HeapDestroy(&ptrHeap);
}

static void HeapItemsOneItem()
{
	Vector *ptrVector;
	Heap *ptrHeap;
	int num1 = 1 ;
		
	ptrVector = VectorCreate (5, 3); 
	VectorAppend (ptrVector , &num1);
		
	ptrHeap = HeapBuild(ptrVector ,Comparator ) ;

	if ( HeapSize(ptrHeap) == 1 )
     {
	  puts(s_pass);    
     }
     else
     {
       puts(s_failed);   
     }
	
	VectorDestroy(&ptrVector , NULL);
	HeapDestroy(&ptrHeap);
}

static void HeapItemsManyItems()
{
	Vector *ptrVector;
	Heap *ptrHeap;
	int num200 = 200 , num100 = 100 , num185 = 185 , num50 = 50 , num80 = 80 , num90 = 90 , num800 =800 ;
				
	ptrVector = VectorCreate (5, 3);
	
	VectorAppend (ptrVector , &num50);	
	VectorAppend (ptrVector , &num80);	
	VectorAppend (ptrVector , &num90);		
	VectorAppend (ptrVector , &num200);
	VectorAppend (ptrVector , &num100);
	VectorAppend (ptrVector , &num185);
	VectorAppend (ptrVector , &num800);
		
	ptrHeap = HeapBuild(ptrVector , Comparator) ;

	if ( HeapSize(ptrHeap) == 7 )
     {
	  puts(s_pass);    
     }
     else
     {
       puts(s_failed);   
     }
	
	VectorDestroy(&ptrVector , NULL);
	HeapDestroy(&ptrHeap);
}

static void HeapItemsAfterInsert()
{
	Vector *ptrVector;
	Heap *ptrHeap;
	int num200 = 200 , num100 = 100 , num185 = 185 , num50 = 50 , num80 = 80 , num90 = 90 , num800 =800 , num324=324;
				
	ptrVector = VectorCreate (5, 3);
	
	VectorAppend (ptrVector , &num50);	
	VectorAppend (ptrVector , &num80);	
	VectorAppend (ptrVector , &num90);		
	VectorAppend (ptrVector , &num200);
	VectorAppend (ptrVector , &num100);
	VectorAppend (ptrVector , &num185);
	VectorAppend (ptrVector , &num800);
		
	ptrHeap = HeapBuild(ptrVector ,Comparator ) ;
	
	HeapInsert(ptrHeap , &num324);
	
	if ( HeapSize(ptrHeap) == 8 )
     {
	  puts(s_pass);    
     }
     else
     {
       puts(s_failed);   
     }
	
	VectorDestroy(&ptrVector , NULL);
	HeapDestroy(&ptrHeap);
}

static void HeapItemsAfterExtract()
{
	Vector *ptrVector;
	Heap *ptrHeap;
	int num200 = 200 , num100 = 100 , num185 = 185 , num50 = 50 , num80 = 80 , num90 = 90 , num800 =800 ; 
				
	ptrVector = VectorCreate (5, 3);
	
	VectorAppend (ptrVector , &num50);	
	VectorAppend (ptrVector , &num80);	
	VectorAppend (ptrVector , &num90);		
	VectorAppend (ptrVector , &num200);
	VectorAppend (ptrVector , &num100);
	VectorAppend (ptrVector , &num185);
	VectorAppend (ptrVector , &num800); 
		
	ptrHeap = HeapBuild(ptrVector , Comparator) ;
	
     HeapExtract(ptrHeap);
	
	if ( HeapSize(ptrHeap) == 6 )
     {
	  puts(s_pass);    
     }
     else
     {
       puts(s_failed);   
     }
	
	VectorDestroy(&ptrVector , NULL);
	HeapDestroy(&ptrHeap);
}

static void HeapItemsAfterTwoInsert()
{
	Vector *ptrVector;
	Heap *ptrHeap;
	int num200 = 200 , num100 = 100 , num185 = 185 , num50 = 50 , num80 = 80 , num90 = 90 , num800 =800 , num324=324 , num22=22; 
				
	ptrVector = VectorCreate (5, 3);
	
	VectorAppend (ptrVector , &num50);	
	VectorAppend (ptrVector , &num80);	
	VectorAppend (ptrVector , &num90);		
	VectorAppend (ptrVector , &num200);
	VectorAppend (ptrVector , &num100);
	VectorAppend (ptrVector , &num185);
	VectorAppend (ptrVector , &num800);
		
	ptrHeap = HeapBuild(ptrVector ,Comparator ) ;
	
	HeapInsert(ptrHeap , &num324);
	HeapInsert(ptrHeap , &num22);
		
	if ( HeapSize(ptrHeap) == 9 )
     {
	  puts(s_pass);    
     }
     else
     {
       puts(s_failed);   
     }
	
	VectorDestroy(&ptrVector , NULL);
	HeapDestroy(&ptrHeap);
}

static void HeapItemsAfterTwoExtract()
{
	Vector *ptrVector;
	Heap *ptrHeap;
	int num200 = 200 , num100 = 100 , num185 = 185 , num50 = 50 , num80 = 80 , num90 = 90 , num800 =800 ; 
				
	ptrVector = VectorCreate (5, 3);
	
	VectorAppend (ptrVector , &num50);	
	VectorAppend (ptrVector , &num80);	
	VectorAppend (ptrVector , &num90);		
	VectorAppend (ptrVector , &num200);
	VectorAppend (ptrVector , &num100);
	VectorAppend (ptrVector , &num185);
	VectorAppend (ptrVector , &num800); 
		
	ptrHeap = HeapBuild(ptrVector , Comparator) ;
	
     HeapExtract(ptrHeap);
	HeapExtract(ptrHeap);
		
	if ( HeapSize(ptrHeap) == 5 )
     {
	  puts(s_pass);    
     }
     else
     {
       puts(s_failed);   
     }
	
	VectorDestroy(&ptrVector , NULL);
	HeapDestroy(&ptrHeap);
}

/* ------------------------------------------------------ HeapInsert tests ----------------------------------------------------------------- */

static void HeapInsertNormal()
{
	Vector *ptrVector;
	Heap *ptrHeap;	
	HeapResult result ; 
	int num200 = 200 , num100 = 100 , num185 = 185 , num50 = 50 , num80 = 80 , num90 = 90 , num800 =800 , num579=579 ; 
				
	ptrVector = VectorCreate (5, 3);
	
	VectorAppend (ptrVector , &num50);	
	VectorAppend (ptrVector , &num80);	
	VectorAppend (ptrVector , &num90);		
	VectorAppend (ptrVector , &num200);
	VectorAppend (ptrVector , &num100);
	VectorAppend (ptrVector , &num185);
	VectorAppend (ptrVector , &num800); 
	
	VectorForEach(ptrVector , PrintVector , NULL);
	putchar('\n');
	ptrHeap = HeapBuild(ptrVector , Comparator);
	
	HeapForEach( ptrHeap , ActFunction , NULL);
	putchar('\n');	
	
	result = HeapInsert(ptrHeap , &num579);
	
	HeapForEach( ptrHeap , ActFunction , NULL);
	putchar('\n');
		
	if ( result == HEAP_SUCCESS )
     {
	  puts(s_pass);    
     }
     else
     {
       puts(s_failed);   
     }	
	
	VectorDestroy(&ptrVector , NULL);
	HeapDestroy(&ptrHeap);
}

static void HeapInsertNull()
{
	HeapResult result ;
	int num579 = 579;
	
	if ( (result = HeapInsert(NULL , &num579)) == HEAP_NOT_INITIALIZED )
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
	HeapResult result ;
	int num579=579;
	
	ptrVector = VectorCreate (5, 3);  

	ptrHeap = HeapBuild(ptrVector ,Comparator );
	
	HeapForEach( ptrHeap , ActFunction , NULL);
	putchar('\n');	
	
	result = HeapInsert(ptrHeap , &num579);
	
	HeapForEach( ptrHeap , ActFunction , NULL);
	putchar('\n');	
		
	if ( result == HEAP_SUCCESS )
     {
	  puts(s_pass);    
     }
     else
     {
       puts(s_failed);   
     }	
	
	VectorDestroy(&ptrVector , NULL);
	HeapDestroy(&ptrHeap);
}

static void HeapInsertTwoValues()
{
	Vector *ptrVector;
	Heap *ptrHeap;
	HeapResult result , result2 ;
	int num79 = 79 , num85=85;
	
	ptrVector = VectorCreate (5, 3);  

	ptrHeap = HeapBuild(ptrVector ,Comparator );
	
	HeapForEach( ptrHeap , ActFunction , NULL);
	putchar('\n');	
	
	result = HeapInsert(ptrHeap , &num79);
	result2 = HeapInsert(ptrHeap , &num85);
		
	HeapForEach( ptrHeap , ActFunction , NULL);
	putchar('\n');		
		
	if ( (result == HEAP_SUCCESS) && (result2 == HEAP_SUCCESS) )
     {
	  puts(s_pass);    
     }
     else
     {
       puts(s_failed);   
     }
     
	VectorDestroy(&ptrVector , NULL);
	HeapDestroy(&ptrHeap);    	
}

static void HeapInsertSmallValue()
{
	Vector *ptrVector;
	Heap *ptrHeap;	
	HeapResult result ; 
	int num200 = 200 , num100 = 100 , num185 = 185 , num50 = 50 , num80 = 80 , num90 = 90 , num800 =800  , num1=1 ; 
				
	ptrVector = VectorCreate (5, 3);
	
	VectorAppend (ptrVector , &num50);	
	VectorAppend (ptrVector , &num80);	
	VectorAppend (ptrVector , &num90);		
	VectorAppend (ptrVector , &num200);
	VectorAppend (ptrVector , &num100);
	VectorAppend (ptrVector , &num185);
	VectorAppend (ptrVector , &num800); 
	
	VectorForEach(ptrVector , PrintVector , NULL);
	putchar('\n');
	ptrHeap = HeapBuild(ptrVector , Comparator);
	
	HeapForEach( ptrHeap , ActFunction , NULL);
	putchar('\n');	
	
	result = HeapInsert(ptrHeap , &num1);
	
	HeapForEach( ptrHeap , ActFunction , NULL);
	putchar('\n');
		
	if ( result == HEAP_SUCCESS )
     {
	  puts(s_pass);    
     }
     else
     {
       puts(s_failed);   
     }	
	
	VectorDestroy(&ptrVector , NULL);
	HeapDestroy(&ptrHeap);
}

static void HeapInsertSameValue()
{
	Vector *ptrVector;
	Heap *ptrHeap;	
	HeapResult result ; 
	int num200 = 200 , num100 = 100 , num185 = 185 , num50 = 50 , num80 = 80 , num90 = 90 , num800 =800  ; 
				
	ptrVector = VectorCreate (5, 3);
	
	VectorAppend (ptrVector , &num50);	
	VectorAppend (ptrVector , &num80);	
	VectorAppend (ptrVector , &num90);		
	VectorAppend (ptrVector , &num200);
	VectorAppend (ptrVector , &num100);
	VectorAppend (ptrVector , &num185);
	VectorAppend (ptrVector , &num800); 
	
	VectorForEach(ptrVector , PrintVector , NULL);
	putchar('\n');
	ptrHeap = HeapBuild(ptrVector , Comparator);
	
	HeapForEach( ptrHeap , ActFunction , NULL);
	putchar('\n');	
	
	result = HeapInsert(ptrHeap , &num185);
	
	HeapForEach( ptrHeap , ActFunction , NULL);
	putchar('\n');
		
	if ( result == HEAP_SUCCESS )
     {
	  puts(s_pass);    
     }
     else
     {
       puts(s_failed);   
     }	
	
	VectorDestroy(&ptrVector , NULL);
	HeapDestroy(&ptrHeap);
}

static void HeapInsertMiddleValue()
{
	Vector *ptrVector;
	Heap *ptrHeap;	
	HeapResult result ; 
	int num200 = 200 , num100 = 100 , num185 = 185 , num50 = 50 , num80 = 80 , num90 = 90 , num800 =800 , num150=150  ; 
				
	ptrVector = VectorCreate (5, 3);
	
	VectorAppend (ptrVector , &num50);	
	VectorAppend (ptrVector , &num80);	
	VectorAppend (ptrVector , &num90);		
	VectorAppend (ptrVector , &num200);
	VectorAppend (ptrVector , &num100);
	VectorAppend (ptrVector , &num185);
	VectorAppend (ptrVector , &num800); 
	
	VectorForEach(ptrVector , PrintVector , NULL);
	putchar('\n');
	ptrHeap = HeapBuild(ptrVector , Comparator);
	
	HeapForEach( ptrHeap , ActFunction , NULL);
	putchar('\n');	
	
	result = HeapInsert(ptrHeap , &num150);
	
	HeapForEach( ptrHeap , ActFunction , NULL);
	putchar('\n');
		
	if ( result == HEAP_SUCCESS )
     {
	  puts(s_pass);    
     }
     else
     {
       puts(s_failed);   
     }	
	
	VectorDestroy(&ptrVector , NULL);
	HeapDestroy(&ptrHeap);
}

/* -------------------------------------------------- HeapMax tests ----------------------- */

static void HeapMaxNormal()
{
	Vector *ptrVector;
	Heap *ptrHeap;	 
	int num200 = 200 , num100 = 100 , num185 = 185 , num50 = 50 , num80 = 80 , num90 = 90 , num800 =800  ; 
	const void* max;
				
	ptrVector = VectorCreate (5, 3);
	
	VectorAppend (ptrVector , &num50);	
	VectorAppend (ptrVector , &num80);	
	VectorAppend (ptrVector , &num90);		
	VectorAppend (ptrVector , &num200);
	VectorAppend (ptrVector , &num100);
	VectorAppend (ptrVector , &num185);
	VectorAppend (ptrVector , &num800); 
	
	ptrHeap = HeapBuild(ptrVector , Comparator);
		
	max = HeapPeek(ptrHeap );
	
		
	if ( *(int*)max == 800 )
     {
	  puts(s_pass);    
     }
     else
     {
       puts(s_failed);   
     }	
	
	VectorDestroy(&ptrVector , NULL);
	HeapDestroy(&ptrHeap);
}

static void HeapMaxNullHeap()
{
	const void* max;
	
	max = HeapPeek(NULL );	
		
	if ( max == NULL )
     {
	  puts(s_pass);    
     }
     else
     {
       puts(s_failed);   
     }	
}


static void HeapMaxEmptyHeap()
{
	Vector *ptrVector;
	Heap *ptrHeap;	
	const void* max;
				
	ptrVector = VectorCreate (5, 3);
	
	ptrHeap = HeapBuild(ptrVector , Comparator);
	
	max = HeapPeek(ptrHeap );
	
		
	if ( max == NULL )
     {
	  puts(s_pass);    
     }
     else
     {
       puts(s_failed);   
     }	
	
	VectorDestroy(&ptrVector , NULL);
	HeapDestroy(&ptrHeap);
}

static void HeapMaxOneValue()
{
	Vector *ptrVector;
	Heap *ptrHeap;	
	int num200 = 200 ; 
	const void* max;
				
	ptrVector = VectorCreate (5, 3);

	VectorAppend (ptrVector , &num200);
	
	ptrHeap = HeapBuild(ptrVector , Comparator);	
	
	max = HeapPeek(ptrHeap );
	
		
	if ( *(int*)max == 200 )
     {
	  puts(s_pass);    
     }
     else
     {
       puts(s_failed);   
     }	
	
	VectorDestroy(&ptrVector , NULL);
	HeapDestroy(&ptrHeap);
}
/* ----------------------- HeapExtractMax tests ----------------------- */

static void HeapExtractMaxNormal()
{
	Vector *ptrVector;
	Heap *ptrHeap;	 
	int num200 = 200 , num100 = 100 , num185 = 185 , num50 = 50 , num80 = 80 , num90 = 90 , num800 =800  ; 
     void* max;
				
	ptrVector = VectorCreate (5, 3);
	
	VectorAppend (ptrVector , &num50);	
	VectorAppend (ptrVector , &num80);	
	VectorAppend (ptrVector , &num90);		
	VectorAppend (ptrVector , &num200);
	VectorAppend (ptrVector , &num100);
	VectorAppend (ptrVector , &num185);
	VectorAppend (ptrVector , &num800); 
	
	ptrHeap = HeapBuild(ptrVector , Comparator);

	HeapForEach( ptrHeap , ActFunction , NULL);
	putchar('\n');	
		
	max = HeapExtract(ptrHeap );

	HeapForEach( ptrHeap , ActFunction , NULL);
	putchar('\n');		
		
	if ( *(int*)max == 800 )
     {
	  puts(s_pass);    
     }
     else
     {
       puts(s_failed);   
     }	
	
	VectorDestroy(&ptrVector , NULL);
	HeapDestroy(&ptrHeap);
}

static void HeapExtractMaxNullHeap()
{
     void* max;	
		
	max = HeapExtract(NULL );

	if ( max == NULL )
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
     void* max;
				
	ptrVector = VectorCreate (5, 3);
	
	ptrHeap = HeapBuild(ptrVector , Comparator);
		
	max = HeapExtract(ptrHeap );	
		
	if ( max == NULL )
     {
	  puts(s_pass);    
     }
     else
     {
       puts(s_failed);   
     }	
	
	VectorDestroy(&ptrVector , NULL);
	HeapDestroy(&ptrHeap);
}


static void HeapExtractMaxOneItem()
{
	Vector *ptrVector;
	Heap *ptrHeap;	 
	int num200 = 200 ; 
     void* max;
				
	ptrVector = VectorCreate (5, 3);
	
	VectorAppend (ptrVector , &num200);

	ptrHeap = HeapBuild(ptrVector , Comparator);

	HeapForEach( ptrHeap , ActFunction , NULL);
	putchar('\n');	
		
	max = HeapExtract(ptrHeap );

	HeapForEach( ptrHeap , ActFunction , NULL);
	putchar('\n');		
		
	if ( *(int*)max == 200 )
     {
	  puts(s_pass);    
     }
     else
     {
       puts(s_failed);   
     }	
	
	VectorDestroy(&ptrVector , NULL);
	HeapDestroy(&ptrHeap);
}


static void HeapExtractMaxTwoItems()
{
	Vector *ptrVector;
	Heap *ptrHeap;	 
	int num200 = 200 , num100 = 100 , num185 = 185 , num50 = 50 , num80 = 80 , num90 = 90 , num800 =800  ; 
     void* max , *max2;
				
	ptrVector = VectorCreate (5, 3);
	
	VectorAppend (ptrVector , &num50);	
	VectorAppend (ptrVector , &num80);	
	VectorAppend (ptrVector , &num90);		
	VectorAppend (ptrVector , &num200);
	VectorAppend (ptrVector , &num100);
	VectorAppend (ptrVector , &num185);
	VectorAppend (ptrVector , &num800); 
	
	ptrHeap = HeapBuild(ptrVector , Comparator);

	HeapForEach( ptrHeap , ActFunction , NULL);
	putchar('\n');	
		
	max = HeapExtract(ptrHeap );
	max2 = HeapExtract(ptrHeap );
	
	HeapForEach( ptrHeap , ActFunction , NULL);
	putchar('\n');		
		
	if ( *(int*)max == 800  && *(int*)max2 == 200)
     {
	  puts(s_pass);    
     }
     else
     {
       puts(s_failed);   
     }	
	
	VectorDestroy(&ptrVector , NULL);
	HeapDestroy(&ptrHeap);
}


/* ------------------------- Heap Sort ----------------------------- */
static void HeapSortPositive()
{
	Vector *ptrVector;
	int num200 = 200 , num100 = 100 , num185 = 185 , num50 = 50 , num80 = 80 , num90 = 90 , num800 =800  ; 
				
	ptrVector = VectorCreate (5, 3);

	VectorAppend (ptrVector , &num185);	
	VectorAppend (ptrVector , &num90);		
	VectorAppend (ptrVector , &num800); 	
	VectorAppend (ptrVector , &num200);
	VectorAppend (ptrVector , &num100);
	VectorAppend (ptrVector , &num50);	
	VectorAppend (ptrVector , &num80);	
	
	VectorForEach(ptrVector , PrintVector , NULL);	
	putchar('\n');	
		
	HeapSort(ptrVector , Comparator );
	
	VectorForEach(ptrVector , PrintVector , NULL);	
	putchar('\n');			
	
	VectorDestroy(&ptrVector , NULL);	
}




int PrintVector(void* _element, size_t _index, void* _context)
{
	printf("%d " , *((int*)_element));
	return 1;
}

int Comparator(const void *_left, const void *_right)
{
	return *((int*)_left) < *((int*)_right) ;
}

int	ActFunction(const void *_elem, void * _context)
{
	printf("%d " , *((int*)_elem));
	return 1;
}


