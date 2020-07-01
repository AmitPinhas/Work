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

#define DEF_LINES    10
#define DEF_DELAY    500
#define OK           1993
#define FLAG_FTOK    'B'
#define FILE_NAME    "."
#define FLAG_SEM_GET 0666

/* =================== macro ======================== */

#define MICRO_TO_MILI(T) ( (T) * 1000 )

/* =================== struct ======================= */ 

/* ------ Args ------*/								  			
typedef struct{
	int m_lines ;
	int m_delay ;
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
	fprintf( stderr ,"Usage: ./printer -n(lines) -s(delay) \n");
	return;
}


/* --------------- InitDefault ---------------- */
void InitDefault( Args *_args ) 
{
	_args -> m_lines = DEF_LINES ;
	_args -> m_delay = MICRO_TO_MILI(DEF_DELAY); 
	
	return;	
}


/* ---------------- Init Args -------------------- */
int InitArgs( Args *_args, int _argc, char **_argv )
{
	int option;

     InitDefault( _args ) ;
	
	while ((option = getopt( _argc , _argv , "n:s:")) != -1)
	{
		switch (option)
		{
			case 'n' :
				     _args -> m_lines = atoi(optarg) ;
					break;	
			case 's' :			
					_args -> m_delay = MICRO_TO_MILI( atoi(optarg) ) ;
				    	break;					    		
			default :
					PrintUsage();
					return errno;						
		}
	}
	
	return OK;
}

/* -------------- CreateSema ------------- */
int CreateSema( Args *_args )
{
    key_t key;
    Semun sb ;
    
    if ((key = ftok( FILE_NAME , FLAG_FTOK )) == -1)
    {
        perror("ftok");
        return errno;
    }

    if ((_args -> m_semId = semget(key, 1 , FLAG_SEM_GET | IPC_CREAT )) == -1)
    {
        perror("msgget");
        return errno;
    }   
    
    sb.val = 1 ;
    
    if ( semctl( _args -> m_semId , 0, SETVAL , sb ) == -1 )
    {
        perror("semctl");
        return errno;    	
    }

    return OK ;	
}

/* ------------- SemDown -------------- */
int SemDown( Args *_args )
{
	struct sembuf sb;
	
	sb.sem_num = 0 ;
	sb.sem_flg = 0 ;
	sb.sem_op = -1 ;	
	     
	if ( semop(_args->m_semId, &sb, 1) == -1 )
     {
	 	perror("semop");
	 	return errno;
     }
     	
	return OK ;	
}

/* ------------- SemUp -------------- */
int SemUp( Args *_args )
{
	struct sembuf sb;
	
	sb.sem_num = 0 ;
	sb.sem_flg = 0 ;
	sb.sem_op = 1 ;	
	     
	if ( semop(_args->m_semId, &sb, 1) == -1 )
     {
	 	perror("semop");
	 	return errno;
     }
     	
	return OK ;	
}


/* ------- PrintLines ------- */
int PrintLines( Args *_args )
{
	int i , res ;
	
	for ( i = 0 ; i < _args -> m_lines ; ++i )
	{
		usleep( _args -> m_delay ) ;

          if ( (res = SemDown( _args ) ) != OK )
          {
           	return res ;
          }	
	      
		printf("Iteration #%d !!!\n" , i+1 );
		
          if ( (res = SemUp( _args ) ) != OK )
          {
           	return res ;
          }	

	}
	
	return OK ;
}



/* -------- DeleteSema ------------ */
int DeleteSema(Args *_args)
{
    Semun arg ;	
		
    if (semctl(_args->m_semId, 1, IPC_RMID, arg) == -1)
    {
        perror("semctl");
        return errno ;
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
	
	if ( (res = CreateSema( &args )) != OK )
	{
		return res ;
	}
	
	if((res = PrintLines( &args )) != OK )
	{
		return res;
	}
	
	if ((res = DeleteSema( &args )) != OK )
	{
		return res;
	} 
	
	return 0 ;
}



