#include <stdio.h>              /* NULL , printf */
#include <stdlib.h>             /* size_t */
#include <time.h>               /* clock */
#include "../ADTDefs/ADTDefs.h" /* Error status */
#include "sorts.h"              /* API statements */


/* ------------------------------------------- typedef --------------------------------------------------- */

  /* pointer to sort function */
typedef ADTErr (*Sort)(Vector*);                                 

  /* for print name sort in the check test function */
typedef enum { BUBBLE_SORT , SHAKE_SORT , INSERTION_SORT , QUICK_SORT , SHELL_SORT ,
               SELECTION_SORT , MERGE_SORT ,  COUNTING_SORT , RADIX_SORT , QUICK_SORT_ITERATIVE , MERGE_SORT_ITERATIVE } PrintNameSort ; 

  /* for print the name test in the  check test function */
typedef enum { BEST_CASE , TYPICAL_CASE , WORST_CASE , FIRST_SIMPLE_CHECK ,
               EMPTY_VECTOR , ONE_ITEM , SAME_ITEMS , MIN_BIG_THEN_MAX , 
               MIN_EQUAL_MAX , NEGATIVE_PARAM , NEG_MIN_POS_MAX , NEG_NUM_DIGITS , ZERO_DIGITS } NameTest ; 

/* ------------------------------------------- Static variables ------------------------------------------ */

  /* result test positive */
static char s_pass[]="Pass";   

  /* result test negitive */   
static char s_failed[]="Failed";  


/* ------------------------------------------- Local function --------------------------------------------- */

  /* check if vector is sort */
static ADTErr IsSort(Vector *_vec);  

  /* check the positive test if pass or failed and print to the screen */                           
static void CheckTestPassOrFailedAndPrint(ADTErr _result , Vector *_ptrVector ,  PrintNameSort _nameSort , int _size , NameTest _nameTest ); 

  /* creat sorted vector */
static Vector* CreateASortedVector( int _size );
		
  /* creat random vector */
static Vector* CreateARandomVector( int _size , int _range );

  /* creat worst vector from big data to small data */
static Vector* CreateAWorstVectorBigToSmall( int _size );

  /* check null test if pass or failed and print to the screen */     
static void CheckNullTestAndPrint(ADTErr _result , PrintNameSort _nameSort );

  /* creat vector with same items */
static Vector* CreateASameItemsVector( int _size  );

  /* check the negitive test if pass or failed and print to the screen */     
static void CheckNegitiveTestAndPrint(ADTErr _result , PrintNameSort _nameSort , NameTest _nameTest );

  /* creat random vector with negative items */
static Vector* CreateARandomVectorNegativeItems( int _size , int _range );

  /* creat random vector with negative and POSITIVE items */
static Vector* CreateARandomVectorNegativePositiveItems( int _size , int _range );


/*============================================================= Tests =============================================================================*/


/* ------------------------------------------- First Simple Check Sort --------------------------------------- */

static void FirstSimpleCheckSort(Sort _sortFunc , PrintNameSort _nameSort );

/* ------------------------------------------- Null Vector --------------------------------------------------- */

static void CheckNullVector( Sort _sortFunc , PrintNameSort _nameSort );

/* ------------------------------------------- Empty Vector -------------------------------------------------- */

static void CheckEmptyVector( Sort _sortFunc , PrintNameSort _nameSort );

/* ------------------------------------------- One Item ------------------------------------------------------ */

static void CheckOneItem( Sort _sortFunc , PrintNameSort _nameSort );

/* ------------------------------------------- Same Items ---------------------------------------------------- */

static void CheckSameItems( Sort _sortFunc , PrintNameSort _nameSort , int _size );


/* ------------------------------------------- Best Case ----------------------------------------------------- */

static void BestCase10000(Sort _sortFunc , PrintNameSort _nameSort , FILE *_file , int _size );
static void BestCase50000(Sort _sortFunc , PrintNameSort _nameSort , FILE *_file , int _size );
static void BestCase100000(Sort _sortFunc , PrintNameSort _nameSort , FILE *_file , int _size );

/* ------------------------------------------- Best Case Quick Sort ----------------------------------------------------- */
/* The best case in all sorts is that the array is fully sorted,
   but in a quick sort it is not the best cast so this are special functions of the best case for quick sort */

static void QuickSortBestCase10000(Sort _sortFunc , PrintNameSort _nameSort , FILE *_file , int _size );
static void QuickSortBestCase50000(Sort _sortFunc , PrintNameSort _nameSort , FILE *_file , int _size );
static void QuickSortBestCase100000(Sort _sortFunc , PrintNameSort _nameSort , FILE *_file , int _size );


/* ------------------------------------------- Typical Case -------------------------------------------------- */

static void TypicalCase10000(Sort _sortFunc , PrintNameSort _nameSort , FILE *_file , int _size );
static void TypicalCase50000(Sort _sortFunc , PrintNameSort _nameSort , FILE *_file , int _size );
static void TypicalCase100000(Sort _sortFunc , PrintNameSort _nameSort , FILE *_file , int _size );

/* ------------------------------------------- Worst Case ---------------------------------------------------- */

static void WorstCase10000(Sort _sortFunc , PrintNameSort _nameSort , FILE *_file , int _size );
static void WorstCase50000(Sort _sortFunc , PrintNameSort _nameSort , FILE *_file , int _size );
static void WorstCase100000(Sort _sortFunc , PrintNameSort _nameSort , FILE *_file , int _size );


/* ------------------------------------------- Counting Sort tests ------------------------------------------- */

static void CountingSortSimplePositive();
static void CountingSortCheckNullVector();
static void CountingSortCheckEmptyVector();
static void CountingSortCheckOneItem();
static void CountingSortCheckSameItems();
static void CountingSortMinBigThenMax();
static void CountingSortMinEqualMax();
static void CountingSortNegativeMinAndMax();
static void CountingSortNegativeMinPositiveMax();
static void CountingSortBestCase10000(FILE *_file);
static void CountingSortBestCase50000(FILE *_file);
static void CountingSortBestCase100000(FILE *_file);
static void CountingSortTypicalCase10000(FILE *_file);
static void CountingSortTypicalCase50000(FILE *_file);
static void CountingSortTypicalCase100000(FILE *_file);

/* ------------------------------------------- Radix Sort tests ---------------------------------------------- */

static void RadixSortSimplePositive();
static void RadixSortCheckNullVector();
static void RadixSortCheckEmptyVector();
static void RadixSortCheckOneItem();
static void RadixSortCheckSameItems();
static void RadixSortNegativeNumOfDigits();
static void RadixSortZeroNumOfDigits();
static void RadixSortBestCase10000(FILE *_file);
static void RadixSortBestCase50000(FILE *_file);
static void RadixSortBestCase100000(FILE *_file);
static void RadixSortTypicalCase10000(FILE *_file);
static void RadixSortTypicalCase50000(FILE *_file);
static void RadixSortTypicalCase100000(FILE *_file);


