#ifndef _XOPEN_SOURCE
#define _XOPEN_SOURCE 500
#endif

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>

void sigint_handler_parent(int sig);
void sigint_handler_child(int sig);

int main(int argc , char* argv[])
{
    pid_t pid;
    struct sigaction sa;

    sa.sa_handler = sigint_handler_child;
    sa.sa_flags = 0;  
    sigemptyset(&sa.sa_mask); 
    if (sigaction(SIGUSR1, &sa, NULL) == -1)
    {
    	   perror("sigaction");
        exit(1);
    } 

    sa.sa_handler = sigint_handler_parent;
    sa.sa_flags = 0;  
    sigemptyset(&sa.sa_mask); 
    if (sigaction(SIGUSR2, &sa, NULL) == -1)
    {
    	   perror("sigaction");
        exit(1);
    } 
                   
    pid = fork(); 
    
    if ( -1 == pid )
    {
    	printf("fork error\n");
    	return 1;
    }
    
	if ( pid > 0 )
	{
  	   kill(pid, SIGUSR1) ;
  	   pause();	   
	}
	else
	{ 
  	   pause();              	
	}
	
	return 0;
}

void sigint_handler_parent(int sig)
{
	printf("pong\n");
	return;
}

void sigint_handler_child(int sig)
{
	printf("ping\n");
	kill(getppid() , SIGUSR2); 	
	return;
}

