#include <stdio.h>
#include "../include/log.h"

void LogWrite(char *_file , int _line ,const char *_func , char *_txt , MsgType _msgType)
{
	FILE *f;
	f = fopen("log.txt" , "a");
	fprintf( f , "%s\n", _txt );
	
	switch(_msgType)
	{
		case OK: 		
			   		break;
		case ERROR:    
		               break;                
		default:
				     break;
	}
	
	fclose(f);
	return;
}