/* -------------------------------------------------------------- Main -------------------------------------------------------------- */

/* argv[1] = 10k , argv[2] = 50k , argv[3] = 100k */
int main(int argc, char *argv[]) 
{

	FILE *file;
	
	file = fopen("Results_Sorts.txt" , "w");
	
	if ( NULL == file )
	{
		printf("Error file\n");
		return;
	} 
	
	fprintf(file ,"Name Sort\t\t| Best Case 10k\tBest Case 50k\tBest Case 100k\t| Typical Case 10k\tTypical Case 50k\tTypical Case 100k   | Name Sort\n");
	fprintf(file ,"______________________________________________________________________________________________________________________________________________\n");		
	fprintf(file ,"Bubble Sort\t");
	printf("Bubble Sort Test :\n");
	CheckNullVector( BubbleSort , BUBBLE_SORT );   
	CheckEmptyVector( BubbleSort , BUBBLE_SORT );   
     CheckOneItem( BubbleSort , BUBBLE_SORT );  
     CheckSameItems( BubbleSort , BUBBLE_SORT , atoi(argv[1]) ); 
     FirstSimpleCheckSort( BubbleSort , BUBBLE_SORT );   
     BestCase10000(BubbleSort , BUBBLE_SORT , file , atoi(argv[1]) ); 
     BestCase50000(BubbleSort , BUBBLE_SORT , file , atoi(argv[2]) );
     BestCase100000(BubbleSort , BUBBLE_SORT , file , atoi(argv[3]) );  
     TypicalCase10000(BubbleSort , BUBBLE_SORT , file , atoi(argv[1]) ); 
     TypicalCase50000(BubbleSort , BUBBLE_SORT , file , atoi(argv[2]) );
     TypicalCase100000(BubbleSort , BUBBLE_SORT , file , atoi(argv[3]) );  
	fprintf(file ,"| Bubble Sort\n");     
	fprintf(file ,"______________________________________________________________________________________________________________________________________________\n");	   
	fprintf(file ,"Shake Sort\t");
	printf("Shake Sort Test :\n");	
     CheckNullVector( ShakeSort , SHAKE_SORT );   
	CheckEmptyVector( ShakeSort , SHAKE_SORT );   
     CheckOneItem( ShakeSort , SHAKE_SORT );   
     CheckSameItems( ShakeSort , SHAKE_SORT , atoi(argv[1]) );     	    
     FirstSimpleCheckSort( ShakeSort , SHAKE_SORT );    
     BestCase10000(ShakeSort , SHAKE_SORT , file , atoi(argv[1]) );  
     BestCase50000(ShakeSort , SHAKE_SORT , file , atoi(argv[2]) );
     BestCase100000(ShakeSort , SHAKE_SORT , file , atoi(argv[3]) );  
     TypicalCase10000(ShakeSort , SHAKE_SORT , file , atoi(argv[1]) ); 
     TypicalCase50000(ShakeSort , SHAKE_SORT , file , atoi(argv[2]) );
     TypicalCase100000(ShakeSort , SHAKE_SORT , file , atoi(argv[3]) );  
	fprintf(file ,"| Shake Sort\n");     
	fprintf(file ,"______________________________________________________________________________________________________________________________________________\n");	 
	fprintf(file ,"Insertion Sort\t");	
	printf("Insertion Sort Test :\n");	
     CheckNullVector( InsertionSort , INSERTION_SORT );   
	CheckEmptyVector( InsertionSort , INSERTION_SORT );  
     CheckOneItem( InsertionSort , INSERTION_SORT ); 
     CheckSameItems( InsertionSort , INSERTION_SORT , atoi(argv[1]) );   	  
     FirstSimpleCheckSort( InsertionSort , INSERTION_SORT );  
     BestCase10000(InsertionSort , INSERTION_SORT , file , atoi(argv[1]) );  
     BestCase50000(InsertionSort , INSERTION_SORT , file , atoi(argv[2]) );  
     BestCase100000(InsertionSort , INSERTION_SORT , file , atoi(argv[3]) );  
     TypicalCase10000(InsertionSort , INSERTION_SORT , file , atoi(argv[1]) ); 
     TypicalCase50000(InsertionSort , INSERTION_SORT , file , atoi(argv[2]) ); 
     TypicalCase100000(InsertionSort , INSERTION_SORT , file , atoi(argv[3]) );  
	fprintf(file ,"| Insertion Sort\n");	     
	fprintf(file ,"______________________________________________________________________________________________________________________________________________\n");	       
	fprintf(file ,"Selection Sort\t");
	printf("Selection Sort Test :\n");	
     CheckNullVector( SelectionSort , SELECTION_SORT );  
	CheckEmptyVector( SelectionSort , SELECTION_SORT );   
     CheckOneItem( SelectionSort , SELECTION_SORT );   
     CheckSameItems( SelectionSort , SELECTION_SORT , atoi(argv[1]) );       
     FirstSimpleCheckSort( SelectionSort , SELECTION_SORT );    
     BestCase10000(SelectionSort , SELECTION_SORT , file , atoi(argv[1]) ); 
     BestCase50000(SelectionSort , SELECTION_SORT , file , atoi(argv[2]) );
     BestCase100000(SelectionSort , SELECTION_SORT , file , atoi(argv[3]) );   
     TypicalCase10000(SelectionSort , SELECTION_SORT , file , atoi(argv[1]) ); 
     TypicalCase50000(SelectionSort , SELECTION_SORT , file , atoi(argv[2]) ); 
     TypicalCase100000(SelectionSort , SELECTION_SORT , file , atoi(argv[3]) );  
	fprintf(file ,"| Selection Sort\n");     
	fprintf(file ,"______________________________________________________________________________________________________________________________________________\n");	
	fprintf(file ,"Shell Sort\t");
	printf("Shell Sort Test :\n");	
     CheckNullVector( ShellSort , SHELL_SORT );  
	CheckEmptyVector( ShellSort , SHELL_SORT );   
     CheckOneItem( ShellSort , SHELL_SORT );   
     CheckSameItems( ShellSort , SHELL_SORT , atoi(argv[1]) );  	      
     FirstSimpleCheckSort( ShellSort , SHELL_SORT );   
     BestCase10000(ShellSort , SHELL_SORT , file , atoi(argv[1]) ); 
     BestCase50000(ShellSort , SHELL_SORT , file , atoi(argv[2]) );
     BestCase100000(ShellSort , SHELL_SORT , file , atoi(argv[3]) );  
     TypicalCase10000(ShellSort , SHELL_SORT , file , atoi(argv[1]) ); 
     TypicalCase50000(ShellSort , SHELL_SORT , file , atoi(argv[2]) );
     TypicalCase100000(ShellSort , SHELL_SORT , file , atoi(argv[3]) );  
	fprintf(file ,"| Shell Sort\n");      
	fprintf(file ,"______________________________________________________________________________________________________________________________________________\n");	          
	fprintf(file ,"Quick Sort\t"); 
	printf("Quick Sort Test :\n");	
     CheckNullVector( QuickSort , QUICK_SORT );  
	CheckEmptyVector( QuickSort , QUICK_SORT ); 	 	
     CheckOneItem( QuickSort , QUICK_SORT ); 	 	
     CheckSameItems( QuickSort , QUICK_SORT , atoi(argv[1]) );       	
     FirstSimpleCheckSort( QuickSort , QUICK_SORT ); 	 	  
     QuickSortBestCase10000(QuickSort , QUICK_SORT , file  , atoi(argv[1]) ); 
     QuickSortBestCase50000(QuickSort , QUICK_SORT , file , atoi(argv[2]) );
     QuickSortBestCase100000(QuickSort , QUICK_SORT , file , atoi(argv[3]) );  
     TypicalCase10000(QuickSort , QUICK_SORT , file , atoi(argv[1]) ); 
     TypicalCase50000(QuickSort , QUICK_SORT , file , atoi(argv[2]) );
     TypicalCase100000(QuickSort , QUICK_SORT , file , atoi(argv[3]) );  
	fprintf(file ,"| Quick Sort\n");      
fprintf(file ,"______________________________________________________________________________________________________________________________________________\n");	          
	fprintf(file ,"Quick Iterative"); 
	printf("Quick Sort Iterative Test :\n");	
     CheckNullVector( QuickSortIterative , QUICK_SORT_ITERATIVE );  
	CheckEmptyVector( QuickSortIterative , QUICK_SORT_ITERATIVE ); 	 	
     CheckOneItem( QuickSortIterative , QUICK_SORT_ITERATIVE ); 	 	
     CheckSameItems( QuickSortIterative , QUICK_SORT_ITERATIVE , atoi(argv[1]) );       	
     FirstSimpleCheckSort( QuickSortIterative , QUICK_SORT_ITERATIVE ); 	 	  
     QuickSortBestCase10000(QuickSortIterative , QUICK_SORT_ITERATIVE , file  , atoi(argv[1]) ); 
     QuickSortBestCase50000(QuickSortIterative , QUICK_SORT_ITERATIVE , file , atoi(argv[2]) );
     QuickSortBestCase100000(QuickSortIterative , QUICK_SORT_ITERATIVE , file , atoi(argv[3]) );  
     TypicalCase10000(QuickSortIterative , QUICK_SORT_ITERATIVE , file , atoi(argv[1]) ); 
     TypicalCase50000(QuickSortIterative , QUICK_SORT_ITERATIVE , file , atoi(argv[2]) );
     TypicalCase100000(QuickSortIterative , QUICK_SORT_ITERATIVE , file , atoi(argv[3]) );  
	fprintf(file ,"| Quick Iterative\n"); 	fprintf(file ,"______________________________________________________________________________________________________________________________________________\n");	    
	fprintf(file ,"Merge Sort\t");
	printf("Merge Sort Test :\n");		
     CheckNullVector( MergeSort , MERGE_SORT );  
	CheckEmptyVector( MergeSort , MERGE_SORT );    
     CheckOneItem( MergeSort , MERGE_SORT );    
     CheckSameItems( MergeSort , MERGE_SORT , atoi(argv[1]) );     	
     FirstSimpleCheckSort( MergeSort , MERGE_SORT );    
     BestCase10000(MergeSort , MERGE_SORT , file , atoi(argv[1]) ); 
     BestCase50000(MergeSort , MERGE_SORT , file , atoi(argv[2]) );
     BestCase100000(MergeSort , MERGE_SORT , file , atoi(argv[3]) );    
     TypicalCase10000(MergeSort , MERGE_SORT , file , atoi(argv[1]) ); 
     TypicalCase50000(MergeSort , MERGE_SORT , file , atoi(argv[2]) );
     TypicalCase100000(MergeSort , MERGE_SORT , file , atoi(argv[3]) );  
	fprintf(file ,"| Merge Sort\n");     
fprintf(file ,"______________________________________________________________________________________________________________________________________________\n");	    
/*	fprintf(file ,"Merge Iterative");
	printf("Merge Sort Iterative Test :\n");		
     CheckNullVector( MergeSortIterative , MERGE_SORT_ITERATIVE );  
	CheckEmptyVector( MergeSortIterative , MERGE_SORT_ITERATIVE );    
     CheckOneItem( MergeSortIterative , MERGE_SORT_ITERATIVE );    
     CheckSameItems( MergeSortIterative , MERGE_SORT_ITERATIVE , atoi(argv[1]) );     	
     FirstSimpleCheckSort( MergeSortIterative , MERGE_SORT_ITERATIVE );    
     BestCase10000(MergeSortIterative , MERGE_SORT_ITERATIVE , file , atoi(argv[1]) ); 
     BestCase50000(MergeSortIterative , MERGE_SORT_ITERATIVE , file , atoi(argv[2]) );
     BestCase100000(MergeSortIterative , MERGE_SORT_ITERATIVE , file , atoi(argv[3]) );    
     TypicalCase10000(MergeSortIterative , MERGE_SORT_ITERATIVE , file , atoi(argv[1]) ); 
     TypicalCase50000(MergeSortIterative , MERGE_SORT_ITERATIVE , file , atoi(argv[2]) );
     TypicalCase100000(MergeSortIterative , MERGE_SORT_ITERATIVE , file , atoi(argv[3]) );  
	fprintf(file ,"| Merge Iterative\n");  	fprintf(file ,"______________________________________________________________________________________________________________________________________________\n");	*/     
	fprintf(file ,"Counting Sort\t");
	printf("Counting Sort Test :\n");	
	CountingSortSimplePositive(); 
     CountingSortCheckNullVector();
     CountingSortCheckEmptyVector();
     CountingSortCheckOneItem();	
     CountingSortCheckSameItems();
     CountingSortMinBigThenMax();
     CountingSortMinEqualMax();
     CountingSortNegativeMinAndMax();
     CountingSortNegativeMinPositiveMax();
     CountingSortBestCase10000(file);
     CountingSortBestCase50000(file);
     CountingSortBestCase100000(file);
     CountingSortTypicalCase10000(file);
     CountingSortTypicalCase50000(file);
     CountingSortTypicalCase100000(file);    
	fprintf(file ,"| Counting Sort\n");     
	fprintf(file ,"______________________________________________________________________________________________________________________________________________\n");	
 	fprintf(file ,"Radix Sort\t"); 
	printf("Radix Sort Test :\n");	 	
	RadixSortSimplePositive(); 
     RadixSortCheckNullVector();	
     RadixSortCheckEmptyVector();
     RadixSortCheckOneItem();
     RadixSortCheckSameItems();
     RadixSortNegativeNumOfDigits();
     RadixSortZeroNumOfDigits();
     RadixSortBestCase10000(file);
     RadixSortBestCase50000(file);
     RadixSortBestCase100000(file);    
     RadixSortTypicalCase10000(file);
     RadixSortTypicalCase50000(file);
     RadixSortTypicalCase100000(file); 	
 	fprintf(file ,"| Radix Sort\n");      
	fprintf(file ,"______________________________________________________________________________________________________________________________________________\n");	
          
     fclose(file);     
       			
	return 1;
}



