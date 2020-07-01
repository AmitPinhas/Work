#include <stdio.h>                        /* perror */
#include <sys/time.h>                     /* select */
#include <sys/types.h>                    /* socket , bind , send */
#include <sys/socket.h>                   /* socket , bind , send */
#include <unistd.h>                       /* close */
#include <arpa/inet.h>                    /* htons */
#include <string.h>                       /* memset */
#include <netinet/in.h>                   /* inet_addr */
#include <arpa/inet.h>                    /* inet_addr */
#include <errno.h>                        /* errno */
#include <fcntl.h>                        /* fcntl */
#include <stdlib.h>                       /* allocation */
#include "DLList.h"              	       /* doubly link list */
#include "list_functions.h"               /* List Itr For Each */
#include "list_itr.h"                     /* List Itr */
#include "server_net.h"                   /* API server net */

/* ------------------------ define ----------------------------- */

#define SOCKET_PROTOCOL       0 
#define FAIL                  -1
#define SMALLEST_PORT_NUM     1025
#define BIGGER_PORT_NUM       64000
#define FUNC_SUCCEEDED        1
#define EMPTY                 0
#define MIN_SIZE_LISTEN_QUEUE 1
#define MAX_NUM_DESCRIPTOR    1024
#define FOREVER               1
#define BUFFER_SIZE           4096
#define OK                    1
#define ERROR                 0
#define SEND_FLAG             0

/* ------------------------- macro ------------------------------ */
#define SEND_FUNC(Func, Data) \
{                             \
	if ( Func != NULL )      \
	{					\
		Func(Data);		\
	}					\
}						 					

#define NEW_CLIENT(Server) ( (Server)->m_functions.m_funcNewClient )
#define CLIENT_LEFT(Server) ( (Server)->m_functions.m_funcClientLeft )
#define FUNC_ERROR(Server) ( (Server)->m_functions.m_funcError )
#define FUNC_NEW_MSG(Server) ( (Server)->m_functions.m_funcNewMsg )
#define ACTIVITY(Server) ( (Server)->m_selectArgs.m_activity )
#define MASTER_FDS(Server) ( (Server)->m_selectArgs.m_masterFds ) 
#define TMP_FDS(Server) ( (Server)->m_selectArgs.m_tmpFds ) 
#define CLIENT_COUNT(Server) ( (Server)->m_clientArgs.m_clientCount ) 
#define MAX_CLIENTS(Server) ( (Server)->m_clientArgs.m_maxClients ) 
#define CLIENT_SOCKETS(Server) ( (Server)->m_clientArgs.m_clientSockets ) 

/* ------------------------- structs ----------------------------- */

/* --------------- funcs ----------------- */
typedef struct{
     NewClient          m_funcNewClient ;
	ClientLeft         m_funcClientLeft ;  
	ErrorFunc          m_funcError ;	
	NewMessage         m_funcNewMsg ;	    
}Funcs;

/* -------------- select ----------------- */
typedef struct{
	int                m_activity ;
	fd_set             m_masterFds ;
	fd_set             m_tmpFds ;			
}Select;

/* ------------- client ------------------ */
typedef struct{
	int                m_clientCount ;
	int                m_maxClients ;      
	List               *m_clientSockets ;	
}Client;

/* -------------- Server ---------------- */
struct Server{
     int                m_listenSocket ;   	 
	Client             m_clientArgs ;
	Select             m_selectArgs ;
	Funcs              m_functions ;				       
};


/* ---------------------- local func ----------------------------- */

static int SocketNonBlock(Server *_server, int _socket ) ;
static void CheckNewClient ( Server *_server ) ;  
static int* CreateSocketClient ( int _clientSocket ) ;
static void CheckCurClient( Server *_server ) ;
static int ReciveAndSentData(void* _clientSocket, void* _server);
static void DestroySocketClient ( void* _clientSocket ) ;
static int CheckParams(ServerArgs *_serverArgs) ;
static int Bind(int _portNum, int _serverSocket) ;
static int InitRestArgsServer(Server *_server, ServerArgs *_serverArgs) ;
static int SetoptBindListenNonBlock(Server *_server, ServerArgs *_serverArgs) ;
static void WaitForActivity(Server *_server ) ; 
static void AcceptNewClient(Server *_server ) ; 
static void CloseClientSocket(Server *_server, int _clientSocket) ;
static void EnterNewClient(Server *_server, int _socketClient) ;  

