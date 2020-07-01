#include <stdlib.h>             /* size_t , NULL , dynamic allocation , free */
#include "../ADTDefs/ADTDefs.h" /* Error status */
#include "sorts.h"              /* API statements , vector.h */
#include "../stack/stack.h"     /* stack for quick sort iterative */

/*-------------------------------------------------------------- Macro ---------------------------------------------------------------------------*/

 /* swap between two vectores */
#define SWAP_VEC( vector , indexVectorOne , indexVectorTwo , vectorOneData , vectorTwoData )   \
                  {                                                                            \
                      VectorSet( vector , indexVectorOne , vectorTwoData );                    \
                      VectorSet( vector , indexVectorTwo , vectorOneData );                    \
	             }                                                                            \

/*---------------------------------------------------- define ------------------------------------------------------------------------------------*/

 /* radix sort */
#define DECIMAL_BASIS 10
#define MIN_DECIMAL_DIGIT 0
#define MAX_DECIMAL_DIGIT 9

 /* Insertion Sort */
#define GAP_ONE 1
                 
/*---------------------------------------------------- Local functions statements -----------------------------------------------------------------*/

 /* recursive function for quick sort */
static void QuickRec(Vector *_vec , size_t _begin , size_t _end );

 /* for quick sort , choose one pivot and insert him to right index , return the new index */
static int Partition(Vector *_vec , size_t _begin , size_t _end);

 /* shell sort and insertion sort , in insertion sort gap is always equal to one */
static void InsertionSortGap(Vector *_vec ,int _gap);

 /* Selection Sort , find min for not sorted vector and insert to the sorted vector */
static void FindMinAndSwap(Vector *_vec ,int _index , int _size);

 /* recursive function for merge sort */
static void MergeRec(Vector *_vec ,int *_tmpArray , int _begin , int _end );

 /* recive two vectors not sorted and make from the one sorted vector */	
static void Merge(Vector *_vec ,int *_tmpArray , int _begin , int _end );

 /* for Radix sort */
static void CountingSortLocal(Vector *_vec ,int _exp , int _size , int _sizeCountArray , int _tmpArray[] , int _countArray[]);

 /* for bubble sort (in bubble start index is zero always) and shake sort , 
    the function sorted vector with bubble sort from start (index 0 ) to the end ( index 'sizeVector - 1' ) ,
    update if was a change or not */
static void BubbleSortFromStartToEnd( Vector *_vec , int *_size , int _startIndex , int *_change ) ;      

 /* for shake sort , 
    the function sorted vector with bubble sort from end ( index 'sizeVector - 1' ) to the start ( index 'minIndex' ) ,
    update if was a change or not */
static void BubbleSortFromEndToStart( Vector *_vec , int *_minIndex , int _size , int *_change ) ;      

 /* check param for counting sort */
static ADTErr CheckParamCounting( Vector *_vec , int _minValue , int _maxValue ) ; 

 /* counting sort , make the count items array */
static void CountItems( Vector *_vec , int _countArray[] , int _size , int _minValue );

 /* counting sort , sum count array */
static void SumCountArray( int _countArray[] , int _sizeCountArray );
    	    
 /* counting sort , insert items in the right index to tmp array */
static void InsertItemsToTmpArrat( Vector *_vec , int _countArray[] , int _size , int _minValue , int _tmpArray[] );

 /* counting sort , copy the sort tmp array to the original vector */
static void CopyTmpArrayToVector ( Vector *_vec , int _tmpArray[] , int _size ) ;

 /* counting sort and radix sort, free allocation of tmp array and count array */
static void FreeAllocation( int *_countArray , int *_tmpArray );	

 /* radix sort , check params */
static ADTErr CheckParamRadix (Vector *_vec , int _nDigits) ;

 /* quick sort iterative , pop begin and end */
static void PopBeginAndEnd(Stack *_ptrStack , int *_begin , int *_end );	

 /* quick sort iterative , push begin and end */
