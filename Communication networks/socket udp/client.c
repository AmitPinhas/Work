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
#define ROYI           "192.168.0.44"

/* -------------- struct ------------------- */
typedef struct{
        int m_sock ;
        
}ServerArgs;


/* ------------ local func ----------------- */

static int GetSocket(ServerArgs *_serverArgs);
static int SentData(ServerArgs *_serverArgs);

/* ======================== main ========================= */

int main()
{
        int res ;
        ServerArgs serverArgs ;
        
        if ( ( res = GetSocket( &serverArgs ) ) != FUNC_SUCCEEDED )
        {
                return res ;
        }
	
        if ( ( res = SentData( &serverArgs ) ) != FUNC_SUCCEEDED )
        {
                return res ;
        }
	
	return 0;
}


/* ======================= local func ========================= */

/* --------------- Create Socket ------------ */
static int GetSocket(ServerArgs *_serverArgs)
{             
       _serverArgs ->  m_sock = socket(AF_INET, SOCK_DGRAM, 0);
       if ( _serverArgs ->  m_sock < 0 )
       {
                perror("socket failed");
                return errno;
       }
       
       return FUNC_SUCCEEDED ;
}



/* -------------- Sent Data -------------- */
static int SentData(ServerArgs *_serverArgs)
{
        struct sockaddr_in sin ;
        int sent_bytes ;
        char *data = "lalala" ;
        
        memset(&sin, 0, sizeof(sin) );
        sin.sin_family = AF_INET ;
        sin.sin_addr.s_addr = inet_addr(LOOPBACK_ADDR) ;
        sin.sin_port = htons( SERVER_PORT ) ;        
        
        if ( ( sent_bytes = sendto(_serverArgs ->  m_sock, data, 6, 0, (struct sockaddr *) &sin, sizeof(sin) ) ) < 0 )
        {
                perror("sendto failed");
                return errno;
        }
        
	printf("%d\n" , sent_bytes );
            
        return FUNC_SUCCEEDED ;
}