/* ========================= API ================================= */

/* -------------------- Server Create ---------------------------- */
Server* ServerCreate(ServerArgs *_serverArgs)
{
	Server *server ;

	if ( ERROR ==  CheckParams( _serverArgs ) )
	{
		return NULL ;
	}
        
	server = (Server*) malloc( sizeof(Server) ) ;
     if ( NULL == server )
     {
          return NULL ;
     }	
    
     server ->  m_listenSocket = socket(AF_INET, SOCK_STREAM, SOCKET_PROTOCOL); 
     if ( FAIL == server ->  m_listenSocket )
     {
		free( server ) ;
		return NULL ;
     } 

	if ( ERROR == SetoptBindListenNonBlock(server, _serverArgs) )
	{
		close ( server ->  m_listenSocket ) ;
		free( server ) ;
		return NULL ;
	}             

	if ( ERROR == InitRestArgsServer( server, _serverArgs ) )
	{
		close ( server ->  m_listenSocket ) ;
		free( server ) ;
		return NULL ;
	}
	    	   
     return server ;                         	                
}


/* ------------------------- Server Destroy -------------------------- */
void ServerDestroy(Server **_server) 
{
	if ( (NULL != _server) && (NULL != *_server) )
	{
		close(  (*_server) ->  m_listenSocket) ;
						 
		ListDestroy( &( CLIENT_SOCKETS(*_server)) , DestroySocketClient ) ; 
						 
		free ( *_server ) ;
		*_server = NULL ;             
	}
		   
	return;
}


/* --------------------------- Server Run --------------------------- */
void ServerRun(Server *_server ) 
{
	if ( NULL == _server )
	{
		return ;
	}
	
	while (FOREVER)
	{
	     WaitForActivity( _server ) ;
		                        
		CheckNewClient( _server )  ;
			  
		CheckCurClient( _server )  ;           
	}
		           
	return ;
}


/* ----------------------- Send Message ----------------------------- */
int SendMessage(Server *_server, int _clientSocket, void *_msg, int _sizeMsg)
{
	if ( FAIL == send( _clientSocket, _msg, _sizeMsg, SEND_FLAG) )
	{
		SEND_FUNC( FUNC_ERROR(_server), SEND_ERROR ) ;
		return errno ;
	}
            
	return FUNC_SUCCEEDED ;
}

/* ======================= local func ================================ */

/* -------------------- Socket Non Block ----------------------------- */
static int SocketNonBlock(Server *_server, int _socket )
{
	int flags ;
        
	if ( FAIL == ( flags = fcntl(  _socket, F_GETFL ) ) )
	{
		SEND_FUNC( FUNC_ERROR(_server), FCNTL_ERROR ) ;   
		return errno;
	}
       
	if ( FAIL == fcntl( _socket, F_SETFL, flags | O_NONBLOCK ) )
	{
		SEND_FUNC( FUNC_ERROR(_server), FCNTL_ERROR ) ;   
		return errno;
	}
               
	return FUNC_SUCCEEDED ;
}


/* ------------------------ Check New Client ------------------------ */
static void CheckNewClient ( Server *_server )
{
	if ( FD_ISSET (  _server ->  m_listenSocket , &(TMP_FDS(_server)) ) )
	{
		ACTIVITY(_server)-- ;
			
		AcceptNewClient( _server ) ;	
	}
	
	return ;
} 

/* ---------------------- CreateSocketClient ------------------------ */
static int* CreateSocketClient ( int _clientSocket ) 
{
        int *ptrSocket ;
        
        ptrSocket = (int*) malloc( sizeof(int) ) ;
        if ( NULL == ptrSocket )
        {
        		return NULL ;
        }
        
        *ptrSocket = _clientSocket ;
        
        return ptrSocket ;
}



