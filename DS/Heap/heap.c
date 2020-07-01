#include <stdlib.h> /* allocation */
#include "ADTDefs.h"
#include "heap.h"


#define PARENT(i) ((i-1)/2)
#define LEFT(i) ((2*(i)) +1)
#define RIGHT(i) ((2*(i)) +2)
#define MAGIC_NUMBER 28011993
        

struct Heap
{
   Vector *m_vec;
   size_t m_heapSize;
   int m_magicNum;
};


static void Heapify(Vector *_vec , size_t _index , int _nItems);
static void HeapifyInsert(Heap *_heap , int _numOfItems , int _data);
static void HeapifyExtractMax(Heap *_heap ,int *_data);

Heap* HeapBuild(Vector *_vec)
{
	Heap *ptrHeap;
	int itemsNum=0 , index ;
	
	if ( NULL == _vec )
	{
		return NULL;
	}
	
	ptrHeap = (Heap*)malloc(sizeof(Heap));
	
	if ( NULL == ptrHeap )
	{
		return NULL;
	}
	
	VectorItemsNum(_vec , &itemsNum);
	
	ptrHeap->m_heapSize =  itemsNum ;	
     ptrHeap -> m_vec = _vec ;	
	ptrHeap->m_magicNum = MAGIC_NUMBER;
	
	for( index = PARENT(itemsNum-1) ; index>= 0 ; index--)
	{
	  Heapify(ptrHeap -> m_vec , index , itemsNum);
	}
		
	return ptrHeap;
}

void HeapDestroy(Heap *_heap)
{
	if ( (_heap != NULL) && (_heap->m_magicNum == MAGIC_NUMBER) )
	{
		_heap->m_magicNum = 0 ;
		free(_heap);
	}
	return;
}

ADTErr HeapInsert(Heap *_heap , int _data)
{
	int  numOfItems ;	
		
	if ( NULL == _heap )
	{
		return ERR_NOT_INITIALIZED;
	}
	
	VectorAdd (_heap->m_vec , _data);
	VectorItemsNum(_heap->m_vec , &numOfItems);
	_heap->m_heapSize = numOfItems ;
	
	
     HeapifyInsert(_heap , numOfItems , _data);	
	
	return ERR_OK ;
}

ADTErr HeapMax(Heap *_heap , int *_data)
{
	ADTErr result;	
	
	if ( (NULL == _heap) || (NULL == _data) )
	{
		return ERR_NOT_INITIALIZED ;
	}
	
	if ( (result=VectorGet(_heap->m_vec, 0 , _data)) == ERR_WORNG_INDEX )
	{
		return ERR_UNDERFLOW ;
	}
	
	return ERR_OK ;
	
}

ADTErr HeapExtractMax(Heap *_heap , int *_data)
{
	if ( (NULL == _heap) || (NULL == _data) )
	{
		return ERR_NOT_INITIALIZED ;
	}	
	
	if ( _heap->m_heapSize == 0 )
	{
		return ERR_UNDERFLOW ;
	}
		
	HeapifyExtractMax(_heap , _data);
	
	return ERR_OK;
}


int HeapItemsNum(Heap *_heap)
{	
	if ( NULL == _heap )
	{
		return ERR_PTR_NULL;
	}
	
	return _heap->m_heapSize;
}

void HeapPrint(Heap *_heap)
{
	if ( _heap != NULL )
	{
	VectorPrint(_heap->m_vec);
	}
	return;
}


static void Heapify(Vector *_vec , size_t _index , int _nItems)
{
	int parentVal , leftVal , rightVal ;
	ADTErr stts = ERR_WORNG_INDEX ;
	if ( LEFT(_index) > _nItems-1 || _nItems == 0 )
	{
		return;
	}
	else
	{
		VectorGet(_vec , LEFT(_index) , &leftVal );
		VectorGet(_vec , _index , &parentVal );	
		if(RIGHT(_index) <= _nItems-1)
		{
		  stts = VectorGet(_vec , RIGHT(_index) , &rightVal );
		}
		if((parentVal > leftVal) && (stts != ERR_OK || parentVal > rightVal) )
		{
			return;
		}
		else if ( stts == ERR_OK && rightVal > leftVal)
		{
	     	VectorSet(_vec , _index , rightVal );
	     	VectorSet(_vec , RIGHT(_index) , parentVal );
	     	Heapify( _vec , RIGHT(_index) , _nItems );				
		}
		else
		{
	     	VectorSet(_vec , _index , leftVal );
	     	VectorSet(_vec , LEFT(_index) , parentVal );
	     	Heapify( _vec , LEFT(_index) , _nItems );		     				
		}
		
	}
}

static void HeapifyInsert(Heap *_heap , int _numOfItems , int _data)
{
	int newData , change=1 , itemParent , parent ;			
		
	newData = _numOfItems-1;

	while ( newData>=0 && change )
	{
		change = 0 ;
		parent = PARENT(newData) ;
			
          VectorGet(_heap->m_vec, parent , &itemParent) ;
			
		if ( itemParent < _data )
		{
			change = 1 ;
               VectorSet(_heap->m_vec, parent , _data);
               VectorSet(_heap->m_vec, newData , itemParent);				
		}
		newData = PARENT(newData);
	}

}

static void HeapifyExtractMax(Heap *_heap ,int *_data)
{
	int dataLast , parent , change=1 , left , right , itemLeft , itemRight , resultRight ;
	
	VectorGet(_heap->m_vec, 0 , _data);
	VectorDelete (_heap->m_vec ,&dataLast); 
	VectorSet(_heap->m_vec, 0 , dataLast);
	_heap->m_heapSize -= 1 ;
	
	Heapify(_heap->m_vec , 0 , _heap->m_heapSize);
}

