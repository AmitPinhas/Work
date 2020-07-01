#include <stdlib.h>   /* allocation */ 
#include "executor.h"
#include "task.h"
#include "time_m.h"
#include "UI.h"


struct Executor{
	TQueue *m_tasks;
};


/*================================================================================================================================================*/
/*============================================================== API =============================================================================*/
/*================================================================================================================================================*/

/* ------------------------------------------------------ Executor Create ----------------------------------------------------------------------- */
Executor* ExecutorCreate(TQueue *_tasks)
{
	Executor *executor;
	
	executor =(Executor*) malloc(sizeof(Executor));
	if ( NULL == executor )
	{
		return NULL ;
	}
	
	executor->m_tasks = _tasks;

	return executor;
}

/* ------------------------------------------------------ Executor Destroy ----------------------------------------------------------------------- */
void ExecutorDestroy(Executor *_executor)
{
	free(_executor);
	return;
}

/* -------------------------------------------------------- Executor Run ------------------------------------------------------------------------ */
void ExecutorRun(Executor *_executor)
{
	Task *task;
	int isContinue ;
	
	TimeSetStart();
	
	while ( TQueueGetSize( _executor->m_tasks) )
	{
		task = TQueuePop( _executor->m_tasks ) ;
		TimeWait( TaskGetNextTimeRun(task) );
		if ( (isContinue = TaskRun(task)) )
		{
			TaskUpdateDueTime(task);
			TQueuePush( _executor->m_tasks , task );
		}
		else
		{
			TaskDestroy(task);
		}

	}
	
	return ;
}