static void PushBeginAndEnd(Stack *_ptrStack , int _begin , int _end );	
    	    
/*=========================================================== API  =================================================================================*/


/*-------------------------------------------- Bubble Sort ----------------------------------------------------------*/

ADTErr BubbleSort(Vector *_vec)
{
    int change=1 , size ;
    
    if ( NULL == _vec )
    {
        return ERR_NOT_INITIALIZED ;
    }
        
    VectorItemsNum(_vec , &size);	
     
    while(change)
    {
       BubbleSortFromStartToEnd( _vec , &size , 0 , &change ) ;           
    }
     
     return ERR_OK;
}

/*-------------------------------------------- Shake Sort ------------------------------------------------------------*/

ADTErr ShakeSort(Vector *_vec)
{
    int change=1 , size , minIndex=0 ;
    
    if ( NULL == _vec )
    {
       return ERR_NOT_INITIALIZED ;
    }
    
    VectorItemsNum(_vec , &size);
	
    while(change)
    {     
       BubbleSortFromStartToEnd( _vec , &size , minIndex , &change ) ;             
    		 
       if (change)
    	  {
    	     BubbleSortFromEndToStart( _vec , &minIndex , size , &change ) ;    
       }
    }
    return ERR_OK;
}

/*-------------------------------------------- Insertion Sort ------------------------------------------------------------*/

ADTErr InsertionSort(Vector *_vec)
{
    if ( NULL == _vec )
    {
    	  return ERR_NOT_INITIALIZED ;
    }
    	
    InsertionSortGap( _vec , GAP_ONE ); 
       
    return ERR_OK;
}

/*--------------------------------------------- Quick Sort -----------------------------------------------------------------*/

ADTErr QuickSort (Vector *_vec)
{
	int size;
	
	if ( NULL == _vec )
	{
		return ERR_NOT_INITIALIZED ;
	}
	
	VectorItemsNum(_vec , &size);
	
	if ( size >= 2 )
	{
	QuickRec(_vec , 0 , size-1);
	}
	
	return ERR_OK;	
}

/*--------------------------------------------- Quick Sort Iterative ------------------------------------------------------------*/

ADTErr QuickSortIterative (Vector *_vec)
{
	int size , begin , end , indexPivot ;
	Stack *ptrStack;

	if ( NULL == _vec )
	{
		return ERR_NOT_INITIALIZED ;
	}
	
	ptrStack = StackCreate(10 , 10);
	
	VectorItemsNum(_vec , &size);
	
	if ( size >= 2 )
	{
          PushBeginAndEnd( ptrStack , 0 , size-1 );			
	}
	
	while ( !StackIsEmpty(ptrStack) )
	{	
          PopBeginAndEnd( ptrStack , &begin , &end );	
		
		indexPivot = Partition( _vec , begin , end );
		
		if ( indexPivot+1 < end )
		{
		     PushBeginAndEnd( ptrStack , indexPivot+1 , end );
		}
		if ( begin < indexPivot-1 )
		{
		     PushBeginAndEnd( ptrStack , begin , indexPivot-1 );					
		}
	}
	
     StackDestroy(ptrStack);	
	return ERR_OK;	
}

/*--------------------------------------------- Shell Sort --------------------------------------------------------------------*/

ADTErr ShellSort (Vector *_vec)
{
	int size , gap ;
	
	if ( NULL == _vec )
	{
		return ERR_NOT_INITIALIZED ;
	}
	
	VectorItemsNum(_vec , &size);
	gap = size/2 ;
	
	while(gap>0)
	{
		InsertionSortGap(_vec , gap);
		gap /=2;
	}
	
	return ERR_OK;
}

/*---------------------------------------------- Selection Sort ----------------------------------------------------------------*/

ADTErr SelectionSort (Vector *_vec)
{
	register int index ;
	int size ;
	
	if ( NULL == _vec )
	{
		return ERR_NOT_INITIALIZED ;
	}
	
	VectorItemsNum(_vec , &size);
	
	for( index = 0 ; index < size-1 ; index++ )
	{
       FindMinAndSwap( _vec , index  , size);
	}
	
	return ERR_OK;
}

