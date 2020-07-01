#include <stdlib.h> /* allocation */
#include "heap.h"


#define PARENT(i) ((i)/2)
#define LEFT(i) ((2*(i)))
#define RIGHT(i) ((2*(i)) +1)
#define INDEX_MAX 1
        

struct Heap
{
   Vector *m_vec;
   size_t m_heapSize;
   LessThanComparator m_compFunc ;
};

/* -------------------------------------------------------- local functions -------------------------------------------------------------------- */
static void Heapify(Vector *_vec , size_t _index , size_t _nItems , LessThanComparator _pfLess);
static void HeapifyInsert(Heap *_heap , size_t _numOfItems , void* _data);
static void* HeapifyExtractMax(Heap *_heap );
static void ConvertVectorToHeap(Heap *_heap);

/*================================================================================================================================================*/
/*======================================================== API ===================================================================================*/
/*================================================================================================================================================*/


/* ------------------------------------------------------- Heap Build --------------------------------------------------------------------------- */
Heap* HeapBuild(Vector* _vector, LessThanComparator _pfLess)
{
	Heap *ptrHeap;
	size_t itemsNum=0  ;
	
	if ( NULL == _vector )
	{
		return NULL;
	}
	
	ptrHeap = (Heap*)malloc(sizeof(Heap));
	
	if ( NULL == ptrHeap )
	{
		return NULL;
	}
	
	itemsNum = VectorSize( _vector );
	
	ptrHeap -> m_heapSize =  itemsNum ;	
     ptrHeap -> m_vec = _vector ;	
     ptrHeap -> m_compFunc = _pfLess ;

	ConvertVectorToHeap(ptrHeap);	
		
	return ptrHeap;
}

/* -------------------------------------------------- Heap Destroy ------------------------------------------------------------------------------ */
Vector* HeapDestroy(Heap** _heap)
{
	Vector *vector = NULL ;
	
	if ( (_heap != NULL) && (*_heap != NULL) )
	{
		vector = (*_heap)-> m_vec ;
		free(*_heap);
		*_heap = NULL ;
	}

	return vector;
}


/* -------------------------------------------------- Heap Insert ------------------------------------------------------------------------------ */
HeapResult HeapInsert(Heap* _heap, void* _element)
{
	size_t  numOfItems ;	
		
	if ( NULL == _heap )
	{
		return HEAP_NOT_INITIALIZED;
	}
	
	VectorAppend( _heap->m_vec , _element );  
	numOfItems = VectorSize( _heap->m_vec );
	_heap->m_heapSize = numOfItems ;
	
     HeapifyInsert( _heap , numOfItems , _element );	
	
	return HEAP_SUCCESS ;
}


/* ------------------------------------------------------- Heap Peek -------------------------------------------------------------------------- */
const void* HeapPeek(const Heap* _heap)
{
	void *max ;
	
	if ( NULL == _heap )
	{
		return NULL  ;
	}
	
	if ( (VectorGet( _heap->m_vec, INDEX_MAX , &max )) != VECTOR_SUCCESS )
	{
		return NULL ;
	}
	
	return max ;
}

/* ----------------------------------------------------- HeapExtract ------------------------------------------------------------------------- */
void* HeapExtract(Heap* _heap)
{
	if ( (NULL == _heap) || (_heap->m_heapSize == 0) )
	{
		return NULL ;
	}	
		
	return HeapifyExtractMax(_heap );
}

/* ---------------------------------------------------- Heap Size --------------------------------------------------------------------------- */
size_t HeapSize(const Heap* _heap)
{	
	if ( NULL == _heap )
	{
		return 0 ;
	}
	
	return _heap->m_heapSize;
}


/* ------------------------------------------------- Heap For Each -------------------------------------------------------------------------- */
size_t HeapForEach(const Heap* _heap, ActionFunction _act, void* _context)
{
	size_t index ;
	void* item;
	
	if ( NULL == _heap )
	{
		return 0 ;
	}
	
	for ( index = 1 ; index <= _heap -> m_heapSize ; ++index )
	{
		VectorGet( _heap->m_vec , index , &item);
		if (!_act( item , _context ))
		{
			break;
		}
	}
	
	return index ;
}


