#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

#define READ_PIPE   (mypipefd[0])
#define WRITE_PIPE  (mypipefd[1])

int main(int argc , char *argv[])
{
	pid_t pid;
	int mypipefd[2];
	char buf[20];
	char str[]="Hello";
	int countWrite=0 , countRead=0 ;

	if (  pipe(mypipefd) == -1 )
	{
		perror("pipe");
		exit(1);
	}
	
	pid = fork();
	
	if ( pid == 0 )
	{
		printf("Child Process\n");
		close(READ_PIPE);
		write(WRITE_PIPE , str , sizeof(str));  
		close(WRITE_PIPE);					
	}
	else
	{
		printf("Parent Process\n");	
		close(WRITE_PIPE);			
		read(READ_PIPE , buf , sizeof(buf));
		close(READ_PIPE);  
		printf ( "buf: %s\n" , buf);		
	}
	
	return 0 ;
}

