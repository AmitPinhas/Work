#include <stdlib.h>   /* allocation */
#include "t_queue.h"
#include "vector.h"

#define ZERO_BLOCK_SIZE 0

struct TQueue{
	Heap *m_tasks;
};

/* ------------------------------------------------------- local functions ----------------------------------------------------------------------- */
int IsLessTask(const void *_task1, const void *_task2);

/*=================================================================================================================================================*/
/*============================================================== API ==============================================================================*/
/*=================================================================================================================================================*/

/* -------------------------------------------------------- TQueue Create ----------------------------------------------------------------- */
TQueue* TQueueCreate(size_t _numOfTasks)
{
	TQueue *tQueue;
	Vector *vector;
	
	tQueue = (TQueue*)malloc(sizeof(TQueue));
	if ( NULL == tQueue )
	{
		return NULL;
	}
	
	vector = VectorCreate ( _numOfTasks , ZERO_BLOCK_SIZE );
	if ( NULL == vector )
	{
		return NULL;
	}
	
	tQueue->m_tasks = HeapBuild( vector , IsLessTask );	
	if ( NULL == tQueue -> m_tasks )
	{
		free(tQueue);
		VectorDestroy(&vector, NULL);
		return NULL;
	}
	
	return tQueue;
}

/* ------------------------------------------------------- TQueue Destroy ---------------------------------------------------------------- */
void TQueueDestroy(TQueue *_t_queue)
{
	Vector *vector = HeapDestroy(&(_t_queue->m_tasks));
	
     VectorDestroy(&vector, TaskDestroy);
     
     free(_t_queue);
     
     return;	
}

/* ----------------------------------------------------- TQueue Get Size ---------------------------------------------------------------------- */
size_t TQueueGetSize(TQueue *_t_queue)
{
	return HeapSize(_t_queue->m_tasks);
}

/* ------------------------------------------------------- TQueue Pop ------------------------------------------------------------------------- */
Task* TQueuePop(TQueue *_t_queue)
{
	return HeapExtract( _t_queue->m_tasks );
}


/* ------------------------------------------------------ TQueue Push ------------------------------------------------------------------------- */
void TQueuePush(TQueue *_t_queue , Task *_task)
{
	HeapInsert( _t_queue->m_tasks , _task );
	return;
}

/* ---------------------------------------------------- TQueue Get Heap ------------------------------------------------------------------------ */
Heap* TQueueGetHeap(TQueue* _t_queue)
{
	return _t_queue -> m_tasks;
}

/*=================================================================================================================================================*/
/*======================================================== local functions ========================================================================*/
/*=================================================================================================================================================*/

/* ------------------------------------------------------- Comparator ---------------------------------------------------------------------------- */
int IsLessTask(const void *_task1, const void *_task2)
{
	return TaskGetNextTimeRun(((Task*)_task1)) > TaskGetNextTimeRun(((Task*)_task2)) ;
}



