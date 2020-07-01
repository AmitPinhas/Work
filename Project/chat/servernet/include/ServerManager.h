#ifndef __SERVERMANAGER_H__
#define __SERVERMANAGER_H__

#include "server_net.h"

typedef struct ServerManager ServerManager ;

/*
	Description - make pointer to server manager
	Input		- no input
	Output		- a) pointer to server manager
				  b) null
	Error		- null : allocation failed 	  		
*/
ServerManager* ServerManagerCreate() ;

/*
	Description - run server manager
	Input		- pointer to server manager
	Output		- no output
	Error		- no error 
	Warning		- server manager pointer must be initialized		
*/
void ServerMangementRun(ServerManager *_serverManager);

/*
	Description - destroy server manager
	Input		- pointer to pointer server manager
	Output		- no output
	Error		- no error 
	Warning		- server manager pointer to pointer must be initialized		
	Notice		- for destroy server from the terminal 
				  press on ctrl c , and to exit from the program
				  ctrl c again	
*/
void ServerManagerDestroy(ServerManager **_serverManager);

#endif /* __SERVERMANAGER_H__ */