/*------------------------------------------------ Merge Sort ------------------------------------------------------------------*/

ADTErr MergeSort (Vector *_vec)
{
	int size , *tmpArray ;
	
	if ( NULL == _vec )
	{
		return ERR_NOT_INITIALIZED ;
	}
	
     VectorItemsNum(_vec , &size);
	
	if ( size >= 2 )
	{
	    tmpArray = (int*)malloc(size * sizeof(int) );
	    	
         MergeRec(_vec ,tmpArray , 0 , size-1 );	
         
         free(tmpArray);
	}
		
	return ERR_OK;
}

/*------------------------------------------------ Merge Sort Iterative ------------------------------------------------------------------*/

ADTErr MergeSortIterative (Vector *_vec)
{
	int size , *tmpArray , begin=0 , end=1 , i=1 , tmpEnd=1  ;
	
	if ( NULL == _vec )
	{
		return ERR_NOT_INITIALIZED ;
	}
	
     VectorItemsNum(_vec , &size);
	
	if ( size >= 2 )
	{
	    tmpArray = (int*)malloc(size * sizeof(int) );
	    
	    while ( tmpEnd <= size/2)
	    {  	    
	        for ( begin=0 , end=tmpEnd  ; end < size ; begin +=i , end +=i  )
	        {
	    	      Merge( _vec , tmpArray , begin , end ) ;
	        }
	        if ( (end != size-1) && (begin!=size-1) )
	        {
	        	Merge( _vec , tmpArray , begin , size-1 ) ;
	        }
	        
	    	   tmpEnd = ((tmpEnd+1)*2)-1 ;	        
	        i ++;         
         }
         
         free(tmpArray);
	}
		
	return ERR_OK;
}

/*--------------------------------------------- Counting Sort ------------------------------------------------------------------*/

ADTErr CountingSort (Vector *_vec , int _minValue , int _maxValue)
{
	int *countArray , sizeCountArray = _maxValue - _minValue + 1 , size , *tmpArray ;
     ADTErr resultParam ;
     
     if( (resultParam = CheckParamCounting ( _vec , _minValue , _maxValue )) != ERR_OK )  
     {
     	return resultParam ;
     }  
	
     VectorItemsNum(_vec , &size);

	if ( (countArray = (int*)calloc( sizeCountArray , sizeof(int) )) == NULL )
	{
		return ERR_ALLOCATION_FAILED ;
	}
	if ( (tmpArray = (int*)calloc( size , sizeof(int) ) ) == NULL )
	{
		free(countArray) ;
		return ERR_ALLOCATION_FAILED ;
	}

     CountItems( _vec , countArray , size , _minValue );

     SumCountArray( countArray , sizeCountArray );	

     InsertItemsToTmpArrat( _vec , countArray , size , _minValue , tmpArray );

     CopyTmpArrayToVector ( _vec , tmpArray , size ) ;	

     FreeAllocation( countArray , tmpArray );	
	
	return ERR_OK;
}

/*---------------------------------------------------- Radix Sort -------------------------------------------------------------------*/

ADTErr RadixSort (Vector *_vec , int _nDigits)
{
	int index , exp , size , sizeCountArray = MAX_DECIMAL_DIGIT - MIN_DECIMAL_DIGIT + 1 , *tmpArray , *countArray ;
	ADTErr resultParams ;

     if ( (resultParams = CheckParamRadix (_vec , _nDigits)) != ERR_OK )	
     {
     	return resultParams ;
     }		
	if ( 0 == _nDigits )
	{
		return ERR_OK ;
	} 

     VectorItemsNum(_vec , &size);	

	if ((tmpArray = (int*)malloc( size * sizeof(int) ) ) == NULL )
	{
		return ERR_ALLOCATION_FAILED ;
	}
	if ( (countArray = (int*)malloc( sizeCountArray * sizeof(int) )) == NULL )
	{
	     free(tmpArray);		
		return ERR_ALLOCATION_FAILED ;
	}	
	
	for ( index = 1 , exp = 1 ; index <= _nDigits ; index++ , exp *=DECIMAL_BASIS )
	{
	   CountingSortLocal( _vec , exp , size , sizeCountArray , tmpArray , countArray ); 	
	}

     FreeAllocation( countArray , tmpArray );
     	
	return ERR_OK ; 
}

