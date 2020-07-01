#include <stdlib.h>    /* allocation */
#include "scheduler.h"
#include "t_queue.h"
#include "executor.h"
#include "UI.h"


struct Scheduler{
	TQueue *m_tasks;
};



/*================================================================================================================================================*/
/*============================================================== API =============================================================================*/
/*================================================================================================================================================*/

/* ----------------------------------------------------- Scheduler Create ----------------------------------------------------------------------- */
Scheduler* SchedulerCreate(size_t _numOfTasks)
{
	Scheduler *scheduler;
	
	if ( 0 > _numOfTasks )
	{
		return NULL;
	}
	
	scheduler = (Scheduler*) malloc(sizeof(Scheduler));	
	if ( NULL == scheduler )
	{
		return NULL;
	}
	
	scheduler->m_tasks = TQueueCreate(_numOfTasks);
	if ( NULL == scheduler->m_tasks )
	{
		free(scheduler);
		return NULL;
	}
	
	return scheduler;
}


/* ---------------------------------------------------- Scheduler Destroy ----------------------------------------------------------------------- */
void SchedulerDestroy(Scheduler **_scheduler)
{
	if ( NULL == _scheduler || NULL == *_scheduler )
	{
		return;
	}
	
	TQueueDestroy( (*_scheduler)->m_tasks );
	
	free(*_scheduler);
	
	*_scheduler = NULL ;
	
	return;
}

/* ----------------------------------------------------- Scheduler Add -------------------------------------------------------------------------- */
void SchedulerAdd(Scheduler *_scheduler ,TaskFunction _func , void* _context )
{
	Task *task;
	
	if ( NULL == _scheduler )
	{
		return ;
	}
	
	task = TaskCreate( _func , _context );
	if ( NULL == task )
	{
		return;
	}
		
	TQueuePush( _scheduler->m_tasks , task );

	return ;	
}


/* ---------------------------------------------------- Scheduler Run -------------------------------------------------------------------------- */
void SchedulerRun(Scheduler *_scheduler)
{
	Executor *executor;
	
	if ( NULL == _scheduler )
	{
		return;
	}
	
	executor = ExecutorCreate( _scheduler->m_tasks );

	UIPrintTasks(_scheduler->m_tasks);		
		
	ExecutorRun(executor);
	
	ExecutorDestroy(executor);
	
	return ;
}

