#ifndef __SCHEDULER_H__
#define __SCHEDULER_H__

#include "task.h"

typedef struct Scheduler Scheduler ;

/*=========================================================================================================*/
/*============================================ API ========================================================*/
/*=========================================================================================================*/

/**  
 * @brief Dynamically create a new scheduler object of given number of tasks 
 * @param[in] _numOfTasks - number of tasks that will be run in the program
 * @return Scheduler * - on success / NULL on fail 
 *
 * @warning if _numOfTasks will be 0 or a negativ number , will return null. 
 *
 */
Scheduler* SchedulerCreate(size_t _numOfTasks);

/**  
 * @brief Deallocate a previously allocated scheduler
 * @param[in] _scheduler - pointer to pointer to scheduler to be deallocated. 
 */
void SchedulerDestroy(Scheduler **_scheduler);

/**  
 * @brief add tasks to the scheduler
 * @param[in] *_scheduler - pointer to the scheduler
 * @param[in] _func - task function , int(*TaskFunction)(void* _context); 
 * @param[in] *_context - pointer from int to the context , the context is the number of run of the func
 * @param[in] period - how long to run the function in milliseconds
 *
 * @warning if _scheduler will be null the add will failed  
 * @warning if _func will be not from this type int(*TaskFunction)(void* _context)  the add will failed 
 * @warning if _context will be 0 or a negativ number , the add will failed 
 * @warning if period will be 0 or a negativ number , he add will failed    
 *
 */
void SchedulerAdd(Scheduler *_scheduler ,TaskFunction _func , void* _context );

/**  
 * @brief run the executor
 * @param[in] *_scheduler - pointer to the scheduler
 *
 * @warning if _scheduler will be null the add will failed     
 *
 */
void SchedulerRun(Scheduler *_scheduler);

#endif /* __SCHEDULER_H__ */