/*==================================================================================================================================================*/
/*================================================================== Local Functions ===============================================================*/
/*==================================================================================================================================================*/


static void QuickRec(Vector *_vec , size_t _begin , size_t _end )
{
	int indexPivot;
	
	if ( _begin < _end )
	{	
	     indexPivot = Partition(_vec , _begin , _end );
		if ( indexPivot-1 >= 0 )
		{
		QuickRec(_vec , _begin , indexPivot-1 );
		}
		QuickRec(_vec , indexPivot+1 , _end);
	} 
	
}

/*----------------------------------------------------------------------------------------------------------------------------------------*/

static int Partition(Vector *_vec , size_t _begin , size_t _end)
{
	int pivot , small=_begin+1  ,  itemDatasmall , big=_end , itemDatabig ;
	
	VectorGet(_vec, _begin , &pivot);
	
	while ( (small <= big) )
	{
		VectorGet(_vec, small , &itemDatasmall);
		VectorGet(_vec, big , &itemDatabig);
		
		while( (itemDatasmall <= pivot) && (small<=big) )
		{
			small++;
			VectorGet(_vec, small , &itemDatasmall);
		}
		
		while( (itemDatabig >= pivot) && (small<=big) )
		{
			big--;
			VectorGet(_vec, big , &itemDatabig);
		}		
		
		if ( small < big )
		{
      		SWAP_VEC(_vec , small , big , itemDatasmall , itemDatabig);
			small++;
		     big--;
		}		
	}
    	SWAP_VEC(_vec , _begin , big , pivot , itemDatabig);		
	return big;				
}

/*----------------------------------------------------------------------------------------------------------------------------------------*/

static void InsertionSortGap(Vector *_vec ,int _gap)
{
	int size , dataLeft , dataRight , indexTmp ;
	register int index ;
	
     VectorItemsNum(_vec , &size);	
     
     for ( index=0 ; index+_gap<size ; index++  )
     {
     	indexTmp=index;
    		VectorGet(_vec, indexTmp , &dataLeft);
    		VectorGet(_vec, indexTmp+_gap , &dataRight);
    		 	
    		while ( (dataLeft > dataRight) && (indexTmp>=0) )
    		{
              VectorSet(_vec, indexTmp , dataRight);
       	    VectorSet(_vec, indexTmp+_gap , dataLeft); 
       		   
       	    if ( indexTmp-_gap >= 0)
       	    {
       		   indexTmp -=_gap;
    		        VectorGet(_vec, indexTmp , &dataLeft);
    		        VectorGet(_vec, indexTmp+_gap , &dataRight);       		   	
       	    }
       	    else
              {
       		  break;
       	    }	      		 		
    		 }  		 	     	
     }
}

/*----------------------------------------------------------------------------------------------------------------------------------------*/

static void FindMinAndSwap(Vector *_vec ,int _index , int _size)
{	
	int tmpMin , firstIndex , firstdata , indexMin , min;
	
	firstIndex = _index ;
	VectorGet(_vec, firstIndex , &firstdata);
	indexMin = _index ;
	VectorGet(_vec, indexMin , &min);
	
	for ( ; _index<_size ; _index++)
	{
		VectorGet(_vec, _index , &tmpMin);
		if ( tmpMin < min )
		{
			min = tmpMin ;
			indexMin = _index ;
		}
	}
	
	SWAP_VEC(_vec , firstIndex , indexMin , firstdata , min );
}

