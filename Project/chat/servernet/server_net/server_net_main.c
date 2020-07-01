#ifndef _XOPEN_SOURCE
#define _XOPEN_SOURCE 500
#endif

#include <stdio.h>            /* printf , NULL */ 
#include <string.h>           /* strlen */   
#include <stdlib.h>
#include <unistd.h>  
#include <errno.h>   
#include <signal.h>
#include "server_net.h"       /* API server net */

#define SIZE_MSG 100

int NewMsg(void *_server, int _socketClient, char *_msg, int _sizeMsg) ;
void sigint_handler(int _sig ); 

Server *server ;
struct sigaction old;

int main()
{
	ServerArgs args ;
	struct sigaction sa;

	sa.sa_handler = sigint_handler;
	sa.sa_flags = 0 ;
	sigemptyset(&sa.sa_mask);

	if (sigaction(SIGINT, &sa, &old) == -1)
	{
		perror("sigaction");
		exit(1);
	} 
    
	args.m_portNum =         2300 ;
	args.m_sizeListenQueue = 1000 ;
	args.m_maxCLients =      1000 ;
	args.m_funcNewClient =   NULL ;
	args.m_funcClientLeft =  NULL ;
	args.m_funcError =       NULL ;
	args.m_funcNewMsg =      NewMsg ;
	
	server = ServerCreate( &args ) ;
	if ( NULL == server )
	{
	        printf("create server failed\n");
	        return 1;
	}
	
	ServerRun( server ) ;
	
	return 0 ;
}


int NewMsg(void *_server, int _socketClient, char *_msg, int _sizeMsg) 
{
     char msg[SIZE_MSG] ;
     
	printf("%s\n" ,  _msg);  
	   
     sprintf ( msg , "Thank you %d", _socketClient-1 );     
     
	SendMessage((Server*)_server, _socketClient, msg, _sizeMsg );
	return 0 ;
}

void sigint_handler(int _sig )
{
	write(0, "Destroy server\n", 15); 
	ServerDestroy(&server) ;
	if (sigaction(SIGINT, &old, NULL) == -1)
	{
		perror("sigaction");
		exit(1);
	} 	
}

