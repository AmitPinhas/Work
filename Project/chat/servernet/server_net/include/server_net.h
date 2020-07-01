#ifndef __SERVER_NET_H__
#define __SERVER_NET_H__

typedef enum{
	FCNTL_ERROR ,
	SELECT_ERROR ,
	ACCEPT_ERROR ,
	RECV_ERROR ,
	SEND_ERROR ,
	SERVER_FULL
}ServerError;

typedef struct Server Server ;

typedef int (*NewClient)(int _socketClient)  ;
typedef int (*ClientLeft)(int _socketClient, void* _context) ;
typedef int (*ErrorFunc)(ServerError _error) ;
typedef int (*NewMessage)(void *_server, int _socketClient, char *_msg, int _sizeMsg) ;

typedef struct{
	int           m_portNum ;
	int           m_sizeListenQueue ;
	int           m_maxCLients ;
	NewClient     m_funcNewClient ;
	ClientLeft    m_funcClientLeft ;
	ErrorFunc     m_funcError ;
	NewMessage    m_funcNewMsg ;
	void* 		m_context;
}ServerArgs ;


/* ====================================== API ========================================== */

/*
	Description - make pointer to the server 

	Input       - a) pointer to server args 

	Output      - a) pointer to the server 
		      b) null 

	Error       - a) pointer to the server - create succeeded 
                      b) null - create failed ,
                                allocation failed
                                or illegal server port number
				or illegal size listen queue

	Warning     - a) port number must be big then 1024 and small then 64K
		      b) size listen queue most be big then zero
*/
Server* ServerCreate(ServerArgs *_serverArgs) ;


/*
	Description - destroy the server 

	Input       - a) pointer to pointer to server  

	Output      - no output

	Error       - no error
*/
void ServerDestroy(Server **_server) ;

/*
	Description - run the server 

	Input       - a) pointer to server  

	Output      - no output

	Error       - no error
*/
void ServerRun(Server *_server ) ;

/*
	Description - send message to client

	Input       - number client socket

	Output      - a) 1 
                      b) errno

	Error       - a) 1 - func SUCCEEDED
                      b) errno - func failed
*/
int SendMessage(Server *_server, int _clientSocket, void *_msg, int _sizeMsg);

#endif /* __SERVER_NET_H__ */