/*----------------------------------------------------------------- Merge Sort ------------------------------------------------------------------*/

static void MergeRec(Vector *_vec ,int *_tmpArray , int _begin , int _end )
{
	int middle ;
	
	if ( _begin >= _end )
	{
		return;
	}
	
	middle = (_begin + _end) / 2 ;
	MergeRec( _vec ,_tmpArray , _begin , middle);
	MergeRec( _vec , _tmpArray , middle+1 , _end);
	Merge(_vec , _tmpArray , _begin , _end);	
}
	
/*----------------------------------------------------------------------------------------------------------------------------------------*/

static void Merge(Vector *_vec ,int *_tmpArray , int _begin , int _end )
{
	int leftEnd = (_end + _begin)/2 , left = _begin , dataLeft ;
	int rightStart = leftEnd + 1 , right = rightStart , dataRight ;
	int indexTmpArray = _begin ;
	
	while ( (left <= leftEnd) && (right <= _end) )
	{
         VectorGet(_vec, left , &dataLeft);	
         VectorGet(_vec, right , &dataRight);	
         
         if ( dataLeft <= dataRight )
         {
         	   _tmpArray[indexTmpArray] = dataLeft ;
         	   left++ ;
         }
         else
         {
         	   _tmpArray[indexTmpArray] = dataRight ;
         	   right++ ;
         }
         indexTmpArray++ ;
	}
	
	while( left<=leftEnd)
	{
	    VectorGet(_vec, left , &dataLeft);
	    _tmpArray[indexTmpArray] = dataLeft ;
	    indexTmpArray++ ;	
	    left++ ;
	}
	
	while ( right <= _end)
	{
	    VectorGet(_vec, right , &dataRight);
	    _tmpArray[indexTmpArray] = dataRight ;
	    indexTmpArray++ ;
	    right++ ;
	}
	
     while ( _begin <= _end)
     {
	     VectorSet(_vec, _begin , _tmpArray[_begin]);	
	     _begin ++ ;
	}
}

/*----------------------------------------------------------------------------------------------------------------------------------------*/

static void CountingSortLocal(Vector *_vec ,int _exp , int _size , int _sizeCountArray , int _tmpArray[] , int _countArray[])
{
	register int index;
	int item , indexNew ;

	
	for ( index = 0 ; index < _sizeCountArray ; index++ )
	{
		_countArray[index] = 0 ;
	}
	
	for ( index = 0 ; index < _size ; index++ )
	{
		VectorGet(_vec, index , &item);		
		_countArray[(item/_exp)%DECIMAL_BASIS] +=1;
	}
	
	for ( index = 1 ; index < _sizeCountArray ; index++ )
	{
		_countArray[index] = _countArray[index] + _countArray[index-1] ;
	}
	
	for ( index = _size-1 ; index >=0 ; index-- )
	{
		VectorGet(_vec, index , &item);
		indexNew = _countArray[(item/_exp)%DECIMAL_BASIS] ;
		_countArray[(item/_exp)%DECIMAL_BASIS] -=1;
		_tmpArray[indexNew-1] = item ; 
	}
	
	for ( index = 0 ; index<_size ; index++ )
	{
		VectorSet(_vec, index , _tmpArray[index]);
	}

}

/*----------------------------------------------------------------------------------------------------------------------------------------*/

static void BubbleSortFromStartToEnd( Vector *_vec , int *_size , int _startIndex , int *_change ) 
{ 
    register int indexLeft , indexRight  ;
    int  dataLeft , dataRight ;	    	 
     
    for( indexLeft = _startIndex , indexRight = indexLeft+1 , *_change=0 ; indexRight < *_size ; indexLeft++ , indexRight++ )
     {
    		 VectorGet( _vec , indexLeft , &dataLeft );
    	      VectorGet( _vec , indexRight , &dataRight );   	
    		 		 	
           if( dataLeft > dataRight )
           {
              SWAP_VEC( _vec , indexLeft , indexRight , dataLeft , dataRight );
        	    *_change=1;
         	 }
    	}      		 
     *_size-- ;
}