/* ---------------------- Check Cur Client -------------------------- */
static void CheckCurClient( Server *_server )
{          
	ListItr beginItr ,  endItr , returnItr ;
        
	beginItr =  ListItrBegin( CLIENT_SOCKETS(_server) ) ;
	endItr =  ListItrEnd( CLIENT_SOCKETS(_server) ) ;   
       
	while ( ACTIVITY(_server) > 0 )
	{                      
		returnItr = ListItrForEach( beginItr, endItr , ReciveAndSentData, _server );                
		if ( ACTIVITY(_server) > 0 )
		{
			ACTIVITY(_server)-- ;
			beginItr = ListItrNext( returnItr ) ;
			ListItrRemove( returnItr );
		}    
	}
	return;
}


/* --------------------- Recive And Sent Data ------------------------ */
static int ReciveAndSentData(void* _clientSocket, void* _server)
{
	int readBytes ;
	char buffer[BUFFER_SIZE] ;
	int clientSocket = *((int*)_clientSocket) ;
	Server *server = ((Server*)_server) ;
        
	memset( buffer, 0, sizeof(buffer) );
        
	if ( FD_ISSET ( clientSocket , &(TMP_FDS(server)) ) ) 
	{  
		readBytes = recv ( clientSocket, buffer, sizeof(buffer), 0);	
		if ( FAIL == readBytes )
		{
			SEND_FUNC( FUNC_ERROR(server), RECV_ERROR ) ;
			return errno;
		}
		else if ( 0 == readBytes )
		{
			CloseClientSocket( server, clientSocket ) ;     
			return 0 ;			
		}
		else
		{
			FUNC_NEW_MSG(server)( server, clientSocket, buffer, sizeof(buffer) );      
		}
		ACTIVITY(server)-- ;    
	} 
        
	if ( ACTIVITY(server) == 0 )
	{
		return 0 ;
	}
               
	return  FUNC_SUCCEEDED ;                
}


/* -------------------- Destroy Socket Client ----------------------- */
static void DestroySocketClient ( void* _clientSocket ) 
{
	   close( *((int*)_clientSocket) ) ;
        free(_clientSocket) ;
}


/* ----------------------- Check Params ------------------------------ */
static int CheckParams(ServerArgs *_serverArgs) 
{
	        if ( ( _serverArgs -> m_portNum < SMALLEST_PORT_NUM ) || ( _serverArgs -> m_portNum > BIGGER_PORT_NUM ) || ( _serverArgs -> m_sizeListenQueue < MIN_SIZE_LISTEN_QUEUE ) || ( NULL == ( _serverArgs -> m_funcNewMsg ) ) )
        {
                return ERROR ;
        }
        
        return OK ;
}

/* -------------------------- Bind ----------------------------------- */
static int Bind(int _portNum, int _serverSocket) 
{
     struct sockaddr_in sin ; 

     memset(&sin, 0, sizeof(sin));
     sin.sin_family = AF_INET ;
     sin.sin_addr.s_addr = INADDR_ANY ;
     sin.sin_port = htons( _portNum ) ; 
     if( FAIL ==  bind ( _serverSocket, (struct sockaddr *) &sin, sizeof(sin) ) )
     {
		return ERROR ;
     }      
     
     return OK ;
}


/* --------------------- Init Rest Args Server ----------------------- */
static int InitRestArgsServer(Server *_server, ServerArgs *_serverArgs) 
{
     FD_ZERO ( &(MASTER_FDS(_server)) ) ;
     FD_ZERO ( &(TMP_FDS(_server)) ) ;
     FD_SET ( _server ->  m_listenSocket, &(MASTER_FDS(_server)) ) ;                

     CLIENT_SOCKETS(_server) = ListCreate() ;
     if ( NULL == CLIENT_SOCKETS(_server) )
     {
		return ERROR ;
     }        
        
     CLIENT_COUNT(_server) = EMPTY ;        
	MAX_CLIENTS(_server) = _serverArgs -> m_maxCLients ;   
	NEW_CLIENT(_server) = _serverArgs -> m_funcNewClient ;
    	CLIENT_LEFT(_server) = _serverArgs -> m_funcClientLeft ;
     FUNC_ERROR(_server) = _serverArgs -> m_funcError ;
     FUNC_NEW_MSG(_server) = _serverArgs -> m_funcNewMsg ;
     
     return OK ;
}

