#ifndef _XOPEN_SOURCE
#define _XOPEN_SOURCE 500
#endif

#include <stdlib.h>
#include <stdio.h>
#include <getopt.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>
#include "pingpong.h"

/* ================== define ======================= */

#define ARGS_OK 35533453
#define ON 1
#define OFF 0
#define SIZE_FILE_NAME 5
#define OK 1993

/* =================== macro ======================== */

#define MILI_SEC(T) ( (T) * 1000 )
#define PRINT_READ( Flag , CountRead  , Buf )  				   \
	{ 	if ( Flag ) 				  					   \
		{                       						        \
		   printf("Pong message #%d='%s'\n" , CountRead, Buf);	   \
		}						  					   \
	}												   	  

/* =================== struct ======================= */ 

/* ------ Args ------*/								  			
typedef struct{
	int  m_Verbose ;
	char *m_fileName ;
	int  m_workSimulation ;
}Args;


/* ============= statements local func ============== */

void PrintUsage();
int InitArgs( Args *_args, int _argc, char **_argv );
void InitDefault( Args *_args ) ;
int GetMsgQueue( Args *_args , int *_msqpid ) ;
int ReadFromMsgQ(Args *_args , int _msqid );


/* ==================== main ======================== */

int main (int argc , char **argv)
{	
	Args args;
	int msqid, res ;
	
	if ((res = InitArgs( &args, argc, argv )) != ARGS_OK )
	{
		return res ;
	} 
	
	if ( (res = GetMsgQueue( &args, &msqid )) != OK )
	{
		return res ;
	}
	
	if((res = ReadFromMsgQ( &args , msqid )) != OK )
	{
		return res;
	}
	
	return 0 ;
}


/* ========================= local func ============================== */

/* ---------------- Print Usage ------------------- */
void PrintUsage()
{
	fprintf( stderr ,"Usage: ./pong -v(verbose) -f(filename) -s(work sim) \n");
	return;
}


/* ---------------- Init Args -------------------- */
int InitArgs( Args *_args, int _argc, char **_argv )
{
	int option;

     InitDefault( _args ) ;
	
	while ((option = getopt( _argc , _argv , "vf:s:")) != -1)
	{
		switch (option)
		{
			case 'v' :
				     _args -> m_Verbose = ON ;
					break;
			case 'f' :
				     _args -> m_fileName = optarg ;
					break;	
			case 's' :			
					_args -> m_workSimulation = MILI_SEC( atoi(optarg) ) ;
				    	break;					    		
			default :
					PrintUsage();
					return errno;						
		}
	}
	
	return ARGS_OK;
}


/* --------------- InitDefault ---------------- */
void InitDefault( Args *_args ) 
{
	_args -> m_Verbose = OFF ;
	_args -> m_fileName = "." ;
	_args -> m_workSimulation = MILI_SEC ( 500 ) ;
	
	return;	
}


/* -------------- GetMsgQueue ------------- */
int GetMsgQueue( Args *_args , int *_msqpid )
{
    key_t key;
    
    
    if ((key = ftok( _args->m_fileName , FLAG_FTOK )) == -1)
    {
        perror("ftok");
        return errno;
    }

    if ((*_msqpid = msgget(key, FLAG_MSG_GET )) == -1)
    {
        perror("msgget");
        return errno;
    }    
    
    return OK ;	
}


/* -------------- ReadFromMsgQ --------------- */
int ReadFromMsgQ(Args *_args , int _msqid )
{
	MyMsgbuf buf;
	int i=0, len ;

	while ( 1 )
	{

        if (msgrcv(_msqid, &buf , sizeof buf.mtext, -PING_TYPE , 0) == -1) 
        {
            perror("msgrcv");
            return OK;
        }   
        
	   usleep(_args->m_workSimulation);    

        PRINT_READ( _args -> m_Verbose  , ++i  , buf.mtext );
	   
	   if ( buf.mtype == EOF_TYPE || (strcmp(buf.mtext , EOF_MSG)) == 0 )
	   {   
	   	break ;
	   }
        	   
	   buf.mtype = PONG_TYPE ;
	   len = strlen(buf.mtext);
	    
	   if (msgsnd(_msqid, &buf, len+1, 0) == -1)
        { 
         	 perror("msgsnd");
         	 return errno;		
	   }	 

	}
 	
 	return OK;
}