/* ------------------------------------------------ Heap Sort ------------------------------------------------------------------------------ */
void HeapSort(Vector* _vec, LessThanComparator _pfLess)
{
	Heap *heap;
	void* max , *last ;
	
	if ( NULL == _vec )
	{
		return ;
	}
	
	heap = HeapBuild( _vec , _pfLess );
	
	while ( heap -> m_heapSize > INDEX_MAX )
	{
		VectorGet(heap->m_vec, INDEX_MAX , &max );
		VectorGet(heap->m_vec, heap -> m_heapSize , &last);
		
		VectorSet( heap->m_vec , INDEX_MAX , last );
		VectorSet( heap->m_vec , heap -> m_heapSize , max );
		
		 heap -> m_heapSize-- ;
		if ( heap -> m_heapSize > 1 )
		{
		Heapify( heap->m_vec , INDEX_MAX , heap -> m_heapSize , _pfLess);
		}
	}
	return;
}

/*================================================================================================================================================*/
/*================================================ local functions ===============================================================================*/
/*================================================================================================================================================*/

/* -------------------------------------------- Convert Vector To Heap -------------------------------------------------------------------------- */
static void ConvertVectorToHeap(Heap *_heap)
{
	int index ;
	size_t itemsNum ;
	
	itemsNum = _heap -> m_heapSize ;
	
	for( index = PARENT(itemsNum) ; index> 0 ; index--)
	{
	  Heapify( _heap -> m_vec , index , itemsNum , _heap->m_compFunc );
	}	
	
	return;
}

/* -------------------------------------------------- Heapify --------------------------------------------------------------------------------- */
static void Heapify(Vector *_vec , size_t _index , size_t _nItems, LessThanComparator _pfLess)
{
	void *parentVal , *leftVal , *rightVal ;
	VectorResult stts=VECTOR_INDEX_OUT_OF_BOUNDS_ERROR ;
	
	if ( LEFT(_index) > _nItems || _nItems == 0 )
	{
		return;
	}
	else
	{
		VectorGet(_vec , LEFT(_index) , &leftVal );
		VectorGet(_vec , _index , &parentVal );	
		if(RIGHT(_index) <= _nItems)
		{
		  stts = VectorGet(_vec , RIGHT(_index) , &rightVal );
		}
		if( (_pfLess(leftVal , parentVal)) && (stts != VECTOR_SUCCESS || (_pfLess(rightVal , parentVal)) ) )
		{
			return;
		}
		else if ( stts == VECTOR_SUCCESS && (_pfLess(leftVal , rightVal)) )
		{
	     	VectorSet(_vec , _index , rightVal );
	     	VectorSet(_vec , RIGHT(_index) , parentVal );
	     	Heapify( _vec , RIGHT(_index) , _nItems , _pfLess );				
		}
		else
		{
	     	VectorSet(_vec , _index , leftVal );
	     	VectorSet(_vec , LEFT(_index) , parentVal );
	     	Heapify( _vec , LEFT(_index) , _nItems , _pfLess );		     				
		}
		
	}
}

/* ---------------------------------------------------- Heapify Insert ------------------------------------------------------------------------- */
static void HeapifyInsert(Heap *_heap , size_t _numOfItems , void* _data)
{
	int change=1 ;
	size_t newData , parent ;	
	void *itemParent ;	
		
	newData = _numOfItems;

	while ( newData>1 && change )
	{
		change = 0 ;
		parent = PARENT(newData) ;
			
          VectorGet(_heap->m_vec, parent , &itemParent) ;
			
		if ( _heap->m_compFunc( itemParent , _data ) )
		{
			change = 1 ;
               VectorSet(_heap->m_vec, parent , _data);
               VectorSet(_heap->m_vec, newData , itemParent);				
		}
		newData = PARENT(newData);
	}

}

/* ------------------------------------------------ Heapify Extract Max ------------------------------------------------------------------------- */
static void* HeapifyExtractMax(Heap *_heap )
{
	void *data , *dataLast;
	
	VectorGet(_heap->m_vec, 1 , &data );
	VectorRemove ( _heap->m_vec ,&dataLast ); 
	VectorSet(_heap->m_vec, 1 , dataLast);
	_heap->m_heapSize -= 1 ;
	
	Heapify(_heap->m_vec , 1 , _heap->m_heapSize , _heap->m_compFunc );
	
	return data;
}



