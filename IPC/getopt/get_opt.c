#include <stdlib.h>
#include <stdio.h>
#include <getopt.h>

void PrintUsage()
{
	printf("Usage: temp -c <temp> | temp -f <temp> \n");
	exit(2);
	return;
}


void PrintFarenheit(float _temp)
{
	float f = ((_temp * 9 ) / 5 ) + 32 ;
	printf("%.2f centrigrade is %.2f fraenheit\n" , _temp , f );
	return;
}

void PrintCentrigrade(float _temp)
{
	float f = ((_temp - 32 ) * 5 ) / 9 ;
	printf("%.2f fraenheit is %.2f centrigrade\n" ,  _temp , f );
	return;
}

int main (int argc , char **argv)
{
	int option;
	int cflag = 0 ;
	int fflag = 0 ;
	if ( argc < 2 )
	{
		PrintUsage();
	}

	
	while ((option = getopt(argc , argv , "c:f:")) != -1)
	{
		switch (option)
		{
			case 'c' :
					if (cflag)
					{
						PrintUsage();
					}
					else
					{
						cflag++;
						fflag++;
					}
				     PrintFarenheit(atof(optarg));
					break;
			case 'f' :
					if (fflag)
					{
						PrintUsage();
					}
					else
					{
						cflag++;
						fflag++;
					}			
					PrintCentrigrade(atof(optarg));
					break;	
			default :
					printf("Error");
					break;						
		}
	}
	
	return 0;
}
