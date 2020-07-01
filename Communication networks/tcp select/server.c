#include <stdio.h>                        /* perror */
#include <sys/time.h>                     /* select */
#include <sys/types.h>                    /* socket , bind */
#include <sys/socket.h>                   /* socket , bind */
#include <unistd.h>                       /* close */
#include <arpa/inet.h>                    /* htons */
#include <string.h>                       /* memset */
#include <netinet/in.h>                   /* inet_addr */
#include <arpa/inet.h>                    /* inet_addr */
#include <errno.h>                        /* errno */
#include <fcntl.h>                        /* fcntl */
#include <stdlib.h>                       /* allocation */
#include "./DLList/DLList.h"              /* doubly link list */
#include "./DLList/list_functions.h"      /* List Itr For Each */
#include "./DLList/list_itr.h"            /* List Itr */


/* ---------------------- defines ---------------------- */

#define FUNC_SUCCEEDED 1
#define SERVER_PORT    2300 
#define LOOPBACK_ADDR  "127.0.0.1" 
#define FAIL           -1
#define FOREVER        1
#define SIZE_QUEUE     1000
#define MAX_CLIENTS    1000

/* ---------------------- struct ----------------------- */
typedef struct{
        int                m_serverSocket ;  
	List               *m_clientSockets ;
	int                m_clientCount ;
	fd_set             m_readFds ;
	fd_set             m_tmpReadFds ;
	int                m_activity ;
}ServerArgs;


/* ------------------- local func ----------------------- */

static int InitServer(ServerArgs *_serverArgs);
static int ReceiveAndSentData(ServerArgs *_serverArgs);
static int SentData(int _clientSocket);
static int CloseServer(ServerArgs *_serverArgs);
static int CheckCurClient(ServerArgs *_serverArgs);
static int CheckNewClient ( ServerArgs *_serverArgs);   
static int* CreateSocketClient ( int _clientSocket ) ;
static void DestroySocketClient ( void* _clientSocket ) ;
static int ReciveData(void* _clientSocket, void* _ServerArgs);
static int SocketNonBlock( int _socket );

/* ======================= main ========================= */

int main()
{
        int res ;
        ServerArgs serverArgs ;
        
        if ( ( res = InitServer( &serverArgs ) ) != FUNC_SUCCEEDED )
        {
                return res ;
        }

        if ( ( res = ReceiveAndSentData( &serverArgs ) ) != FUNC_SUCCEEDED )
        {
                return res ;
        }

        if ( ( res = CloseServer( &serverArgs ) ) != FUNC_SUCCEEDED )
        {
                return res ;
        }
	
	return 0;
}


/* ======================= local func ========================= */

/* --------------- Init Server ------------ */
static int InitServer(ServerArgs *_serverArgs)
{
        struct sockaddr_in sin ;  
	int optVal = 1, res ;      
        
       _serverArgs ->  m_serverSocket = socket(AF_INET, SOCK_STREAM, 0);
       if ( _serverArgs ->  m_serverSocket < 0 )
       {
                perror("socket failed");
                return errno;
       }

       if (setsockopt( _serverArgs ->  m_serverSocket, SOL_SOCKET, SO_REUSEADDR, &optVal, sizeof(optVal)) < 0 )
	{
		perror("reuse failed") ;
		return errno ;
	}
       
       memset(&sin, 0, sizeof(sin));
       sin.sin_family = AF_INET ;
       sin.sin_addr.s_addr = INADDR_ANY ;
       sin.sin_port = htons( SERVER_PORT ) ;
       
       if( bind ( _serverArgs ->  m_serverSocket, (struct sockaddr *) &sin, sizeof(sin) ) < 0 )
       {
                perror("bind failed");
                return errno;
       }
        
       if (listen( _serverArgs ->  m_serverSocket, SIZE_QUEUE) < 0 )
       {
		perror("listen failed");
                return errno;
       }   

        if ( (res = SocketNonBlock( _serverArgs ->  m_serverSocket ) ) != FUNC_SUCCEEDED )
        {
                return res ;
        }


        FD_ZERO ( &(_serverArgs -> m_readFds) ) ;
        FD_ZERO ( &(_serverArgs -> m_tmpReadFds) ) ;
        
        FD_SET ( _serverArgs ->  m_serverSocket, &(_serverArgs -> m_readFds) ) ;
        
        _serverArgs -> m_clientSockets = ListCreate() ;
        if ( NULL == _serverArgs -> m_clientSockets )
        {
                return FAIL ;
        }
        
        _serverArgs -> m_clientCount = 0 ;
       
       return FUNC_SUCCEEDED ;
}


