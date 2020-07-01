#include <stdio.h>      /* perror */
#include <sys/types.h>  /* socket , bind */
#include <sys/socket.h> /* socket , bind */
#include <unistd.h>     /* close */
#include <arpa/inet.h>  /* htons */
#include <string.h>     /* memset */
#include <netinet/in.h> /* inet_addr */
#include <arpa/inet.h>  /* inet_addr */
#include <errno.h>      /* errno */

/* -------------- defines ------------------ */

#define FUNC_SUCCEEDED 1
#define SERVER_PORT    2000 
#define LOOPBACK_ADDR  "127.0.0.1" 

/* -------------- struct ------------------- */
typedef struct{
        int m_sock ;
        struct sockaddr_in m_sin ;        
}ServerArgs;


/* ------------ local func ----------------- */

static int CreateSocket(ServerArgs *_serverArgs);
static int ReceiveData(ServerArgs *_serverArgs);
static int SentData(ServerArgs *_serverArgs);
static int CloseSocket(ServerArgs *_serverArgs);

/* ======================== main ========================= */

int main()
{
        int res ;
        ServerArgs serverArgs ;
        
        if ( ( res = CreateSocket( &serverArgs ) ) != FUNC_SUCCEEDED )
        {
                return res ;
        }

        if ( ( res = ReceiveData( &serverArgs ) ) != FUNC_SUCCEEDED )
        {
                return res ;
        }
	
        if ( ( res = SentData( &serverArgs ) ) != FUNC_SUCCEEDED )
        {
                return res ;
        }
	
        if ( ( res = CloseSocket( &serverArgs ) ) != FUNC_SUCCEEDED )
        {
                return res ;
        }
	
	return 0;
}


/* ======================= local func ========================= */

/* --------------- Create Socket ------------ */
static int CreateSocket(ServerArgs *_serverArgs)
{
        struct sockaddr_in sin ;        
        
       _serverArgs ->  m_sock = socket(AF_INET, SOCK_DGRAM, 0);
       if ( _serverArgs ->  m_sock < 0 )
       {
                perror("socket failed");
                return errno;
       }
       
       memset(&sin, 0, sizeof(sin));
       sin.sin_family = AF_INET ;
       sin.sin_addr.s_addr = INADDR_ANY ;
       sin.sin_port = htons( SERVER_PORT ) ;
       
       if( bind ( _serverArgs ->  m_sock, (struct sockaddr *) &sin, sizeof(sin) ) < 0 )
       {
                perror("bind failed");
                return errno;
       }
       
       return FUNC_SUCCEEDED ;
}


/* --------------- Receive Data ------------ */
static int ReceiveData(ServerArgs *_serverArgs)
{
        struct sockaddr_in sin ;  
        socklen_t sinLen , readBytes ;
        char buffer[4096] ;
        
        if ( ( readBytes = recvfrom( _serverArgs ->  m_sock, buffer, sizeof(buffer), 0, (struct sockaddr *) &sin, &sinLen ) ) < 0 )
        {
                perror("recvfrom failed");
                return errno;
        }  
        
        _serverArgs -> m_sin = sin ;
        printf("%d\n",readBytes);
        printf("%s\n", buffer);
        
                
        return FUNC_SUCCEEDED;
}


/* -------------- Sent Data -------------- */
static int SentData(ServerArgs *_serverArgs)
{
        int sent_bytes ;
        char *data = "Thank you" ;

        if ( ( sent_bytes = sendto(_serverArgs ->  m_sock, data, 9, 0,(struct sockaddr *) &(_serverArgs -> m_sin), sizeof(_serverArgs -> m_sin) ) ) < 0 )
        {
                perror("sendto failed");
                return errno;
        }
        
            
        return FUNC_SUCCEEDED ;
}

/* ---------------- Close Socket ----------- */
static int CloseSocket(ServerArgs *_serverArgs)
{
        if ( close( _serverArgs ->  m_sock) < 0 )
        {
                perror("close");
                return errno;
        }
        
        return FUNC_SUCCEEDED;
}





