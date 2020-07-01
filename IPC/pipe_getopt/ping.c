#ifndef _XOPEN_SOURCE
#define _XOPEN_SOURCE 500
#endif

#include <stdlib.h>
#include <stdio.h>
#include <getopt.h>
#include <sys/stat.h> 
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h> 

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
	char m_pipeName[30];
	
}Args;

/* ================= statements local func ============== */

int InItArgs( Args *_args, int _argc, char **_argv );	
void PrintUsage();	
void WriteToPipe(Args *_args , char *_strWrite , int *_countWrite  , int _fd);
void ReadFromPipe(Args *_args , char *_buf , int *_countRead , int _mypipefd[]);	

/* ========================= main ======================= */

int main (int argc , char **argv)
{
	Args args;
	int  countWrite=0  ;
	char strWrite[20] ;
	int resultArgs;
	int fd;
	
     if ( (resultArgs = InItArgs( &args, argc, argv )) != ARGS_OK )	
     {
     	return resultArgs;
     }											

	mkfifo( args.m_pipeName , 0666);
	
	fd = open(args.m_pipeName , O_WRONLY);
	
     WriteToPipe( &args, strWrite, &countWrite , fd);		

	close(fd);	
	printf("Writer write %d of messages\n", countWrite);				

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
void WriteToPipe(Args *_args , char *_strWrite , int *_countWrite , int _fd)
{
	int i;

	for ( i = 0 ; i < _args->m_numberWrite ; i++ )
	{
		++(*_countWrite);
		
		PRINT_WRITE( _args->m_flagVerbose , *_countWrite );
				
		usleep(_args->m_writerWorkTime);
		sprintf(_strWrite, " Message %2d", (*_countWrite) );  
				
		write( _fd , _strWrite , strlen(_strWrite));  
	}
	
	return;
}


