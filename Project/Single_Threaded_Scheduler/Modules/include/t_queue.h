#ifndef __T_QUEUE_H__
#define __T_QUEUE_H__

#include <stddef.h>  /* size_t */
#include "task.h"
#include "heap.h"

typedef struct TQueue TQueue ;


/*===============================================================================================================================================*/
/*============================================================== API ============================================================================*/
/*===============================================================================================================================================*/

/**  
 * @brief Dynamically create a new TQueue object of given number of tasks 
 * @param[in] _numOfTasks - number of tasks that will be run in the program
 * @return TQueue * - on success / NULL on fail 
 *
 * @warning if _numOfTasks will be 0 or a negativ number , will return null. 
 *
 */
TQueue* TQueueCreate(size_t _numOfTasks);


/**  
 * @brief Deallocate a previously allocated TQueue
 * @param[in] _t_queue - TQueue to be deallocated. 
 */
void TQueueDestroy(TQueue *_t_queue);

/**  
 * @brief get number of tasks in TQueue
 * @param[in] _t_queue - pointer to TQueue
 * @return size_t  - the number of tasks in TQueue
 *
 */
size_t TQueueGetSize(TQueue *_t_queue);

/**  
 * @brief Extract the first task in the TQueue (the task with the minimum next time run )
 * @param[in] _t_queue - pointer to TQueue
 * @return pointer to task, can be null if TQueue is empty. 
 *
 */
Task* TQueuePop(TQueue *_t_queue);

/**  
 * @brief Add an task to the TQueue preserving heap property.  
 * @param[in] _t_queue - TQueue to insert task to.
 * @param[in] _task - task to insert. can't be null
 * 
 */
void TQueuePush(TQueue *_t_queue , Task *_task);

/**  
 * @brief get the heap that in TQueue .  
 * @param[in] _t_queue - pointer to TQueue.
 * @return pointer to heap . 
 * 
 */
Heap* TQueueGetHeap(TQueue* _t_queue);

#endif /* __T_QUEUE_H__ */
