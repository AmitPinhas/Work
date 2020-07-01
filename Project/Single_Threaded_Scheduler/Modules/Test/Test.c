#include <stdio.h>     /* printf */
#include "scheduler.h"

int Func1(void* _context);
int Func2(void* _context);
int Func3(void* _context);

int main()
{
	Scheduler *scheduler;
	int context1=1 , context2=2 , context3=3 ;
	
	scheduler = SchedulerCreate( 3 );
	
	SchedulerAdd( scheduler , Func1 , &context1 );
	SchedulerAdd( scheduler , Func2 , &context2 );
	SchedulerAdd( scheduler , Func3 , &context3 );
	
	SchedulerRun(scheduler);
	
	SchedulerDestroy(&scheduler);
	
	return 0 ;
}

int Func1(void* _context)
{
	if ( *((int*)_context) > 0 )
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

int Func2(void* _context)
{
	
	if ( *((int*)_context) > 0 )
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

int Func3(void* _context)
{
	if ( *((int*)_context) > 0 )
	{
		return 0;
	}
	else
	{
		return 1;
	}
}
