#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <stdio.h>
#include <string.h>

#define OK 1993

typedef struct{
	int m_shmid ;
	void *m_memory ;
}Args;

int CreateShm (Args *_args)
{	
	_args -> m_shmid = shmget( (key_t)123456789, 6, IPC_CREAT|0666);
	if ( _args -> m_shmid < 0 )
	{
		printf("\n The Creation has gone as a failure, Sorry");
		_args -> m_shmid = shmget((key_t)123456789, 6, 0666);
	}
	
	printf("\n We are getting the shared memory created %d" , _args -> m_shmid);
	
	_args -> m_memory = shmat(_args -> m_shmid, NULL, 0);
	
	return OK;
}

int main()
{
	int retval , res ;
	char *p  ;
	Args args;
	
	if ( ( res = CreateShm( &args ) ) != OK )
	{
		return res ;
	}
	
	p = (char*)args.m_memory ;
	
	memset (p, '\0', 6);
	memcpy (p, "hello", 6);
	
	retval = shmdt (p);
	if ( retval < 0 )
	{
		printf("\n Shuffered Detachment");
		return 0;
	}
	
	return 0;
}
