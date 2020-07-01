#include <stdio.h>
#include <stdlib.h> /* size_t , memory allocation */
#include "ADTDefs.h"
#include "vector.h"
#include "vector_test.h"
#define MAGIC_NUMBER 28011993
#define DEC_FACTOR 2

ADTErr CheckIncrementAlloc(Vector *_vector);
ADTErr CheckDeleteParams(Vector *_vector, int* _data);
ADTErr CheckReduceAlloc(Vector *_vector);

struct Vector
{
     int* m_items;
     size_t m_originalSize;  /* original allocated space for items */
     size_t m_size;          /* actual allocated space for items */
     size_t m_nItems;        /* actual number of items */
     size_t m_blockSize;     /* the chunk size to be allocated when no space */
     int m_magicNum;
};     

Vector* VectorCreate (size_t _initialSize, size_t _extensionBblockSize)
{
     Vector *ptr_vector;
     
     if( 0 == _initialSize && 0 == _extensionBblockSize)
     {
          return NULL;
     }
     
     ptr_vector = (Vector*)malloc(sizeof(Vector));
     
     if ( NULL == ptr_vector)
     {
          return NULL;
     } 
     
     ptr_vector->m_items = (int*)malloc((_initialSize) * sizeof(int));   
     
     if( NULL == ptr_vector->m_items)
     {
          free(ptr_vector);
          return NULL;
     }       
     
     ptr_vector->m_originalSize = _initialSize;
     ptr_vector->m_size = _initialSize;
     ptr_vector->m_nItems = 0;
     ptr_vector->m_blockSize = _extensionBblockSize;
     ptr_vector->m_magicNum = MAGIC_NUMBER;
     
     return ptr_vector;
}

void VectorDestroy (Vector* _vector)
{
     if( (_vector != NULL) && (_vector->m_magicNum == MAGIC_NUMBER))
     {          
       _vector->m_magicNum =0;   
       free(_vector->m_items);     
       free(_vector);
     }  
     return;   
}

ADTErr VectorItemsNum(Vector *_vector , int* _numOfItems)
{
     if( NULL == _vector || NULL == _numOfItems)
     {
         return ERR_NOT_INITIALIZED;
     }
     
     *_numOfItems = _vector->m_nItems;
     
     return ERR_OK;
}

ADTErr VectorGet(Vector *_vector, size_t _index , int *_item)
{
     if( NULL == _vector || NULL == _item)
     {
         return ERR_NOT_INITIALIZED;
     }
     
     if(_index >= _vector->m_nItems)
     {
          return ERR_WORNG_INDEX;
     }
     
     *_item = _vector->m_items[_index];
     
     return ERR_OK ;  
}

ADTErr VectorSet(Vector *_vector, size_t _index , int _item)
{
     if( NULL == _vector)
     {
        return ERR_NOT_INITIALIZED;
     }
     
     if(_index >= _vector->m_nItems)
     {
          return ERR_WORNG_INDEX;
     }    
     
     _vector->m_items[_index] = _item ;
     
     return ERR_OK ;       
}

void VectorPrint(Vector *_vector)
{
     int index;     
     
     if( NULL == _vector)
     {
          return ; 
     }
     
     for(index =0 ; index< _vector->m_nItems; index++)
     {
          printf("%d " , _vector->m_items[index]);
     }
          
}

ADTErr VectorAdd (Vector *_vector ,int _item)
{
     ADTErr resultCheck;     
     
     if( NULL == _vector)
     {
         return ERR_NOT_INITIALIZED;
     }
     
     if((resultCheck = CheckIncrementAlloc(_vector)) != ERR_OK)
     {
          return resultCheck;
     }     
     
     _vector->m_items[_vector->m_nItems] = _item;
     _vector->m_nItems +=1;
     
     return ERR_OK;               
}

ADTErr VectorDelete (Vector *_vector ,int* _item)
{
   ADTErr result;
   
     if((result = CheckDeleteParams(_vector,  _item)) != ERR_OK)
     {
          return result;
     }
     
      *_item = _vector->m_items[_vector->m_nItems-1];
      _vector->m_nItems -=1;
      
     CheckReduceAlloc(_vector);
          
     return ERR_OK;     
}

ADTErr CheckIncrementAlloc(Vector *_vector)
{
     int *tmp;
     
     if(_vector->m_nItems == _vector->m_size)
     {
          if (0 == _vector->m_blockSize)
          {
               return ERR_OVERFLOW;
          }
          
          if((tmp=(int*)realloc(_vector->m_items , sizeof(int)*((_vector->m_size)+_vector->m_blockSize))) == NULL)
          {
               return ERR_REALLOCATION_FAILED;
          } 
          
          _vector->m_size +=_vector->m_blockSize;
          _vector->m_items=tmp;
     }
     
     return ERR_OK;     
}


ADTErr CheckDeleteParams(Vector *_vector, int* _data)
{
     if( NULL == _vector || NULL == _data )
     {
          return ERR_NOT_INITIALIZED;
     }  
        
     if( _vector->m_nItems <=0)
     {
          return ERR_UNDERFLOW;
     }     
     
     return ERR_OK;
}

ADTErr CheckReduceAlloc(Vector *_vector)
{
     int *tmp;
     
      if( (_vector->m_size  > _vector->m_originalSize) && (_vector->m_size - _vector->m_nItems) >= (DEC_FACTOR* _vector->m_blockSize))
      {
             if((tmp=(int*)realloc(_vector->m_items , sizeof(int)*((_vector->m_size)-_vector->m_blockSize))) == NULL)
                {
                return ERR_REALLOCATION_FAILED;
                }
                
          _vector->m_size -=_vector->m_blockSize;
          _vector->m_items=tmp;
      }
      
     return ERR_OK;      
}

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