/* ------------------------------------------- First Simple Check Sort -------------------------------------- */

static void FirstSimpleCheckSort(Sort _sortFunc , PrintNameSort _nameSort )
{
	Vector *ptrVector;
	ADTErr result;
	
	ptrVector = CreateARandomVector( 20 , 500 );
	
	result = _sortFunc(ptrVector);

     CheckTestPassOrFailedAndPrint( result , ptrVector ,  _nameSort , 20 , FIRST_SIMPLE_CHECK );
		
	VectorDestroy(ptrVector);
}


/* ------------------------------------------- Null Vector -------------------------------------- */

static void CheckNullVector( Sort _sortFunc , PrintNameSort _nameSort )
{
	ADTErr result;
	
	result = _sortFunc(NULL);

     CheckNullTestAndPrint(result , _nameSort);
}


/* ------------------------------------------- Empty Vector -------------------------------------------------- */

static void CheckEmptyVector( Sort _sortFunc , PrintNameSort _nameSort )
{
	Vector *ptrVector = VectorCreate (5, 3) ;
	ADTErr result;
	
	result = _sortFunc(ptrVector);

     CheckTestPassOrFailedAndPrint( result , ptrVector ,  _nameSort , 0 , EMPTY_VECTOR );
     
     VectorDestroy(ptrVector);
}

