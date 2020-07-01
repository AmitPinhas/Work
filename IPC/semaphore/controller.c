#ifndef _XOPEN_SOURCE
#define _XOPEN_SOURCE 500
#endif

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

/* =================== define ======================= */

#define OK           1993
#define FLAG_FTOK    'B'
#define FILE_NAME    "."
#define FLAG_SEM_GET 0666
#define OFF          0
#define ON           1

/* =================== struct ======================= */ 

/* ------ Args ------*/								  			
typedef struct{
	int m_pause ;
	int m_resume ;
	int m_destroy ;
	int m_semId ;
	
}Args;

/* ----- Semun ----- */
typedef union {
    int val;
    struct semid_ds *buf;
    unsigned short *array;
}Semun;

/* =============== local func ========================= */

/* ---------------- Print Usage ------------------- */
void PrintUsage()
{
	fprintf( stderr ,"Usage: ./controller -p(pause) -r(resume) -d(destroy) \n");
	return;
}


/* --------------- InitDefault ---------------- */
void InitDefault( Args *_args ) 
{
	_args -> m_pause = OFF ;
	_args -> m_resume = OFF ; 
	_args -> m_destroy = OFF ;
	
	return;	
}


/* ---------------- Init Args -------------------- */
int InitArgs( Args *_args, int _argc, char **_argv )
{
	int option;

     InitDefault( _args ) ;
	
	while ((option = getopt( _argc , _argv , "prd")) != -1)
	{
		switch (option)
		{
			case 'p' :
				     _args -> m_pause = ON ;
					break;	
			case 'r' :			
					_args -> m_resume = ON ;
				    	break;
			case 'd' :			
					_args -> m_destroy = ON ;
				    	break;				    						    		
			default :
					PrintUsage();
					return errno;						
		}
	}
	
	return OK;
}


/* -------------- GetSema ------------- */
int GetSema( Args *_args )
{
    key_t key;
    
    if ((key = ftok( FILE_NAME , FLAG_FTOK )) == -1)
    {
        perror("ftok");
        return errno;
    }

    if ((_args -> m_semId = semget(key, 1 , FLAG_SEM_GET )) == -1)
    {
        perror("msgget");
        return errno;
    }   

    return OK ;	
}

/* ------------- Pause ----------- */
int Pause( Args *_args )
{
	struct sembuf sb;
	
	sb.sem_num = 0 ;
	sb.sem_flg = 0 ;
	sb.sem_op = -1 ;	
	
	if ( _args -> m_pause )
	{    
     	if ( semop(_args->m_semId, &sb, 1) == -1 )
		{
     		perror("semop");
	 		return errno;
		}
	}
	
	return OK ;
}


/* ------------- Resume ----------- */
int Resume( Args *_args )
{
	struct sembuf sb;
	
	sb.sem_num = 0 ;
	sb.sem_flg = 0 ;
	sb.sem_op =  1 ;	
	
	if ( _args -> m_resume )
	{
     	if ( semop(_args->m_semId, &sb, 1) == -1 )
		{
     		perror("semop");
	 		return errno;
		}	
	}
	
	return OK ;
}


/* ---------- DestroySema ---------- */
int DestroySema( Args *_args )
{
    Semun arg ;

    if ( _args -> m_destroy )
    {	
	    if (semctl(_args->m_semId, 1, IPC_RMID, arg) == -1)
  	    {
     	   perror("semctl");
     	   return errno ;
         }		
    }
	return OK ;	
}


/* ==================== main ======================== */

int main (int argc , char **argv)
{	
	Args args;
	int  res;
	
	if ((res = InitArgs( &args, argc, argv )) != OK )
	{
		return res ;
	} 
	
	if ( (res = GetSema( &args )) != OK )
	{
		return res ;
	}
		
	if((res = Pause( &args )) != OK )
	{
		return res;
	}

	if((res = Resume( &args )) != OK )
	{
		return res;
	}
	
	if ((res = DestroySema( &args )) != OK )
	{
		return res;
	}
	
	return 0 ;
}
