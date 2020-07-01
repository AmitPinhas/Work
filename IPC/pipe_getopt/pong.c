#ifndef _XOPEN_SOURCE
#define _XOPEN_SOURCE 500
#endif

#include <stdlib.h>
#include <stdio.h>
#include <getopt.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

/* ================== define ======================= */

#define READ   0
#define WRITE  1
#define ARGS_OK 35533453
#define CHILD_PROCESS 0

/* ================= macro ======================== */

#define MILI_SEC(T) ( (T) * 1000 )
#define PRINT_WRITE( Flag , CountWrite )  					   \
	{ 	if ( Flag ) 				  					   \
		{                       						        \
		   printf("Process Writer #%d message\n" , CountWrite);   \
		}						  					   \
	}							  					   \

#define PRINT_READ( Flag , CountRead  , Buf )  				   \
	{ 	if ( Flag ) 				  					   \
		{                       						        \
		   printf("Read message #%d='%s'\n" , CountRead, Buf);	   \
		}						  					   \
	}							  					   \

/* =================== struct ================= */ 
								  			
typedef struct{
	int m_flagVerbose ;
	int m_numberWrite ;
	int m_writerWorkTime ;
	int m_readerWorkTime ;
	int m_sizeReadBuf ;
	char *m_pipeName[30];
	
}Args;

/* ================= statements local func ============== */

int InItArgs( Args *_args, int _argc, char **_argv );	
void PrintUsage();	
void WriteToPipe(Args *_args , char *_strWrite , int *_countWrite , int _mypipefd[]);
void ReadFromPipe(Args *_args , char *_buf , int *_countRead , int _mypipefd[]);	

/* ========================= main ======================= */

int main (int argc , char **argv)
{
	Args args;
	int  countWrite=0 , countRead=0 ;
	char *buf , strWrite[20] ;
	pid_t pid;
	int mypipefd[2];
	int resultArgs;
	int fd;
	
     if ( (resultArgs = InItArgs( &args, argc, argv )) != ARGS_OK )	
     {
     	return resultArgs;
     }											

	mkfifo(args.m_pipeName , 06666);
	
	

	buf = (char*)malloc( ( args.m_sizeReadBuf + 1));
	if ( NULL == buf )
	{
		fprintf( stderr ,"Error malloc buf\n");
		return 0;
	}
	
	pid = fork();	
	if ( pid == -1 )
	{
		perror("error fork\n");
		return errno;
	}
	
	if ( pid == CHILD_PROCESS )
	{ 
		close(mypipefd[READ]);

          WriteToPipe( &args, strWrite, &countWrite , mypipefd);		

		close(mypipefd[WRITE]);	
	     printf("Writer write %d of messages\n", countWrite);				
	}
	else
	{
		close(mypipefd[WRITE]);
		
          ReadFromPipe( &args, buf, &countRead, mypipefd );					

		close(mypipefd[READ]);
		
		printf("Reader read %d messages\n", countRead);
	}		
	
	free(buf);
	
	return 0;
}



/* ========================== local function ========================== */


/* ------------------------- InItArgs ---------------------- */
int InItArgs( Args *_args, int _argc, char **_argv )
{
	int option;
	
	while ((option = getopt( _argc, _argv, "vn:w:r:s:c:" )) != -1)
	{
		switch (option)
		{
			case 'v' :
					_args->m_flagVerbose = 1;
					break;
			case 'n' :
					_args->m_numberWrite = atoi(optarg);
					break;
			case 'w' :
					_args->m_writerWorkTime = MILI_SEC(atoi(optarg));
					break;
			case 'r' :
					_args->m_readerWorkTime = MILI_SEC(atoi(optarg));
					break;
			case 's' :
					_args->m_sizeReadBuf = atoi(optarg);
					break;
			case 'c' :
					strcpy(_args->m_pipeName , "./" );
					strcat(_args->m_pipeName , optarg);
					break;					
																									
			default :
					PrintUsage();
					return errno; 
		}
	}		
	
	return ARGS_OK;
}

/* ------------------ PrintUsage ------------------- */
void PrintUsage()
{
	fprintf( stderr ,"Usage: ./p_g.out -v(for verbose) -n<num>(number write) -w<num>(write time) -r<num>(read time) -s<num>(size buf) \n");
	return;
}


/* ---------------- WriteToPipe ------------------ */
void WriteToPipe(Args *_args , char *_strWrite , int *_countWrite, int _mypipefd[])
{
	int i;

	for ( i = 0 ; i < _args->m_numberWrite ; i++ )
	{
		++(*_countWrite);
		
		PRINT_WRITE( _args->m_flagVerbose , *_countWrite );
				
		usleep(_args->m_writerWorkTime);
		sprintf(_strWrite, " Message %2d", (*_countWrite) );  
				
		write(_mypipefd[WRITE] , _strWrite , strlen(_strWrite));  
	}
	
	return;
}

/* -------------------------- ReadFromPipe --------------------- */
void ReadFromPipe(Args *_args , char *_buf , int *_countRead , int _mypipefd[])
{
	int nBytes;
	
	while ( (nBytes = read(_mypipefd[READ], _buf, _args->m_sizeReadBuf)) > 0 )
	{
		++(*_countRead);
		_buf[nBytes] = 0;
			
		PRINT_READ( _args->m_flagVerbose , (*_countRead)  , _buf )
	
		usleep(_args->m_readerWorkTime);		
	}	
	
	return;
}

