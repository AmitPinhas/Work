#include <stdio.h> /* printf */
#include <time.h>
#include "UI.h"
#include "t_queue.h"
#include "heap.h"

/*==============================================================================================================================================*/
/*============================================================== API ===========================================================================*/
/*==============================================================================================================================================*/

/* -------------------------------------------------------- UI Print Task --------------------------------------------------------------------- */
int UIPrintTask(const void* _task , void* _context)
{
	int period;
	void* context;
	int id;
	
	id = TaskGetId((Task*)_task);	
	
	switch(id)
	{
		case 1: 
					printf("\nTask A, ");
					break;
		case 2:
					printf("\nTask B, ");
					break;		
		case 3:
					printf("\nTask C, ");
					break;				
		default:
				break;
	}
	
	period = TaskGetPeriod((Task*)_task);
	
	printf("execute every %d sec " , period);
	
	context = TaskGetContext((Task*)_task );
	
	printf("for a total of %d times\n\n" , *((int*)context) );
	
	return 1;	
}

/* ------------------------------------------------------- UI Print Time --------------------------------------------------------------------- */
void UIPrintTime(int _time)
{
	printf("Time %d: ", _time);
}

/* ---------------------------------------------------- UI Print Task Run ------------------------------------------------------------------- */
void UIPrintTaskRun(Task* _task)
{
	int id;
	
	id = TaskGetId(_task);
	
	switch(id)
	{
		case 1: 
					printf("execute task A \n");
					break;
		case 2:
					printf("execute task B \n");
					break;		
		case 3:
					printf("execute task C \n");
					break;				
		default:
				break;
	}	
}

/* -------------------------------------------------- UI Get Period ------------------------------------------------------------------------ */
int UIGetPeriod(Task* _task)
{
	int period;
	
	printf("Please enter the period (in sec) for task number %d --> " , TaskGetId(_task) );
	scanf("%d" , &period);
	
	return period;
}

/* ------------------------------------------------- UI Print Tasks ------------------------------------------------------------------------ */
void UIPrintTasks(TQueue* _tQueue)
{
	Heap *heap;
	
	heap = TQueueGetHeap(_tQueue);
	
	HeapForEach( heap,  UIPrintTask , NULL);
	
	return;
}

/* ------------------------------------------------- UIGetContext --------------------------------------------------------------------------- */
void UIGetContext(Task* _task , int *_context)
{		
	printf("Please enter the total time execute for task number %d --> " , TaskGetId(_task) );
	scanf("%d" , _context);
}