/*----------------------------------------------------------------------------------------------------------------------------------------*/

static void BubbleSortFromEndToStart( Vector *_vec , int *_minIndex , int _size , int *_change ) 
{
    register int left , right ;
    int  dataLeft , dataRight ;
    
    for (right = _size-1 , left = _size-2 , *_change=0 ; left>=*_minIndex ; left-- , right-- )
    {
    		VectorGet(_vec, left , &dataLeft);
    	    	VectorGet(_vec, right , &dataRight);
    		 	
          if( dataLeft > dataRight )
          {
               SWAP_VEC(_vec , left , right , dataLeft , dataRight);
               *_change=1;
    	     }    		 	
    }
    *_minIndex++;   	   
}

/*----------------------------------------------------------------------------------------------------------------------------------------*/

static ADTErr CheckParamCounting( Vector *_vec , int _minValue , int _maxValue ) 
{
	if ( NULL == _vec )
	{
		return ERR_NOT_INITIALIZED ;
	}
	if ( _minValue > _maxValue )
	{
		return ERR_GENERAL ;
	}		
	return ERR_OK;
}

/*----------------------------------------------------------------------------------------------------------------------------------------*/

static void CountItems( Vector *_vec , int _countArray[] , int _size , int _minValue )
{
	register int index ;
	int item ;
		
	for ( index = 0 ; index < _size ; index++ )
	{
		VectorGet(_vec, index , &item);
		
		_countArray[item - _minValue] +=1;
	}
}

/*----------------------------------------------------------------------------------------------------------------------------------------*/

static void SumCountArray( int _countArray[] , int _sizeCountArray )
{
	register int index ;
	
	for ( index = 1 ; index < _sizeCountArray ; index++ )
	{
		_countArray[index] = _countArray[index] + _countArray[index-1] ;
	}
}

/*----------------------------------------------------------------------------------------------------------------------------------------*/

static void InsertItemsToTmpArrat( Vector *_vec , int _countArray[] , int _size , int _minValue , int _tmpArray[] )
{
	register int index ;
	int item , indexNew ;
	
	for ( index = _size-1 ; index >=0 ; index-- )
	{
		VectorGet(_vec, index , &item);
		indexNew = _countArray[ item - _minValue] ;
		_countArray[ item - _minValue] -=1;
		_tmpArray[indexNew-1] = item ; 
	}
}	

/*----------------------------------------------------------------------------------------------------------------------------------------*/

static void CopyTmpArrayToVector ( Vector *_vec , int _tmpArray[] , int _size ) 
{
	register int index ;
		
	for ( index = 0 ; index<_size ; index++ )
	{
		VectorSet( _vec, index , _tmpArray[index]);
	}
}	

/*----------------------------------------------------------------------------------------------------------------------------------------*/

static void FreeAllocation( int *_countArray , int *_tmpArray )
{
	free(_countArray);
	free(_tmpArray);
}

/*----------------------------------------------------------------------------------------------------------------------------------------*/

static ADTErr CheckParamRadix (Vector *_vec , int _nDigits) 
{
	if ( NULL == _vec )
	{
		return ERR_NOT_INITIALIZED ;
	}
	
	if ( _nDigits < 0 )
	{
		return ERR_GENERAL ;
	}
	
	return ERR_OK;
}

/*----------------------------------------------------------------------------------------------------------------------------------------*/

static void PopBeginAndEnd(Stack *_ptrStack , int *_begin , int *_end )
{
	     StackPop( _ptrStack , _end ) ;
		StackPop( _ptrStack , _begin ) ;
}

/*----------------------------------------------------------------------------------------------------------------------------------------*/

static void PushBeginAndEnd(Stack *_ptrStack , int _begin , int _end )
{
		StackPush(_ptrStack , _begin );
		StackPush(_ptrStack , _end );	
}

/*----------------------------------------------------------------------------------------------------------------------------------------*/