/* ------------------------------------------- One Item ------------------------------------------------------ */

static void CheckOneItem( Sort _sortFunc , PrintNameSort _nameSort )
{
	Vector *ptrVector = VectorCreate (5, 3) ;
	ADTErr result;
	
	VectorAdd ( ptrVector , 18 );
	
     result = _sortFunc(ptrVector);

     CheckTestPassOrFailedAndPrint( result , ptrVector ,  _nameSort , 1 , ONE_ITEM );
   
     VectorDestroy(ptrVector);     
}


/* ------------------------------------------- Same Items ------------------------------------------------------ */

static void CheckSameItems( Sort _sortFunc , PrintNameSort _nameSort , int _size )
{
    ADTErr result;
    Vector *ptrVector ;
	
    ptrVector = CreateASameItemsVector( _size );
	
    result = _sortFunc(ptrVector);

    CheckTestPassOrFailedAndPrint( result , ptrVector ,  _nameSort , _size , SAME_ITEMS );
    
    VectorDestroy(ptrVector);    
}


/* =========================================================== Best Case =========================================================== */


/* ------------------------------------------- Best Case 10000 ------------------------------------------- */

static void BestCase10000(Sort _sortFunc , PrintNameSort _nameSort , FILE *_file , int _size )
{
	Vector *ptrVector;
	ADTErr result;
     clock_t t1;
	
     ptrVector = CreateASortedVector( _size );	
	
	t1 = clock();
		
	result = _sortFunc(ptrVector);
		
	t1 = clock()-t1 ;

	fprintf(_file,"| %f sec\t\t", ((double)t1)/ CLOCKS_PER_SEC );
	
     CheckTestPassOrFailedAndPrint(result , ptrVector ,  _nameSort , _size  , BEST_CASE );

	VectorDestroy(ptrVector);
}

/* ------------------------------------------- Best Case 50000 --------------------------------------------- */

static void BestCase50000(Sort _sortFunc , PrintNameSort _nameSort , FILE *_file  , int _size )
{
	Vector *ptrVector;
	ADTErr result;
     clock_t t1;
	
	ptrVector = CreateASortedVector( _size );
	
	t1 = clock();
	
	result = _sortFunc(ptrVector);
	
	t1 = clock()-t1 ;

	fprintf(_file,"%f sec\t", ((double)t1)/ CLOCKS_PER_SEC );
	
     CheckTestPassOrFailedAndPrint( result , ptrVector ,  _nameSort , _size  , BEST_CASE );

	VectorDestroy(ptrVector);
}

/* ------------------------------------------- Best Case 100000 --------------------------------------------- */

static void BestCase100000(Sort _sortFunc , PrintNameSort _nameSort , FILE *_file , int _size )
{
	Vector *ptrVector;
	ADTErr result;
     clock_t t1;
	
	ptrVector = CreateASortedVector( _size );
	
	t1 = clock();
	
	result = _sortFunc(ptrVector);
	
	t1 = clock()-t1 ;

	fprintf(_file,"%f sec\t", ((double)t1)/ CLOCKS_PER_SEC );

     CheckTestPassOrFailedAndPrint( result , ptrVector ,  _nameSort , _size  , BEST_CASE );
     
	VectorDestroy(ptrVector);
}


/* ------------------------------------------- Best Case Quick Sort ----------------------------------------------------- */


static void QuickSortBestCase10000(Sort _sortFunc , PrintNameSort _nameSort , FILE *_file , int _size )
{
	Vector *ptrVector;
	ADTErr result;
     clock_t t1;
	
     ptrVector = CreateARandomVector( _size , _size );
     VectorSet(ptrVector , 0 , _size/2 );
	
	t1 = clock();
		
	result = _sortFunc(ptrVector);
		
	t1 = clock()-t1 ;

	fprintf(_file,"| %f sec\t\t", ((double)t1)/ CLOCKS_PER_SEC );
	
     CheckTestPassOrFailedAndPrint(result , ptrVector ,  _nameSort , _size  , BEST_CASE );

	VectorDestroy(ptrVector);
}

/* ---------------------------------------------------------------------------------------------------------------------- */

static void QuickSortBestCase50000(Sort _sortFunc , PrintNameSort _nameSort , FILE *_file , int _size )
{
	Vector *ptrVector;
	ADTErr result;
     clock_t t1;
	
	ptrVector = CreateARandomVector( _size , _size+1 );
     VectorSet(ptrVector , 0 , _size/2 );
     	
	t1 = clock();
	
	result = _sortFunc(ptrVector);
	
	t1 = clock()-t1 ;

	fprintf(_file,"%f sec\t", ((double)t1)/ CLOCKS_PER_SEC );
	
     CheckTestPassOrFailedAndPrint( result , ptrVector ,  _nameSort , _size  , BEST_CASE );

	VectorDestroy(ptrVector);
}

/* ---------------------------------------------------------------------------------------------------------------------- */

