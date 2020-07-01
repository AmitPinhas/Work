#include <stdlib.h> /* memory allocation */
#include <assert.h>
#include "vector.h"
#include "vector_test.h"

#define MAGIC_NUMBER 0XBEEFBEEF
#define DECREASE_FACTOR 2


struct Vector 
{
     int m_magicNum;
     void** m_items;
     size_t m_originalSize;  /* original allocated space for items */
     size_t m_size;          /* actual allocated space for items */
     size_t m_nItems;        /* actual number of items */
     size_t m_blockSize;     /* the chunk size to be allocated when no space */
};  

/*--------------------------------------------------------- local function -------------------------------------------------------------------------*/
static VectorResult CheckIncrementAlloc(Vector *_vector,void* _item);
static VectorResult CheckDeleteParams(Vector *_vector, void** _pValue);
static void CheckReduceAlloc(Vector *_vector,void** _item);
static void DestroyElement(Vector* _vector, void (*_elementDestroy)(void* _item));
static void InitMembersVector(Vector* _vector , size_t _initialCapacity, size_t _blockSize);
     
/* ============================================================ API =============================================================================== */

/* ------------------------------------------------------- Vector Create -------------------------------------------------------------------------- */
Vector* VectorCreate (size_t _initialCapacity, size_t _blockSize)
{
     Vector *ptrVector ;
     
     if( ( 0 == _initialCapacity ) && ( 0 == _blockSize ) )
     {
          return NULL;
     }
     
     ptrVector = (Vector*)malloc(sizeof(Vector));     
     if ( NULL == ptrVector)
     {
          return NULL;
     } 
     
     ptrVector->m_items = (void**)malloc((_initialCapacity+1) * sizeof(void*));       
     if( NULL == ptrVector->m_items )
     {
          free(ptrVector);
          return NULL;
     }       

     InitMembersVector( ptrVector ,  _initialCapacity ,  _blockSize);  
     ptrVector -> m_magicNum = MAGIC_NUMBER;	 
     
     return ptrVector;
}
/*---------------------------------------------------------- Vector Destroy ------------------------------------------------------------------------*/
void VectorDestroy(Vector** _vector, void (*_elementDestroy)(void* _item))
{	
     if ( !_vector || !*_vector || !((*_vector)->m_magicNum == MAGIC_NUMBER) )
     {
     	return; 
     }   
           
     (*_vector)->m_magicNum = 0XDEADBEEF;         

     DestroyElement( *_vector,  _elementDestroy );
       
     free((*_vector)->m_items);     
     free(*_vector);
     *_vector = NULL ;
     
     return;    
}
/*------------------------------------------------------------ Vector Size -------------------------------------------------------------------------*/
size_t VectorSize(const Vector* _vector)
{
     if( NULL == _vector || !(_vector->m_magicNum == MAGIC_NUMBER) )
     {
         return 0;
     }
     
     return _vector->m_nItems;
}
/*------------------------------------------------------------- Vector Get -------------------------------------------------------------------------*/
VectorResult VectorGet(const Vector* _vector, size_t _index, void** _pValue)
{
     if( NULL == _vector || NULL == _pValue )
     {
         return VECTOR_UNITIALIZED_ERROR;
     }
          
     if( _index > _vector->m_nItems )
     {
         return VECTOR_INDEX_OUT_OF_BOUNDS_ERROR;
     }
     
     *_pValue = _vector->m_items[_index];
     
     return VECTOR_SUCCESS ;  
}
/*------------------------------------------------------------- Vector Set -------------------------------------------------------------------------*/
VectorResult VectorSet(Vector* _vector, size_t _index, void*  _value)
{
     if( NULL == _vector || !(_vector->m_magicNum == MAGIC_NUMBER) )
     {
        return VECTOR_UNITIALIZED_ERROR;
     }
     
     if(_index > _vector->m_nItems)
     {
          return VECTOR_INDEX_OUT_OF_BOUNDS_ERROR;
     }    
     
     _vector->m_items[_index] = _value ;
     
     return VECTOR_SUCCESS ;       
}

/*---------------------------------------------------------- Vector Append -------------------------------------------------------------------------*/
VectorResult VectorAppend(Vector* _vector, void* _item)
{
     VectorResult resultCheck;     
     
     if( NULL == _vector || NULL == _item || !(_vector->m_magicNum == MAGIC_NUMBER) )
     {
         return VECTOR_UNITIALIZED_ERROR;
     }
     
     if((resultCheck = CheckIncrementAlloc(_vector,_item)) != VECTOR_SUCCESS)
     {
          return resultCheck;
     }     
 
     _vector->m_items[++_vector->m_nItems] = _item;
     
     return VECTOR_SUCCESS;               
}
/*------------------------------------------------------------ Vector Remove -----------------------------------------------------------------------*/
VectorResult VectorRemove(Vector* _vector, void** _pValue)
{
   VectorResult result;
   
     if((result = CheckDeleteParams(_vector,  _pValue)) != VECTOR_SUCCESS )
     {
          return result;
     }
     
     *_pValue = _vector->m_items[_vector->m_nItems--];
      
     CheckReduceAlloc(_vector , _pValue);
          
     return VECTOR_SUCCESS;     
}