/* --------------- Receive And Sent Data ------------ */
static int ReceiveAndSentData(ServerArgs *_serverArgs)
{
        int res ;

        while (FOREVER)
        {
                              
              if ( ( res = CheckNewClient( _serverArgs ) ) != FUNC_SUCCEEDED )
              {
                        return res ;
              } 
        
              if ( ( res = CheckCurClient( _serverArgs ) ) != FUNC_SUCCEEDED )
              {
                        return res ;
              }                   
                
        }
        
        
        return FUNC_SUCCEEDED;
}


/* -------------- Sent Data -------------- */
static int SentData(int _clientSocket)
{
        int dataLen = 20 ;
        char data[20] = "Thank you" ;
        int writeBytes ;
        
        sprintf ( data , "Thank you %d" , _clientSocket-1 );

        writeBytes = send( _clientSocket, data, dataLen, 0);        
        if ( errno != EAGAIN && errno != EWOULDBLOCK && writeBytes == -1 )
        {
                perror("send failed");
                return errno;
        }
       
            
        return FUNC_SUCCEEDED ;
}

/* ---------------- Close Server ----------- */
static int CloseServer(ServerArgs *_serverArgs)
{
        if ( close( _serverArgs ->  m_serverSocket) < 0 )
        {
                perror("close");
                return errno;
        }
        
        ListDestroy( &(_serverArgs -> m_clientSockets) , DestroySocketClient ) ;
        
        return FUNC_SUCCEEDED;
}


/* ---------------- Check Cur Client ------------ */
static int CheckCurClient(ServerArgs *_serverArgs)
{          
       ListItr beginClientSockets ,  endClientSockets , res ;
        
       beginClientSockets =  ListItrBegin( _serverArgs -> m_clientSockets ) ;
       endClientSockets =  ListItrEnd( _serverArgs -> m_clientSockets ) ;   
       res = beginClientSockets ;
       
       while (  ! ListItrEquals( res , endClientSockets ) && _serverArgs -> m_activity > 0 )
       {                      
                res = ListItrForEach( beginClientSockets, endClientSockets , ReciveData, _serverArgs ); 
                
                if ( ! ListItrEquals( res , endClientSockets ) && _serverArgs -> m_activity > 0 )
                {
                        beginClientSockets = ListItrNext( res ) ;
                        ListItrRemove( res );
                }
                else
                {
                        return FUNC_SUCCEEDED ;
                }
       
       }

       return FUNC_SUCCEEDED ;
}