static void QuickSortBestCase100000(Sort _sortFunc , PrintNameSort _nameSort , FILE *_file , int _size )
{
	Vector *ptrVector;
	ADTErr result;
     clock_t t1;
	
	ptrVector = CreateARandomVector( _size , _size+1 );
     VectorSet(ptrVector , 0 , _size/2 );
     	
	t1 = clock();
	
	result = _sortFunc(ptrVector);
	
	t1 = clock()-t1 ;

	fprintf(_file,"%f sec\t", ((double)t1)/ CLOCKS_PER_SEC );

     CheckTestPassOrFailedAndPrint( result , ptrVector ,  _nameSort , _size  , BEST_CASE );
     
	VectorDestroy(ptrVector);
}


/* =========================================================== Typical Case =========================================================== */


/* ------------------------------------------- Typical Case 10000 ---------------------------------------------- */

static void TypicalCase10000(Sort _sortFunc , PrintNameSort _nameSort , FILE *_file , int _size )
{
	Vector *ptrVector;
	ADTErr result;
     clock_t t1;
	
	ptrVector =  CreateARandomVector( _size , _size );
	
	t1 = clock();
	
	result = _sortFunc(ptrVector);
	
	t1 = clock()-t1 ;

	fprintf(_file,"| %f sec\t\t", ((double)t1)/ CLOCKS_PER_SEC );

     CheckTestPassOrFailedAndPrint(result , ptrVector ,  _nameSort , _size  , TYPICAL_CASE );

	VectorDestroy(ptrVector);
}

/* ------------------------------------------- Typical Case 50000 ----------------------------------------------- */

static void TypicalCase50000(Sort _sortFunc , PrintNameSort _nameSort , FILE *_file , int _size )
{
	Vector *ptrVector;
	ADTErr result;
     clock_t t1;
	
	ptrVector = CreateARandomVector( _size , _size );
	
	t1 = clock();
	
	result = _sortFunc(ptrVector);
	
	t1 = clock()-t1 ;

	fprintf(_file,"%f sec\t\t", ((double)t1)/ CLOCKS_PER_SEC );

     CheckTestPassOrFailedAndPrint(result , ptrVector ,  _nameSort , _size  , TYPICAL_CASE );
	
	VectorDestroy(ptrVector);
}

/* ------------------------------------------- Typical Case 100000 ----------------------------------------------- */

static void TypicalCase100000(Sort _sortFunc , PrintNameSort _nameSort , FILE *_file , int _size )
{
	Vector *ptrVector;
	ADTErr result;
     clock_t t1;
	
	ptrVector = CreateARandomVector( _size , _size );
	
	t1 = clock();
	
	result = _sortFunc(ptrVector);
	
	t1 = clock()-t1 ;

	fprintf(_file,"%f sec\t\t", ((double)t1)/ CLOCKS_PER_SEC );

     CheckTestPassOrFailedAndPrint(result , ptrVector ,  _nameSort , _size  , TYPICAL_CASE );

	VectorDestroy(ptrVector);
}

/* =========================================================== Worst Case =========================================================== */


/* ------------------------------------------- Worst Case 10000 ---------------------------------------------- */

static void WorstCase10000(Sort _sortFunc , PrintNameSort _nameSort , FILE *_file , int _size )
{
	Vector *ptrVector;
	ADTErr result;
     clock_t t1;
	
	ptrVector =  CreateAWorstVectorBigToSmall( _size );
	
	t1 = clock();
	
	result = _sortFunc(ptrVector);
	
	t1 = clock()-t1 ;

	fprintf(_file,"| %f sec\t\t", ((double)t1)/ CLOCKS_PER_SEC );

     CheckTestPassOrFailedAndPrint(result , ptrVector ,  _nameSort , _size  , WORST_CASE );

	VectorDestroy(ptrVector);
}

/* ------------------------------------------- Worst Case 50000 ----------------------------------------------- */

static void WorstCase50000(Sort _sortFunc , PrintNameSort _nameSort , FILE *_file , int _size )
{
	Vector *ptrVector;
	ADTErr result;
     clock_t t1;
	
	ptrVector =  CreateAWorstVectorBigToSmall( _size );
	
	t1 = clock();
	
	result = _sortFunc(ptrVector);
	
	t1 = clock()-t1 ;

	fprintf(_file,"| %f sec\t\t", ((double)t1)/ CLOCKS_PER_SEC );

     CheckTestPassOrFailedAndPrint(result , ptrVector ,  _nameSort , _size  , WORST_CASE );

	VectorDestroy(ptrVector);
}

/* ------------------------------------------- Worst Case 100000 ----------------------------------------------- */

static void WorstCase100000(Sort _sortFunc , PrintNameSort _nameSort , FILE *_file , int _size )
{
	Vector *ptrVector;
	ADTErr result;
     clock_t t1;
	
	ptrVector =  CreateAWorstVectorBigToSmall( _size );
	
	t1 = clock();
	
	result = _sortFunc(ptrVector);
	
	t1 = clock()-t1 ;

	fprintf(_file,"| %f sec\t\t", ((double)t1)/ CLOCKS_PER_SEC );

     CheckTestPassOrFailedAndPrint(result , ptrVector ,  _nameSort , _size  , WORST_CASE );

	VectorDestroy(ptrVector);
}


/* ======================================== Counting Sort tests ======================================== */

static void CountingSortSimplePositive()
{
	Vector *ptrVector;
	ADTErr result;
	
	ptrVector = CreateARandomVector( 20 , 501 );	
			
	result = CountingSort(ptrVector , 0 , 500);
	
     CheckTestPassOrFailedAndPrint( result , ptrVector ,  COUNTING_SORT , 20  , FIRST_SIMPLE_CHECK );
	
	VectorDestroy(ptrVector);
}


/* ----------------------------------------------------------- */

static void CountingSortCheckNullVector()
{
	ADTErr result;
	
	result = CountingSort (NULL , 0 , 10 );

     CheckNullTestAndPrint(result , COUNTING_SORT );
}

/* ----------------------------------------------------------- */

static void CountingSortCheckEmptyVector()
{
	Vector *ptrVector = VectorCreate (5, 3) ;
	ADTErr result;
	
	result = CountingSort(ptrVector , 0 , 10 );

     CheckTestPassOrFailedAndPrint( result , ptrVector ,  COUNTING_SORT , 0 , EMPTY_VECTOR );	
     
     VectorDestroy(ptrVector);     
}

/* ----------------------------------------------------------- */

static void CountingSortCheckOneItem()
{
	Vector *ptrVector = VectorCreate (5, 3) ;
	ADTErr result;
	
	VectorAdd ( ptrVector , 18 );
	
     result = CountingSort(ptrVector , 15 , 20 );

     CheckTestPassOrFailedAndPrint( result , ptrVector , COUNTING_SORT , 1 , ONE_ITEM );
   
     VectorDestroy(ptrVector);
}

/* ----------------------------------------------------------- */

static void CountingSortCheckSameItems()
{
    ADTErr result;
    Vector *ptrVector ;
	
    ptrVector = CreateASameItemsVector( 10000 );
	
    result = CountingSort(ptrVector , 15 , 20 );

    CheckTestPassOrFailedAndPrint( result , ptrVector ,  COUNTING_SORT , 10000 , SAME_ITEMS );
    
    VectorDestroy(ptrVector);  
}

