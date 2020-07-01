#ifndef __TASK_H__
#define __TASK_H__


typedef struct Task Task;


typedef int(*TaskFunction)(void* _context);
typedef int(*TaskComparator)(const void *_left, const void *_right);

/*=========================================================================================================*/
/*============================================== API ======================================================*/
/*=========================================================================================================*/

/**  
 * @brief Dynamically create a new task object of given task function and context
 * @param[in] _func - int(*TaskFunction)(void* _context)
 * @param[in] _context - address of int variable
 * @return Task * - on success / NULL on fail 
 *
 */
Task* TaskCreate(TaskFunction _func , void* _context );

/**  
 * @brief Deallocate a previously allocated task
 * @param[in] _task - pointer to task 
 */
void TaskDestroy(void* _task);

/**  
 * @brief get next time run of task
 * @param[in] _task - pointer to task  
 * @return int - int time run
 */
int TaskGetNextTimeRun(Task *_task);

/**  
 * @brief get context of task
 * @param[in] _task - pointer to task  
 * @return void* - void* cuntext
 */
void* TaskGetContext(Task *_task);

/**  
 * @brief get period of task
 * @param[in] _task - pointer to task  
 * @return int - int period
 */
int TaskGetPeriod(Task *_task);

/**  
 * @brief get id of the task
 * @param[in] _task - pointer task
 * @return id - int id
 *
 */
int TaskGetId(Task *_task);


int TaskRun(Task *_task);

void TaskUpdateDueTime(Task *_task);

#endif /* __TASK_H__ */
