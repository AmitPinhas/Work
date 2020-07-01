#include <stdio.h>      /* perror */
#include <sys/types.h>  /* socket , bind */
#include <sys/socket.h> /* socket , bind */
#include <unistd.h>     /* close */
#include <arpa/inet.h>  /* htons */
#include <string.h>     /* memset */
#include <netinet/in.h> /* inet_addr */
#include <arpa/inet.h>  /* inet_addr */
#include <errno.h>      /* errno */
#include <stdlib.h>     /* allocation */

/* -------------- defines ------------------ */

#define FUNC_SUCCEEDED 1
#define SERVER_PORT    2300 
#define LOOPBACK_ADDR  "127.0.0.1" 
#define SIZE_ARRAY     1000
#define FOREVER        1
#define ROYI           "192.168.0.35"
#define PERCENT        100

/* -------------- struct ------------------- */
typedef struct{
        int *m_sockets ;
}ServerArgs;


/* ------------ local func ----------------- */

static int GetSocket(ServerArgs *_serverArgs , int _index);
static int SentAndRecData(ServerArgs *_serverArgs, int _index);
static int CloseSocket(ServerArgs *_serverArgs, int _index);

/* ======================== main ========================= */

int main()
{
        int res , i , socket , randNum ;
        ServerArgs serverArgs ;
        
	serverArgs.m_sockets = (int*) calloc( SIZE_ARRAY , sizeof(int) );

	while ( FOREVER )
	{
	        for ( i = 0 ; i < SIZE_ARRAY ; i = rand()%SIZE_ARRAY )
	        {
	             socket = serverArgs.m_sockets[i] ;
	             
	             if ( 0 == socket )
	             {
	                randNum = rand()%PERCENT ;
	                
	                if ( randNum <= 30 )
	                {
                                  if ( ( res = GetSocket( &serverArgs , i ) ) != FUNC_SUCCEEDED )
                                   {
                                            return res ;
                                   }	                        
	                }
	             }
	             else
	             {
	                randNum = rand() % PERCENT ;
	                
	                if ( randNum >= 85 )
	                {
                               if ( ( res = SentAndRecData( &serverArgs , i ) ) != FUNC_SUCCEEDED )
                                {
                                          return res ;
                                }	                        
	                }
	                
	                if ( randNum <= 30 )
	                {
                               if ( ( res = CloseSocket( &serverArgs , i )) != FUNC_SUCCEEDED )
                               {
                                        return res ;
                               }	                        
	                }
	                
	             }
	        }

	}
	
	free ( serverArgs.m_sockets ) ;
	
	return 0;
}


/* ======================= local func ========================= */

/* --------------- Get Socket ------------ */
static int GetSocket(ServerArgs *_serverArgs, int _index)
{  
        struct sockaddr_in sin ;  
        int tmp ;         
       tmp = socket(AF_INET, SOCK_STREAM, 0);
       if ( tmp < 0 )
       {
                perror("socket failed");
                return errno;
       }
       
       _serverArgs ->  m_sockets[_index] = tmp ;
       
       printf("new client socket %d\n" ,  _serverArgs ->  m_sockets[_index]);
       
        memset(&sin, 0, sizeof(sin) );
        sin.sin_family = AF_INET ;
        sin.sin_addr.s_addr = inet_addr(ROYI) ;
        sin.sin_port = htons( 8080 ) ;        
        
	if ( connect( _serverArgs ->  m_sockets[_index], (struct sockaddr *) &sin, sizeof(sin) ) < 0)
	{
		perror("connect failed");
		return errno;
	}	


       return FUNC_SUCCEEDED ;
}



/* -------------- Sent Data -------------- */
static int SentAndRecData(ServerArgs *_serverArgs, int _index)
{
        char data[20] = "royi the kinggg"  ;
	int sentBytes , readBytes ;
	int dataLen = 54 ;
	char buffer[4096];
	int bufLen = sizeof(buffer) ;
        
        sprintf( data , "royi the kinggg %d" , _serverArgs ->  m_sockets[_index] );
        
	sentBytes = send( _serverArgs ->  m_sockets[_index], data, dataLen, 0);
	if ( sentBytes < 0 )
	{
		perror("send failed");
		return errno;
	}
        
        printf( "sent data %d\n" ,  _serverArgs ->  m_sockets[_index] );
        
        readBytes = recv( _serverArgs ->  m_sockets[_index], buffer, bufLen, 0 );
	if ( 0 == readBytes )
	{
		close ( _serverArgs ->  m_sockets[_index] ) ;
		 _serverArgs ->  m_sockets[_index] = 0 ;
                return FUNC_SUCCEEDED ;
	}	

	printf("%s\n" , buffer);	
            
        return FUNC_SUCCEEDED ;
}


/* --------------- Close Socket ---------------- */
static int CloseSocket(ServerArgs *_serverArgs, int _index)
{

        printf( "close client socket %d \n" ,  _serverArgs ->  m_sockets[_index] );

        if ( close( _serverArgs ->  m_sockets[_index]) < 0 )
        {
                perror("close");
                return errno;
        }	
        
        _serverArgs ->  m_sockets[_index] = 0 ;
        
	return FUNC_SUCCEEDED ;
}






