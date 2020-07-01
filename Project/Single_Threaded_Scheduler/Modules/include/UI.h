#ifndef __UI_H__
#define __UI_H__

#include "task.h"
#include "executor.h"


/*===============================================================================================================================================*/
/*============================================================== API ============================================================================*/
/*===============================================================================================================================================*/

/**  
 * @brief print task
 * @param[in] _task - pointer to task 
 * @param[in] _context - void pointer  
 *
 */
int UIPrintTask(const void* _task , void* _context );

/**  
 * @brief print time
 * @param[in] _time - int time
 *
 */
void UIPrintTime(int _time);

/**  
 * @brief print the task that run
 * @param[in] _task - pointer to task 
 *
 */
void UIPrintTaskRun(Task* _task);


/**  
 * @brief get from user period
 * @return int - the period that the user enter 
 *
 */
int UIGetPeriod(Task* _task);

/**  
 * @brief print all the tasks in the T_queue
 * @param[in] T_queue - pointer to T_queue
 *
 */
void UIPrintTasks(TQueue* _tQueue);

/**  
 * @brief get from user the context
 * @param[in] _task - pointer to task 
 * @param[in] _context - pointer to int 
 */
void UIGetContext(Task* _task , int *_context);

#endif /* __UI_H__ */