/* ----------------- Setopt Bind Listen NonBlock --------------------- */
static int SetoptBindListenNonBlock(Server *_server, ServerArgs *_serverArgs)
{
	int optVal = 1 ;
	
     if ( FAIL == setsockopt( _server ->  m_listenSocket, SOL_SOCKET, SO_REUSEADDR, &optVal, sizeof(optVal)) )
	{
		return ERROR ;
	}    

	if ( ERROR == Bind( _serverArgs -> m_portNum, _server ->  m_listenSocket) )
	{
		return ERROR ;	
	}  
       
     if ( FAIL ==  listen( _server ->  m_listenSocket, _serverArgs -> m_sizeListenQueue ) )
     {
		return ERROR ;	
     }    
     
       
     if ( (SocketNonBlock(_server , _server ->  m_listenSocket ) ) != FUNC_SUCCEEDED )
     {
		return ERROR ;	
     }       
     
     return OK ;	
}

/* ---------------------- Wait For Activity ------------------------- */
static void WaitForActivity(Server *_server ) 
{
	TMP_FDS(_server) = MASTER_FDS(_server) ;
		
	ACTIVITY(_server) = select ( MAX_NUM_DESCRIPTOR, &(TMP_FDS(_server)), NULL, NULL, NULL);	
	
	if ( ( FAIL == ACTIVITY(_server) ) && (errno != EINTR) )
	{
		SEND_FUNC( FUNC_ERROR(_server), SELECT_ERROR ) ;  	
	}
	
	return ;
}


/* --------------------- Accept New Client -------------------------- */
static void AcceptNewClient(Server *_server )
{  
     struct sockaddr_in client_sin ;
	socklen_t addr_len = sizeof(client_sin) ;
	int socketClient = 1 ; 
		
	while ( socketClient != FAIL )
	{
		socketClient = accept(  _server ->  m_listenSocket, (struct sockaddr *) &client_sin, &addr_len);
		if ( errno != EAGAIN && errno != EWOULDBLOCK && socketClient == FAIL  )
		{
			SEND_FUNC( FUNC_ERROR(_server), ACCEPT_ERROR ) ;  
			return ;
		} 					   
		if ( socketClient > 0 )
		{	
			EnterNewClient( _server,  socketClient	) ;   
		}
	}		
	return ;
}


/* -------------------------- Close Client Socket ----------------------- */
static void CloseClientSocket(Server *_server, int _clientSocket) 
{
	SEND_FUNC( CLIENT_LEFT(_server), _clientSocket ) ;
	FD_CLR( _clientSocket ,  &(MASTER_FDS(_server)) ) ;
	close(_clientSocket) ;   
	CLIENT_COUNT(_server)-- ; 
}

/* --------------------------- Enter New Client ------------------------- */
static void EnterNewClient(Server *_server, int _socketClient) 
{
	if ( CLIENT_COUNT(_server) >= MAX_CLIENTS(_server) )
	{
		SEND_FUNC( FUNC_ERROR(_server), SERVER_FULL ) ;  			
		close ( _socketClient ) ;
		return ;
	}  
		              
	ListPushHead ( CLIENT_SOCKETS(_server) ,  CreateSocketClient( _socketClient ) ) ;						    
	FD_SET( _socketClient ,  &(MASTER_FDS(_server)) ) ;			    
	CLIENT_COUNT(_server)++ ;			
	SEND_FUNC(NEW_CLIENT(_server), _socketClient) ; 
	
	return;
}


