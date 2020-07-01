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
#define PRINT_WRITE( Flag , CountWrite )  					   \
	{ 	if ( (Flag) ) 				  					   \
		{                       						        \
		   printf("Ping Writer #%d message\n" , (CountWrite));    \
		}						  					   \
	}							  					   \

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
	int  m_numberMsg ;
	int  m_flagEOF ;
	int  m_workSimulation ;
	int  m_isCreate ;
	int  m_isDelete ;
	
}Args;

/* ============= statements local func ============== */

void PrintUsage();
int InitArgs( Args *_args, int _argc, char **_argv );
void InitDefault( Args *_args ) ;
int CreateMsgQueue( Args *_args , int *_msqpid ) ;
int WriteToMsgQ(Args *_args , int _msqid );
int DeleteMsgQ(Args *_args , int _msqid ); 

/* ==================== main ======================== */

int main (int argc , char **argv)
{	
	Args args;
	int msqid, res;
	
	if ((res = InitArgs( &args, argc, argv )) != ARGS_OK )
	{
		return res ;
	} 
	
	if ( (res = CreateMsgQueue( &args, &msqid )) != OK )
	{
		return res ;
	}
	
	if((res = WriteToMsgQ( &args , msqid )) != OK )
	{
		return res;
	}
	
	if ((res = DeleteMsgQ( &args , msqid )) != OK )
	{
		return res;
	}
	
	return 0 ;
}


/* ========================= local func ============================== */

/* ---------------- Print Usage ------------------- */
void PrintUsage()
{
	fprintf( stderr ,"Usage: ./ping -v(verbose) -c(create) -d(delete) -f(filename) -n(number of msg) -e(eof) -s(work sim) \n");
	return;
}


/* ---------------- Init Args -------------------- */
int InitArgs( Args *_args, int _argc, char **_argv )
{
	int option;

     InitDefault( _args ) ;
	
	while ((option = getopt( _argc , _argv , "vcdf:n:es:")) != -1)
	{
		switch (option)
		{
			case 'v' :
				     _args -> m_Verbose = ON ;
					break;
			case 'c' :			
					_args -> m_isCreate = ON ;
					break;
			case 'd' :
				     _args -> m_isDelete = ON ;
					break;
			case 'f' :
					free ( _args -> m_fileName ) ;		
					_args -> m_fileName = (char*)malloc( strlen(optarg) + 1 );
				     strcpy( _args -> m_fileName , optarg );
					break;
			case 'n' :
				     _args -> m_numberMsg = atoi(optarg) ;
					break;
			case 'e' :			
					_args -> m_flagEOF = ON ;
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
	_args -> m_isCreate = OFF ;
	_args -> m_isDelete = OFF ;
	_args -> m_fileName = (char*)malloc( SIZE_FILE_NAME );
	strcpy( _args -> m_fileName , "." );
	_args -> m_numberMsg = 0 ;
	_args -> m_flagEOF = OFF ;
	_args -> m_workSimulation = MILI_SEC ( 500 ) ;
	
	return;	
}


/* -------------- CreateMsgQueue ------------- */
int CreateMsgQueue( Args *_args , int *_msqpid )
{
    key_t key;
    
    if ( _args -> m_isCreate == ON )
    {
    
    if ((key = ftok( _args->m_fileName , FLAG_FTOK )) == -1)
    {
        perror("ftok");
        return errno;
    }

    if ((*_msqpid = msgget(key, FLAG_MSG_GET | IPC_CREAT )) == -1)
    {
        perror("msgget");
        return errno;
    }    
    
    }
    return OK ;	
}


/* -------------- WriteToMsgQ --------------- */
int WriteToMsgQ(Args *_args , int _msqid )
{
	MyMsgbuf buf;
	int i , len  , countRcv=0 ;
	
	printf("Enter %d lines of text\n" , _args -> m_numberMsg );
	
	for ( i = 0 ; i < _args -> m_numberMsg ; i++ )
	{
		buf.mtype = PING_TYPE ;
		fgets(buf.mtext, sizeof buf.mtext, stdin) ;
		len = strlen(buf.mtext);
		PRINT_WRITE( _args -> m_Verbose , i+1 );
		if ( buf.mtext[len-1] == '\n' )
		{
			buf.mtext[len-1] = '\0';	
		} 
		
		usleep(_args->m_workSimulation);
		
          if (msgsnd(_msqid, &buf, len, 0) == -1)
          { 
            	perror("msgsnd");
            	return errno;		
	     }	
	     
        if ( _args -> m_numberMsg == countRcv )
        {
        	break;
        }
        
        if (msgrcv(_msqid, &buf , sizeof buf.mtext, PONG_TYPE, 0) == -1) 
        {
            perror("msgrcv");
            return OK;
        } 
        else
        {
        	  PRINT_READ( _args -> m_Verbose , i+1 , buf.mtext );
        	  countRcv++ ;
        } 	     
	      
	}
	
	if ( _args -> m_flagEOF )
	{
		buf.mtype = EOF_TYPE ;
		strcpy(buf.mtext , EOF_MSG );		
	}
	else
	{
		buf.mtype = PING_TYPE ;
		strcpy(buf.mtext , EOF_MSG);
	}

     if (msgsnd(_msqid, &buf, len+1, 0) == -1)
     { 
        	perror("msgsnd");
         	return errno;		
     }	
     
 /*    while (1)
     {
        if ( _args -> m_numberMsg == countRcv )
        {
        	break;
        }
        
        if (msgrcv(_msqid, &buf , sizeof buf.mtext, PONG_TYPE, 0) == -1) 
        {
            perror("msgrcv");
            return OK;
        } 
        else
        {
        	  PRINT_READ( _args -> m_Verbose , 0 , buf.mtext );
        	  countRcv++ ;
        }      	
     }
 	*/
 	return OK;
}


/* --------------- DeleteMsgQ ---------------- */
int DeleteMsgQ(Args *_args , int _msqid )
{
	if ( _args -> m_isDelete == ON )
	{
   		 if (msgctl(_msqid, IPC_RMID, NULL) == -1)
   		 {
    		    perror("msgctl");
    		    return errno;
           }		
	}
	
	return OK;
}




