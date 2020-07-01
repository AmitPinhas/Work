#include <stdio.h>
#include <stdlib.h> /* size_t , memory allocation */
#include "../ADTDefs/ADTDefs.h"
#include "queue.h"
#include "queue_test.h"
#define MAGIC_NUMBER 28011993

struct Queue
{
     int m_magicNum;
     void** m_queue;
     size_t m_size;         
     size_t m_head;          /* index of head in m_queue. */
     size_t m_tail;          /* index of tail in m_queue. */
     size_t m_nItems;
}; 

Queue* QueueCreate (size_t _size)
{
     Queue *ptrQueue = NULL;
     
     if( 0 == _size)
     {
          return NULL;
     }
     
     ptrQueue = (Queue*)calloc(1 , sizeof(Queue)); 
     
     if( NULL == ptrQueue )
     {
          return NULL;
     }       
     
     ptrQueue->m_queue = (void**)malloc( (_size) * sizeof(void*) );
     
     if( NULL == ptrQueue->m_queue )
     {
          free(ptrQueue);
          return NULL;
     }     
     
     ptrQueue->m_size = _size;
     ptrQueue->m_magicNum = MAGIC_NUMBER;
     
     return ptrQueue;     
}


void   QueueDestroy(Queue *_queue , void (*_elementDestroy)(void* _item))
{
	     int numElement , index;
	     
     if(_queue != NULL && _queue->m_magicNum == MAGIC_NUMBER)
     {          
       _queue->m_magicNum =0; 

	if (   _elementDestroy != NULL )
	{
    	 for(index = _queue->m_head , numElement =_queue->m_nItems ; numElement != 0 ; numElement-- , index = (index+1) % (_queue->m_size) )
   	  {
          _elementDestroy( _queue->m_queue[index]);
   	  }		
	} 
         
       free(_queue->m_queue);     
       free(_queue);
     }       
}

ADTErr QueueInsert(Queue *_queue , void* _item)
{
     if( NULL == _queue)
     {
          return ERR_NOT_INITIALIZED;
     }
     
     if( _queue->m_nItems == _queue->m_size )
     {
          return ERR_OVERFLOW;
     }  
     
     _queue->m_queue[_queue->m_tail] = _item;
     _queue->m_tail = (_queue->m_tail+1) % (_queue->m_size) ; 
     _queue->m_nItems++ ;  
     
     return ERR_OK;
}

ADTErr QueueRemove(Queue *_queue , void** _item)
{
     if( NULL == _queue || NULL == _item)
     {
          return ERR_NOT_INITIALIZED;
     }
     
     if( _queue->m_nItems == 0 )
     {
          return ERR_UNDERFLOW;
     }  
     
     *_item = _queue->m_queue[_queue->m_head] ;
     _queue->m_head = (_queue->m_head+1) % (_queue->m_size) ; 
     _queue->m_nItems-- ;  
     
     return ERR_OK;
}

int    QueueIsEmpty(Queue *_queue)
{
     if( NULL == _queue || _queue->m_nItems == 0 )
     {
          return TRUE;
     } 
     
     return FALSE;
}

size_t QueueForEach(const Queue *_queue, QueueElementAction _action, void* _context)
{
     int numElement , index=0;
     
     if ( NULL == _queue)
     {
          return index;
     }
     
     for(index = _queue->m_head , numElement =_queue->m_nItems ; numElement != 0 ; numElement-- , index = (index+1) % (_queue->m_size) )
     {
          if ( _action(_queue->m_queue[index] , index , _context) == 0 )
          {
          	break;
          }
          
     }
     
     return index;	
}


void GetSizeQueue(Queue *_queue , size_t *_m_size)
{
     *_m_size = _queue->m_size;
}

void GetHead(Queue *_queue , size_t *_m_head)
{
    *_m_head = _queue->m_head; 
}

void GetTail(Queue *_queue , size_t *_m_tail)
{
   *_m_tail = _queue->m_tail;  
}

void GetNumOfItems(Queue *_queue , size_t *_m_nItems)
{
     *_m_nItems = _queue->m_nItems;
}

void GetMagic(Queue *_queue , int *_m_magicNum)
{
     *_m_magicNum = _queue->m_magicNum;
}
