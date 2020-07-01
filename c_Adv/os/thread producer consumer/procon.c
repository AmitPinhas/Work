#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

typedef struct{
	int m_num;
	int m_fWrite;
	int m_fRead;
}Task;

pthread_t threads[3];
Task task;
pthread_mutex_t lockRead;
pthread_mutex_t lockWrite;

void* Producer(void *_task);
void* Consumer(void *_task);

int main()
{
	task.m_num = 0;
	task.m_fWrite =1;
	task.m_fRead =1;
	
	pthread_mutex_init(&lockRead , NULL);
	pthread_mutex_init(&lockWrite , NULL);
		
	pthread_create( &threads[0] , NULL , Producer , &task);			
	pthread_create( &threads[1] , NULL , Consumer , &task);	
	pthread_create( &threads[2] , NULL , Consumer , &task);
	
	pthread_join(threads[0] , NULL);
	pthread_join(threads[1] , NULL);	
	pthread_join(threads[2] , NULL);
	
	return 0 ;
}	

void* Producer(void *_task)
{
	static int num = 1;
	int i;
	for ( i=0 ; i<100 ; i++)
	{
		sleep(1);
		pthread_mutex_lock(&lockWrite);
		if ( ((Task*)_task)->m_fWrite )
		{
			((Task*)_task)->m_fWrite = 0 ;
		      pthread_mutex_unlock(&lockWrite);
		      printf("Producer ");
			((Task*)_task)->m_num = num++;
		}	
		((Task*)_task)->m_fWrite = 1 ;
		((Task*)_task)->m_fRead = 1 ;	
	}	
	pthread_exit(0);
}	

void* Consumer(void *_task)
{
	int i;
	for ( i=0 ; i<100 ; i++)
	{
		sleep(1);	
		pthread_mutex_lock(&lockRead);
		if ( ((Task*)_task)->m_fRead )
		{
			((Task*)_task)->m_fRead = 0 ;
		      printf("Consumer ");		     
			printf("%d\n" , ((Task*)_task)->m_num);
		}
	     pthread_mutex_unlock(&lockRead);
		((Task*)_task)->m_fWrite = 1 ;	
     	((Task*)_task)->m_fRead = 1 ;
	}	

	pthread_exit(0);
}