/* -------------------- Check New Client ----------------- */
static int CheckNewClient ( ServerArgs *_serverArgs)
{
        struct sockaddr_in client_sin ;
	socklen_t addr_len = sizeof(client_sin) ;
	int res=1 ;   
	
	_serverArgs -> m_tmpReadFds = _serverArgs -> m_readFds ;
	
	_serverArgs->m_activity = select ( 1024, &(_serverArgs -> m_tmpReadFds), NULL, NULL, NULL);
	if ( (_serverArgs->m_activity < 0) && (errno != EINTR) )
	{
	        perror("select error");
	        return errno;
	}
	
	if ( FD_ISSET (  _serverArgs ->  m_serverSocket , &(_serverArgs -> m_tmpReadFds) ) )
	{
	
	        _serverArgs->m_activity-- ;
	
	        while ( res != -1 )
	        {
	                  res = accept(  _serverArgs ->  m_serverSocket, (struct sockaddr *) &client_sin, &addr_len);
	                   if ( errno != EAGAIN && errno != EWOULDBLOCK && res == -1  )
	                   {
	        	        perror("accept failed");
	        	        return errno;
	                   } 
	        
	                   if ( res > 0 )
	                   {
	       
	                       if ( _serverArgs -> m_clientCount >= MAX_CLIENTS )
	                       {
	                            close ( res ) ;
	                            return FUNC_SUCCEEDED ;
	                       }  
                   
	                        ListPushHead ( _serverArgs -> m_clientSockets ,  CreateSocketClient( res ) ) ;
	         
	                        FD_SET( res ,  &(_serverArgs -> m_readFds) ) ;
	         
	                        _serverArgs -> m_clientCount++ ;
    
	                   }
	        }
	
	}
	
        return FUNC_SUCCEEDED ;
} 


/* ------------------- CreateSocketClient ---------------- */
static int* CreateSocketClient ( int _clientSocket ) 
{
        int *ptrSocket ;
        
        ptrSocket = (int*) malloc ( sizeof(int) ) ;
        
        *ptrSocket = _clientSocket ;
        
        return ptrSocket ;
}


/* ------------------ Destroy Socket Client ------------- */
static void DestroySocketClient ( void* _clientSocket ) 
{
        free(_clientSocket) ;
}


/* ------------------ Recive Data ---------------------- */
static int ReciveData(void* _clientSocket, void* _serverArgs)
{
        int readBytes, res ;
        char buffer[4096] ;
        int clientSocket = *((int*)_clientSocket) ;
        int expectedDataLen = sizeof(buffer) ;
        
        memset( buffer , 0 ,expectedDataLen );
        
        if ( FD_ISSET ( clientSocket , &( ((ServerArgs*)_serverArgs) -> m_tmpReadFds) ) ) 
        {
              
                readBytes = recv ( clientSocket, buffer, expectedDataLen, 0);	
                if ( 0 == readBytes)
                {
                        FD_CLR( clientSocket ,  &((ServerArgs*)_serverArgs)-> m_readFds ) ;
                        close(clientSocket) ;   
                        ((ServerArgs*)_serverArgs) -> m_clientCount-- ;     
                        return 0 ;
                }
                else if ( errno != EAGAIN && errno != EWOULDBLOCK && readBytes == -1 )
                {
                        perror("recv failed");
                        return errno;
                }
                else if ( ( readBytes == -1 ) && ( (errno == EAGAIN) || (errno == EWOULDBLOCK) ) )
                {
                        return FUNC_SUCCEEDED ;
                }
                else
                {
                        printf("%s\n" ,  buffer);
                        if ( ( res = SentData( clientSocket ) != FUNC_SUCCEEDED ) )
                        {
                                return res ;
                        }          
                }
                 ((ServerArgs*)_serverArgs) -> m_activity-- ;    
        } 
        
        if ( ((ServerArgs*)_serverArgs) -> m_activity == 0 )
        {
                return 0 ;
        }
               
       return  FUNC_SUCCEEDED ;                
}



/* ------------- Socket Non Block ---------- */
static int SocketNonBlock( int _socket )
{
       int flags ;
        
       if ( FAIL == (flags = fcntl(  _socket, F_GETFL)))
	{
		perror("error at fcntl. F_GETFL. ");
		return errno;
	}
       
       if ( FAIL == fcntl( _socket, F_SETFL, flags | O_NONBLOCK))
       {
                perror("error at fcntl. F_SETFL.");
                return errno;
       }        
        return FUNC_SUCCEEDED ;
}