/* ----------------------------------------------------------- */

static void CountingSortMinBigThenMax()
{
	Vector *ptrVector;
	ADTErr result;
	
	ptrVector = CreateARandomVector( 20 , 501 );	
			
	result = CountingSort(ptrVector , 568 , 500);
	
     CheckNegitiveTestAndPrint(result , COUNTING_SORT , MIN_BIG_THEN_MAX );
	
	VectorDestroy(ptrVector);	
}

/* ----------------------------------------------------------- */

static void CountingSortMinEqualMax()
{
	Vector *ptrVector;
	ADTErr result;
	
	ptrVector = CreateASameItemsVector( 50  ) ;
			
	result = CountingSort(ptrVector , 18 , 18 );
	
     CheckTestPassOrFailedAndPrint( result , ptrVector ,  COUNTING_SORT , 50  , MIN_EQUAL_MAX );
	
	VectorDestroy(ptrVector);	
}

/* ----------------------------------------------------------- */

static void CountingSortNegativeMinAndMax()
{
	Vector *ptrVector;
	ADTErr result;
	
	ptrVector = CreateARandomVectorNegativeItems( 50 , 20 ) ; 
			
	result = CountingSort(ptrVector , -20 , -1 );
	
     CheckTestPassOrFailedAndPrint( result , ptrVector ,  COUNTING_SORT , 50  , NEGATIVE_PARAM );
	
	VectorDestroy(ptrVector);
}

/* ----------------------------------------------------------- */

static void CountingSortNegativeMinPositiveMax()
{
	Vector *ptrVector;
	ADTErr result;
	
	ptrVector = CreateARandomVectorNegativePositiveItems( 50 , 20 ) ;
			
	result = CountingSort(ptrVector , -10 , 9 );
	
     CheckTestPassOrFailedAndPrint( result , ptrVector ,  COUNTING_SORT , 50  , NEG_MIN_POS_MAX );
	
	VectorDestroy(ptrVector);
}


/* ----------------------------------------------------------- */

static void CountingSortBestCase10000(FILE *_file)
{
	Vector *ptrVector;
	ADTErr result;
     clock_t t1;
     
     ptrVector = CreateASortedVector( 10000 );		
	
	t1 = clock();
	
	result = CountingSort(ptrVector , 0 , 10000);
	
	t1 = clock()-t1 ;

	fprintf(_file ,"| %f sec\t\t", ((double)t1)/ CLOCKS_PER_SEC );

     CheckTestPassOrFailedAndPrint( result , ptrVector ,  COUNTING_SORT , 10000  , BEST_CASE );

	VectorDestroy(ptrVector);
}
/* ----------------------------------------------------------- */
static void CountingSortBestCase50000(FILE *_file)
{
	Vector *ptrVector;
	ADTErr result;
     clock_t t1;
     
     ptrVector = CreateASortedVector( 50000 );	
	
	t1 = clock();
	
	result = CountingSort(ptrVector , 0 , 50000);
	
	t1 = clock()-t1 ;

	fprintf(_file ,"%f sec\t", ((double)t1)/ CLOCKS_PER_SEC );

     CheckTestPassOrFailedAndPrint( result , ptrVector ,  COUNTING_SORT , 50000  , BEST_CASE );

	VectorDestroy(ptrVector);
}

/* ----------------------------------------------------------- */
static void CountingSortBestCase100000(FILE *_file)
{
	Vector *ptrVector;
	ADTErr result;
     clock_t t1;
     
     ptrVector = CreateASortedVector( 100000 );	
	
	t1 = clock();
	
	result = CountingSort(ptrVector , 0 , 100000);
	
	t1 = clock()-t1 ;

	fprintf(_file ,"%f sec\t", ((double)t1)/ CLOCKS_PER_SEC );

     CheckTestPassOrFailedAndPrint( result , ptrVector ,  COUNTING_SORT , 100000  , BEST_CASE );

	VectorDestroy(ptrVector);
}


/* ----------------------------------------------------------- */
static void CountingSortTypicalCase10000(FILE *_file)
{
	Vector *ptrVector;
	ADTErr result;
     clock_t t1;
     
	ptrVector =  CreateARandomVector( 10000 , 10001 );
	
	t1 = clock();
	
	result = CountingSort(ptrVector , 0 , 10000);
	
	t1 = clock()-t1 ;

	fprintf(_file ,"| %f sec\t\t", ((double)t1)/ CLOCKS_PER_SEC );

     CheckTestPassOrFailedAndPrint( result , ptrVector ,  COUNTING_SORT , 10000  , TYPICAL_CASE );

	VectorDestroy(ptrVector);
}
/* ----------------------------------------------------------- */
static void CountingSortTypicalCase50000(FILE *_file)
{
	Vector *ptrVector;
	ADTErr result;
     clock_t t1;
     
	ptrVector =  CreateARandomVector( 50000 , 50001 );
	
	t1 = clock();
	
	result = CountingSort(ptrVector , 0 , 50000);
	
	t1 = clock()-t1 ;

	fprintf(_file ,"%f sec\t\t", ((double)t1)/ CLOCKS_PER_SEC );

     CheckTestPassOrFailedAndPrint( result , ptrVector ,  COUNTING_SORT , 50000  , TYPICAL_CASE );

	VectorDestroy(ptrVector);
}

/* ----------------------------------------------------------- */
static void CountingSortTypicalCase100000(FILE *_file)
{
	Vector *ptrVector;
	ADTErr result;
     clock_t t1;
     
	ptrVector =  CreateARandomVector( 100000 , 100001 );
	
	t1 = clock();
	
	result = CountingSort(ptrVector , 0 , 100000);
	
	t1 = clock()-t1 ;

	fprintf(_file ,"%f sec\t\t", ((double)t1)/ CLOCKS_PER_SEC );

     CheckTestPassOrFailedAndPrint( result , ptrVector ,  COUNTING_SORT , 100000  , TYPICAL_CASE );
	
	VectorDestroy(ptrVector);
}

/* ======================================== Radix Sort tests ======================================== */

static void RadixSortSimplePositive()
{
	Vector *ptrVector;
	ADTErr result;
	
	ptrVector = CreateARandomVector( 20 , 500 );				

	result = RadixSort(ptrVector , 3);

     CheckTestPassOrFailedAndPrint( result , ptrVector ,  RADIX_SORT , 20  , FIRST_SIMPLE_CHECK );
	
	VectorDestroy(ptrVector);
}

/* ----------------------------------------------------------- */

static void RadixSortCheckNullVector()
{
	ADTErr result;
	
	result = RadixSort (NULL , 4 );

     CheckNullTestAndPrint(result , RADIX_SORT );
}

/* ----------------------------------------------------------- */

