#include <stdio.h>			/* NULL */
#include "ServerManager.h"

int main()
{
	ServerManager* newServer = NULL;
	
	newServer = ServerManagerCreate();
	
	ServerMangementRun(newServer);
	
	return 0;
}