/* --------------------------------------------------------- Vector capacity ---------------------------------------------------------------------- */
size_t VectorCapacity(const Vector* _vector)
{
     if( NULL == _vector || !(_vector->m_magicNum == MAGIC_NUMBER) )
     {
         return 0;
     }	
     
     return _vector -> m_size ;
}

/* ------------------------------------------------------- Vector for each ------------------------------------------------------------------------ */
size_t VectorForEach(const Vector* _vector, VectorElementAction _action, void* _context)
{
	int index=0;
	size_t size;
	
	if ( NULL == _action || NULL == _vector)
	{
		return 0;
	}
	
	size = VectorSize(_vector);
	
     for( index = 1; index <= size ; index++ )
     {
        if(_action( _vector->m_items[index] , index , _context) == 0)
        {
 		 break;
        }	
     }
       
 	return index - 1;
}


/*========================================================= local function =========================================================================*/
static VectorResult CheckIncrementAlloc(Vector *_vector,void* _item)
{
     void **tmp;
     
     if(_vector->m_nItems == _vector->m_size-1)
     {
          if (0 == _vector->m_blockSize)
          {
               return VECTOR_OVERFLOW_ERROR;
          }
          
          if((tmp=(void**)realloc(_vector->m_items , sizeof(void*)*((_vector->m_size)+_vector->m_blockSize))) == NULL)
          {
               return VECTOR_ALLOCATION_ERROR;
          } 
          
          _vector->m_size +=_vector->m_blockSize;
          _vector->m_items=tmp;
     }
     
     return VECTOR_SUCCESS;     
}

/*--------------------------------------------------------------------------------------------------------------------------------------------------*/
static VectorResult CheckDeleteParams(Vector *_vector, void** _pValue)
{
     if( NULL == _vector || NULL == _pValue )
     {
          return VECTOR_UNITIALIZED_ERROR;
     }  
        
     if( _vector->m_nItems <=0)
     {
          return VECTOR_UNDERFLOW_ERROR;
     }     
     
     return VECTOR_SUCCESS;
}
/*--------------------------------------------------------------------------------------------------------------------------------------------------*/
static void CheckReduceAlloc(Vector *_vector,void** _item)
{
     void** tmp;
     
      if( (_vector->m_size  > _vector->m_originalSize) && (_vector->m_size - _vector->m_nItems) >= (DECREASE_FACTOR* _vector->m_blockSize))
      {
             if((tmp=(void**)realloc(_vector->m_items , sizeof(void*)*((_vector->m_size)-_vector->m_blockSize))) == NULL)
             {
                  return ;
             }
                
          _vector->m_size -=_vector->m_blockSize;
          _vector->m_items=tmp;
      }
      
     return ;     
}

/*--------------------------------------------------------------------------------------------------------------------------------------------------*/
static void DestroyElement(Vector* _vector, void (*_elementDestroy)(void* _item))
{
	int index;
	
	 if ( _elementDestroy != NULL )
	{
	
     	for ( index = 0 ; index < _vector -> m_nItems ; index++)
     	{
        		_elementDestroy( _vector -> m_items[index]);
    		}	
    	}
     
     return;
}

/*--------------------------------------------------------------------------------------------------------------------------------------------------*/
static void InitMembersVector(Vector* _vector , size_t _initialCapacity, size_t _blockSize)
{
     _vector -> m_originalSize = _initialCapacity+1;
     _vector -> m_size = _initialCapacity+1;
     _vector -> m_nItems = 0;
     _vector -> m_blockSize = _blockSize;
     
	return;
}

/* ============================================== Functions of vector_test.h ====================================================================== */

void GetOriginalSize(Vector *_vector , size_t *_m_originalSize)
{
    *_m_originalSize = _vector-> m_originalSize;
}

void GetSize(Vector *_vector , size_t *_m_size)
{
   *_m_size =  _vector-> m_size ;
}

void GetBlock(Vector *_vector , size_t *_m_blockSize)
{
    *_m_blockSize = _vector-> m_blockSize;
}

void GetMagic(Vector *_vector , int *_m_magicNum)
{
     *_m_magicNum = _vector->m_magicNum;
}