static void RadixSortCheckEmptyVector()
{
	Vector *ptrVector = VectorCreate (5, 3) ;
	ADTErr result;
	
	result = RadixSort (ptrVector , 5 );

     CheckTestPassOrFailedAndPrint( result , ptrVector ,  RADIX_SORT , 0 , EMPTY_VECTOR );	
     
     VectorDestroy(ptrVector);     
}

/* ----------------------------------------------------------- */

static void RadixSortCheckOneItem()
{
	Vector *ptrVector = VectorCreate (5, 3) ;
	ADTErr result;
	
	VectorAdd ( ptrVector , 18 );
	
     result = RadixSort (ptrVector , 2 );

     CheckTestPassOrFailedAndPrint( result , ptrVector , RADIX_SORT , 1 , ONE_ITEM );
   
     VectorDestroy(ptrVector);
}

/* ----------------------------------------------------------- */

static void RadixSortCheckSameItems()
{
    ADTErr result;
    Vector *ptrVector ;
	
    ptrVector = CreateASameItemsVector( 10000 );
	
    result = RadixSort (ptrVector , 2 );

    CheckTestPassOrFailedAndPrint( result , ptrVector ,  RADIX_SORT , 10000 , SAME_ITEMS );
    
    VectorDestroy(ptrVector); 
}


/* ----------------------------------------------------------- */

static void RadixSortNegativeNumOfDigits()
{
	Vector *ptrVector;
	ADTErr result;
	
	ptrVector = CreateARandomVector( 20 , 501 );	
			
	result = RadixSort (ptrVector , -2 );
	
     CheckNegitiveTestAndPrint(result , RADIX_SORT , NEG_NUM_DIGITS );
	
	VectorDestroy(ptrVector);
}


/* ----------------------------------------------------------- */

static void RadixSortZeroNumOfDigits()
{
	Vector *ptrVector = VectorCreate (5, 3) ;
	ADTErr result;
	
	result = RadixSort (ptrVector , 0 );

     CheckTestPassOrFailedAndPrint( result , ptrVector ,  RADIX_SORT , 0 , ZERO_DIGITS );	
     
     VectorDestroy(ptrVector);
}

/* ----------------------------------------------------------- */

static void RadixSortBestCase10000(FILE *_file)
{
	Vector *ptrVector;
	ADTErr result;
     clock_t t1;
     
     ptrVector = CreateASortedVector( 10000 );	
	
	t1 = clock();
	
	result = RadixSort(ptrVector , 5);
	
	t1 = clock()-t1 ;

	fprintf(_file ,"| %f sec\t\t", ((double)t1)/ CLOCKS_PER_SEC );

     CheckTestPassOrFailedAndPrint( result , ptrVector ,  RADIX_SORT , 10000  , BEST_CASE );

	VectorDestroy(ptrVector);
}
/* ----------------------------------------------------------- */
static void RadixSortBestCase50000(FILE *_file)
{
	Vector *ptrVector;
	ADTErr result;
     clock_t t1;
     
     ptrVector = CreateASortedVector( 50000 );	
	
	t1 = clock();
	
	result = RadixSort(ptrVector , 5);
	
	t1 = clock()-t1 ;

	fprintf(_file ,"%f sec\t", ((double)t1)/ CLOCKS_PER_SEC );

     CheckTestPassOrFailedAndPrint( result , ptrVector ,  RADIX_SORT , 50000  , BEST_CASE );

	VectorDestroy(ptrVector);
}
/* ----------------------------------------------------------- */
static void RadixSortBestCase100000(FILE *_file)
{
	Vector *ptrVector;
	ADTErr result;
     clock_t t1;
     
     ptrVector = CreateASortedVector( 100000 );	
	
	t1 = clock();
	
	result = RadixSort(ptrVector , 6);
	
	t1 = clock()-t1 ;

	fprintf(_file ,"%f sec\t", ((double)t1)/ CLOCKS_PER_SEC );
	
     CheckTestPassOrFailedAndPrint( result , ptrVector ,  RADIX_SORT , 100000  , BEST_CASE );

	VectorDestroy(ptrVector);
}

/* ----------------------------------------------------------- */
static void RadixSortTypicalCase10000(FILE *_file)
{
	Vector *ptrVector;
	ADTErr result;
     clock_t t1;
     
	ptrVector =  CreateARandomVector( 10000 , 10001 );
	
	t1 = clock();
	
	result = RadixSort(ptrVector , 5);
	
	t1 = clock()-t1 ;

	fprintf(_file ,"| %f sec\t\t", ((double)t1)/ CLOCKS_PER_SEC );

     CheckTestPassOrFailedAndPrint( result , ptrVector ,  RADIX_SORT , 10000  , TYPICAL_CASE );

	VectorDestroy(ptrVector);
}
/* ----------------------------------------------------------- */
static void RadixSortTypicalCase50000(FILE *_file)
{
	Vector *ptrVector;
	ADTErr result;
     clock_t t1;
     
	ptrVector =  CreateARandomVector( 50000 , 50001 );
	
	t1 = clock();
	
	result = RadixSort(ptrVector , 5);
	
	t1 = clock()-t1 ;

	fprintf(_file ,"%f sec\t\t", ((double)t1)/ CLOCKS_PER_SEC );

     CheckTestPassOrFailedAndPrint( result , ptrVector ,  RADIX_SORT , 50000  , TYPICAL_CASE );

	VectorDestroy(ptrVector);
}
/* ----------------------------------------------------------- */
static void RadixSortTypicalCase100000(FILE *_file)
{
	Vector *ptrVector;
	ADTErr result;
     clock_t t1;
	
	ptrVector =  CreateARandomVector( 100000 , 100001 );
	
	t1 = clock();
	
	result = RadixSort(ptrVector , 6);
	
	t1 = clock()-t1 ;

	fprintf(_file ,"%f sec\t\t", ((double)t1)/ CLOCKS_PER_SEC );
	
     CheckTestPassOrFailedAndPrint( result , ptrVector ,  RADIX_SORT , 100000  , TYPICAL_CASE );
		
	VectorDestroy(ptrVector);
}

/*==========================================================================================================================================*/
/*============================================================= Local function =============================================================*/
/*==========================================================================================================================================*/

static ADTErr IsSort(Vector *_vec)
{
	int size;
	int left , right , smallData , bigData ;
	VectorItemsNum(_vec , &size);
	
	for ( left = 0 , right = left+1 ; right < size ; left++ , right++)
	{
	    		VectorGet(_vec, left , &smallData);
    		 	VectorGet(_vec, right , &bigData);
    		 	if ( smallData > bigData )
    		 	{
    		 	return ERR_GENERAL ;
    		 	}
	}
	
	return ERR_OK;
}

/* -------------------------------------------------------------------------------------------------------------------------------------- */

