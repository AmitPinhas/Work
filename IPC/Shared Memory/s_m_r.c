#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <stdio.h>
#include <string.h>

int main()
{
	int retval, shmid ;
	void *memory = NULL ;
	char *p ;
	
	shmid = shmget ((key_t)123456789,6, IPC_CREAT|0666);
	
	if ( shmid < 0 )
	{
		printf("\n error shmget");
	}
	
	printf("\n getting the shared %d", shmid);
	
	memory =shmat(shmid, NULL, 0);
	
	if ( NULL == memory )
	{
		printf("\n error shmat");
		return 0;
	}
	
	p =(char*)memory ;
	
	printf("\n MESSAGE is %s \n" , p );
	
	retval = shmdt(p);
	
	if ( retval < 0 )
	{
		printf("error shmdt\n");
		return 0;
	}
	
	retval = shmctl(shmid, IPC_RMID, NULL);
	
	return 0;
}

