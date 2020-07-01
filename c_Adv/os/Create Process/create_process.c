#include <stdio.h> /* printf */
#include <stdlib.h>

int g_var = 0 ;

int main()
{
	int l_var = 0 ;
	int n , i ;
	
	n = fork();
	
	if ( n<0)
	{
		/* Error code handling */
		return 1;
	}
	else if ( n>0)
	{
	/* Parent code */
				exit(1);
		for ( i = 0 ; i <30 ; i++ )
		{
			printf("Parentg_var %d \n" , g_var++);
			printf("Parentl_var %d \n" , l_var++);	
			sleep(1);
		}
	}
	else
	{
	/* Child code */
		for ( i = 0 ; i  ; i++ )
		{
			printf("Childg_var %d \n" , g_var--);
			printf("Childl_var %d \n" , l_var--);						
		}
	}
	printf("im done %d\n" , n);
	return 1;
}
