#ifndef __EXECUTOR_H__
#define __EXECUTOR_H__

#include "t_queue.h"

typedef struct Executor Executor;

/**  
 * @brief Dynamically create a new executor of given TQueue
 * @param[in] _tasks - pointer to TQueue with tasks
 * @return Executor * - on success / NULL on fail 
 *
 */
Executor* ExecutorCreate(TQueue *_tasks);

/**  
 * @brief Deallocate a previously allocated executor
 * @param[in] _executor - pointer to executor to be deallocated. 
 */
void ExecutorDestroy(Executor *_executor);

/**  
 * @brief executor run , run all the tasks in order
 * @param[in] _executor - pointer to executor  
 */
void ExecutorRun(Executor *_executor);

#endif /* __EXECUTOR_H__ */
