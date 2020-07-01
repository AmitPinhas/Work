#include <stdio.h>   /* printf */
#include <pthread.h> /* thread */

#define NUM_OF_THREADS 7

void* PrintFunc(void* tid)
{
	printf("%d \n" , *(int*)tid );
	pthread_exit(tid);
	return tid;
}


int main()
{
	pthread_t threads[NUM_OF_THREADS];
	int i , status;
	
	for ( i = 0 ; i < NUM_OF_THREADS ; i++)
	{
		printf("thread num %d: " , i+1);
		status = pthread_create(&threads[i] , NULL , PrintFunc , &i );
		if ( status)
		{
		    printf ("%d" , status);
		}
	}

	for ( i = 0 ; i < NUM_OF_THREADS ; i++)
	{	
	  pthread_join(threads[i] , NULL); 
	}
	
	return 1;
}
