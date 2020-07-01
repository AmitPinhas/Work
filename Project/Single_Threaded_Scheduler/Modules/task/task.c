#include <stdlib.h> /* allocation */
#include "task.h"
#include "UI.h"
#include "time_m.h"

struct Task{
	TaskFunction m_func;
	void* m_context;
	int m_period;
	int m_nextTimeRun;
	int m_id;
};

/*=================================================================================================================================================*/
/*=========================================================== API =================================================================================*/
/*=================================================================================================================================================*/

/* ------------------------------------------------------ Task Create ---------------------------------------------------------------------------- */
Task* TaskCreate(TaskFunction _func , void* _context )
{
	Task *task;
	static int idTask=1;	
	
	task = (Task*) malloc(sizeof(Task));
	if ( NULL == task )
	{
		return NULL;
	}	

	task->m_id = idTask++;	
	task->m_func = _func;	
	task->m_context = _context;
	task->m_period = UIGetPeriod(task);
	task->m_nextTimeRun = task->m_period;
	
	return task;
}

/* -------------------------------------------------------- Task Destroy ------------------------------------------------------------------------- */
void TaskDestroy(void* _task)
{
	free( ((Task*)_task) );
}

/* ------------------------------------------------ Task Get Next Time Run ---------------------------------------------------------------------- */
int TaskGetNextTimeRun(Task *_task)
{
	return _task -> m_nextTimeRun ;
}

/* ------------------------------------------------- Task Get Context --------------------------------------------------------------------------- */
void* TaskGetContext(Task *_task)
{
	return _task -> m_context ;
}

/* ------------------------------------------------ Task Get Period ----------------------------------------------------------------------------- */
int TaskGetPeriod(Task *_task)
{
	return _task -> m_period ;
}

/* ------------------------------------------------- Task Get Id --------------------------------------------------------------------------------- */
int TaskGetId(Task *_task)
{
	return _task -> m_id;
}

/* -------------------------------------------------- Task Run ----------------------------------------------------------------------------------- */
int TaskRun(Task *_task)
{	
	UIPrintTaskRun(_task);
	(--(*((int*)_task -> m_context))) ;	
	return !(_task->m_func(_task->m_context));
}

/* ------------------------------------------------ Task Update Due Time ----------------------------------------------------------------------- */
void TaskUpdateDueTime(Task *_task)
{
	_task -> m_nextTimeRun = TimeUpdateRun(_task->m_period);
	return;
}


