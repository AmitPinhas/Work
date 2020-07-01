#ifndef __QUEUE_H__
#define __QUEUE_H__

#include "ADTDefs.h"

#define TRUE 1
#define FALSE 0 

typedef struct Queue Queue;
typedef int(*QueueElementAction)(void* _element, size_t _index, void* _context);

/*
    Description: Makes pointer to the cyclic queue.
    Input: size of the queue.
    Output: OK / NULL .
    ERROR: OK - Pointer successfully returned.
           NULL - new pointer=null , if size=0 or allocation failed.
*/
Queue* QueueCreate (size_t _size);

/*
    Description: free dinamic allocation to the queue.
    Input: pointer to the queue.
    Output: no output.
    ERROR: no error.
*/ 
void  QueueDestroy(Queue *_queue , void (*_elementDestroy)(void* _item));

/*
    Description: inserting an item to the end of the queue.
    Input: pointer to the queue and item.
    Output: ERR_OK / ERR_OVERFLOW / ERR_NOT_INITIALIZED.
    ERROR: ERR_OK - item add successfully.
           ERR_OVERFLOW - queue full.
           ERR_NOT_INITIALIZED - param pointer null. 
*/
ADTErr QueueInsert(Queue *_queue , void* _item);

/*
    Description: delete an item from the head of the queue.
    Input: pointer to the queue and pointer to the int item.
    Output: ERR_OK / ERR_OVERFLOW / ERR_NOT_INITIALIZED.
    ERROR: ERR_OK - item delete successfully.
           ERR_UNDERFLOW - queue is empty.
           ERR_NOT_INITIALIZED - queue pointer null or _item null or both. 
*/
ADTErr QueueRemove(Queue *_queue , void** _item);

/*
    Description: check if queue is empty.
    Input: pointer to the queue.
    Output: TRUE / FALSE.
    ERROR: TRUE - queue empty or pointer null.
           FALSE - queue no empty. 
*/ 
int QueueIsEmpty(Queue *_queue);


size_t QueueForEach(const Queue *_queue, QueueElementAction _action, void* _context);

#endif /* __QUEUE_H__ */
