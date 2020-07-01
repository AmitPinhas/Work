#ifndef __TIME_M_H__
#define __TIME_M_H__

/**  
 * @brief get task and wait until it will be ready for run
 * @param[in] _task - pointer to task
 * @param[in] _startTime - start time of the executor
 *
 */
void TimeWait(int _nextTimeRun );

void TimeSetStart();

int TimeUpdateRun(int _period);

#endif /* __TIME_M_H__ */