static void CheckTestPassOrFailedAndPrint(ADTErr _result , Vector *_ptrVector ,  PrintNameSort _nameSort , int _size , NameTest _nameTest )
{
	if ( (_result == ERR_OK) && (IsSort(_ptrVector) == ERR_OK) )
	{
		puts(s_pass);	
	}
	else
	{
          switch ( _nameSort )
	     {
			case BUBBLE_SORT :
							  printf("Bubble Sort ");
							  break;
			case SHAKE_SORT :
							  printf("Shake Sort ");
							  break;
			case INSERTION_SORT :
							  printf("Insertion Sort ");
							  break;
			case QUICK_SORT :
						       printf("Quick Sort ");
						       break;
			case SHELL_SORT :
						       printf("Shell Sort ");
						       break;
			case SELECTION_SORT :
						       printf("Selection Sort ");
						       break;
			case MERGE_SORT :
						       printf("Merge Sort ");
						       break;
			case COUNTING_SORT :
						       printf("Counting Sort ");
						       break;
			case RADIX_SORT :
						       printf("Radix Sort ");
						       break;	
			case QUICK_SORT_ITERATIVE :
						       printf("Quick Sort iterative ");
						       break;	
			case MERGE_SORT_ITERATIVE :
						       printf("Merge Sort iterative ");
						       break;							       					       					       	
	 	    default :
		     	                 break;				
		}
		
          switch ( _nameTest )
	     {
			case BEST_CASE :
							     printf("Best Case ");
							     break;
			case TYPICAL_CASE :
							     printf("Tyipical Case ");
							     break;
			case WORST_CASE :
							     printf("Worst Case ");
							     break;
			case FIRST_SIMPLE_CHECK :
							     printf("First Simple Check Sort ");
							     break;	
			case EMPTY_VECTOR :
							     printf("Empty vector ");
							     break;								     
			case ONE_ITEM :
							     printf("One Item ");
							     break;	
			case SAME_ITEMS :
							     printf("Same Items ");
							     break;
			case MIN_EQUAL_MAX :
							     printf("min equal max ");
							     break;
			case NEGATIVE_PARAM :
							     printf("min and max  negative ");
							     break;	
			case NEG_MIN_POS_MAX :
							     printf("neg min pos max ");
							     break;
			case ZERO_DIGITS :
							     printf("zero num of digits ");
							     break;							     							     			   
	 	    default :
		     	                    break;				
		}		
		
	     printf("%d: " , _size);	
	     	
		puts(s_failed);
	}
}

/* -------------------------------------------------------------------------------------------------------------------------------------- */

static Vector* CreateASortedVector( int _size )
{
	register int index;
	Vector *ptrVector = VectorCreate (5, 3);
		
     for( index=0  ; index<_size ; index++ )
     {
       VectorAdd ( ptrVector , index);     
     }
     
     return ptrVector ;
}

/* -------------------------------------------------------------------------------------------------------------------------------------- */

static Vector* CreateARandomVector( int _size , int _range )
{
	register int index;
	Vector *ptrVector = VectorCreate (5, 3);
		
	srand(time(0));
	
     for( index=0  ; index<_size ; index++)
     {
       VectorAdd ( ptrVector , rand() % _range );       
     }
	
     return ptrVector ;
}

/* -------------------------------------------------------------------------------------------------------------------------------------- */

static Vector* CreateAWorstVectorBigToSmall( int _size )
{
	register int index;
	Vector *ptrVector = VectorCreate (5, 3);
	
     for(index=_size  ; index>0 ; index--)
     {
       VectorAdd (ptrVector , index);
     }
     
     return ptrVector ;
}

/* -------------------------------------------------------------------------------------------------------------------------------------- */

static void CheckNullTestAndPrint(ADTErr _result , PrintNameSort _nameSort )
{
    if ( ERR_NOT_INITIALIZED == _result )
    {
      	puts(s_pass);		
    }
    else
    {
          switch ( _nameSort )
	     {
			case BUBBLE_SORT :
							  printf("Bubble Sort ");
							  break;
			case SHAKE_SORT :
							  printf("Shake Sort ");
							  break;
			case INSERTION_SORT :
							  printf("Insertion Sort ");
							  break;
			case QUICK_SORT :
						       printf("Quick Sort ");
						       break;
			case SHELL_SORT :
						       printf("Shell Sort ");
						       break;
			case SELECTION_SORT :
						       printf("Selection Sort ");
						       break;
			case MERGE_SORT :
						       printf("Merge Sort ");
						       break;
			case COUNTING_SORT :
						       printf("Counting Sort ");
						       break;
			case RADIX_SORT :
						       printf("Radix Sort ");
						       break;
			case QUICK_SORT_ITERATIVE :
						       printf("Quick Sort iterative ");
						       break;	
			case MERGE_SORT_ITERATIVE :
						       printf("Merge Sort iterative ");
						       break;							       						       						  
	 	    default :
		     	                 break;				
		}
    
		printf("Test Null : ");    
    		puts(s_failed);	
    }
}

/* -------------------------------------------------------------------------------------------------------------------------------------- */

static Vector* CreateASameItemsVector( int _size  )
{
	int index;
	Vector *ptrVector = VectorCreate (5, 3) ;
	
    for ( index = 0 ; index < _size ; index++)
    {
    	  VectorAdd ( ptrVector , 18 );
    }
    
    return ptrVector;
}

/* -------------------------------------------------------------------------------------------------------------------------------------- */

static void CheckNegitiveTestAndPrint(ADTErr _result , PrintNameSort _nameSort , NameTest _nameTest )
{
	if ( ERR_GENERAL == _result )
	{
		puts(s_pass);	
	}
	else
	{
          switch ( _nameSort )
	     {
			case COUNTING_SORT :
						       printf("Counting Sort ");
						       break;
			case RADIX_SORT :
						       printf("Radix Sort ");
						       break;						       						       
	 	    default :
		     	                 break;				
		}	
		
          switch ( _nameTest )
	     {
			case MIN_BIG_THEN_MAX :
							     printf("min big then max : ");
							     break;
			case NEG_NUM_DIGITS :
							     printf("negitive num of digits : ");
							     break;							     							   		  
	 	    default :
		     	                    break;				
		}
		
		puts(s_failed);				
	}
}

/* -------------------------------------------------------------------------------------------------------------------------------------- */


static Vector* CreateARandomVectorNegativeItems( int _size , int _range )
{
	register int index;
	Vector *ptrVector = VectorCreate (5, 3);
		
	srand(time(0));
	
     for( index=0  ; index<_size ; index++)
     {
       VectorAdd ( ptrVector , (rand() % _range) - _range );       
     }
	
     return ptrVector ;
}

/* -------------------------------------------------------------------------------------------------------------------------------------- */

static Vector* CreateARandomVectorNegativePositiveItems( int _size , int _range )
{
	register int index;
	Vector *ptrVector = VectorCreate (5, 3);
		
	srand(time(0));
	
     for( index=0  ; index<_size ; index++)
     {
       VectorAdd ( ptrVector , (rand() % _range) - (_range/2) );       
     }
	
     return ptrVector ;
}

