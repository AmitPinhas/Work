#ifndef SERVER_HPP
#define SERVER_HPP

//#define _XOPEN_SOURCE 500


#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <errno.h>
#include <netinet/in.h>
#include <netinet/ip.h> /* superset of previous */
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/select.h>
#include <list>

#define LOOP_BACK_IP "127.0.0.1"

#include "Common.hpp"

namespace advcpp
{


int g_flag;

enum {FAIL=-1, SUCCES=1, MAX_CHANNELS=666};

struct ServerData
{
    int m_sockServer;
    int m_activity;
    int m_counter;
    struct sockaddr_in m_sin;
    fd_set m_master;
    fd_set m_temporary;
    std::list<int> m_clients; // maybe better use a set

};


template <typename UserClass>
class Server :  private Uncopyable
{
public:
    Server(size_t a_buffSize, size_t a_port, size_t a_maxNumClient, int(*m_newMSG)(int a_sock, void* a_buffer) );
    // int RemoveClient(int a_sock);
    int SendMSG(void* _buffer, int _sock, size_t _len);
    void Run();

private:
    void makeServer();
    void initServer();
    int flagInit(int _sock);
    int newClient(int a_sock);
    void checkNewClient();
    int isNewClient();
    int reciveMSG(int a_sock);
    void checkNewMSG();

private: 
    size_t m_maxNumClient;
    size_t m_port;
    size_t m_buffer;
    ServerData m_sd;
    //Error m_error;
    int (*m_app)(int a_sock, void* a_buffer); // must build an class for this 
    //NewClient m_newClient;
    //DeleteClient m_removeClient;

};

template <typename UserClass>
int Server<UserClass>::flagInit(int _sock)
{
    int flag;
    if(FAIL==(flag=fcntl(_sock,F_GETFL)))
    {
        throw "error at fcntl,F_GETFL";
        return FAIL;
    }
    
    if(-1==fcntl(_sock,F_SETFL,flag|O_NONBLOCK))
    {
        throw "error at fcntl,F_SETFL";
        return FAIL;
    }
    
    return SUCCES;
}

template <typename UserClass>
void Server<UserClass>::initServer()
{
    int optval = 1;
    //struct sockaddr_in sin;

    memset(&m_sd.m_sin,0,sizeof(m_sd.m_sin));
    
    m_sd.m_sin.sin_family = AF_INET;
    
    m_sd.m_sin.sin_addr.s_addr = inet_addr(LOOP_BACK_IP);
    
    m_sd.m_sin.sin_port = htons(m_port);
    
    if(setsockopt(m_sd.m_sockServer, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)) < 0 )
    {
        throw "reuse failed";
        
        memset(&m_sd.m_sin,0,sizeof(m_sd.m_sin));
        
    }
    
    if(bind( m_sd.m_sockServer,(struct sockaddr *)&m_sd.m_sin, sizeof(m_sd.m_sin) )<0)
    {
        throw "bind failed";
        
        memset(&m_sd.m_sin, 0, sizeof(m_sd.m_sin) );
        
    }
    
    if (listen(m_sd.m_sockServer,100) < 0)
    {
        throw "listen failed";

        memset(&m_sd.m_sin, 0, sizeof(m_sd.m_sin));
    }
    
    if(flagInit(m_sd.m_sockServer)==FAIL)
    {
        memset(&m_sd.m_sin, 0, sizeof(m_sd.m_sin));
    }
    
    FD_SET(m_sd.m_sockServer, &m_sd.m_master);
    
    m_sd.m_counter++;
    
}

template <typename UserClass>
void Server<UserClass>::makeServer()
{
    m_sd.m_sockServer = socket(AF_INET,SOCK_STREAM,0);

    if(m_sd.m_sockServer<0)
    {
        throw "socket failed";
        //return;
    }

    FD_ZERO(&m_sd.m_master );

    initServer();
}

/* constructor of server */
template <typename UserClass>
Server<UserClass>::Server(size_t a_buffSize, size_t a_port, size_t a_maxNumClient, int(*a_newMSG)(int a_sock, void* a_buffer) )
:   m_maxNumClient(a_maxNumClient)
,   m_port(a_port)
,   m_buffer(a_buffSize)
,   m_app(a_newMSG)
{
    makeServer();
}


template <typename UserClass>
int Server<UserClass>::isNewClient(/*struct sockaddr_in _clientSin, int _sock*/)
{
    unsigned int sizeSin=sizeof(m_sd.m_sin); 

    int client_sock = accept(m_sd.m_sockServer, (struct sockaddr*)&m_sd.m_sin, &sizeSin);

    if(client_sock<0 && errno!=EAGAIN && errno!=EWOULDBLOCK)
    {
        return client_sock ;
    }

    return client_sock;
}

template <typename UserClass>
void Server<UserClass>::checkNewClient( /*ServerData* _sd, struct sockaddr_in _clientSin*/ )
{   
    int sock_client=10/*, *sock_client_malloc*/;

    if( FD_ISSET(m_sd.m_sockServer, &m_sd.m_temporary) )
    {
        while( SUCCES )
        {
            if(m_sd.m_counter > MAX_CHANNELS)
            {
                //todo exception overflow
                return;
            }
            
            if((sock_client = isNewClient() )<0)
            {
                //todo accept failed
                return;
            }
            
            FD_SET(sock_client, &m_sd.m_master);

            m_sd.m_clients.push_front(sock_client);
            
            m_sd.m_counter++;
        }
    }  
}

/* private function  */
template <typename UserClass>
int Server< UserClass >::reciveMSG(int a_sock)
{
    char str[4096];
    int len=sizeof(str), read_bytes;

    read_bytes=recv( a_sock, (void*)str, len, 0);
   // printf("read_bytes %d\n",read_bytes);

    if(read_bytes==0)
    {
        /*REMOVE FROM LIST AND CLEAR SET*/
        //RemoveClient((void*)_server);
        return read_bytes;
    }
    
    else 
    {
        if(read_bytes<0)
        {
            throw "recv failed";
            //return read_bytes; 
        }
    }
    
    /*SEND buffer to APPLICATION */
    m_app(a_sock, str);
    //char strResponse[10] = "recived";
    read_bytes = send(a_sock, strResponse, 10, 0 );
    return read_bytes;
}

template <typename UserClass>
int Server<UserClass>::SendMSG(void* a_buffer, int a_sock, size_t a_len)
{
	int send_bytes=0; 

    send_bytes=send(a_sock, (void*)a_buffer, a_len, 0);

    if(send_bytes<0)
    {
        throw "send failed";
        return -1;
    }
    
   // printf("send_bytes %d\n",send_bytes);
    return send_bytes;
}

template <typename UserClass>
void Server<UserClass>::checkNewMSG(/*Server* _server,void* _context*/)
{
    //_server->m_sd.m_begin=ListItrBegin(_server->m_sd.m_clients);
    std::list<int>::iterator it = m_sd.m_clients.begin();
    //while(!ListItrEquals(_server->m_sd.m_begin, _server->m_sd.m_end))
    for(; it != m_sd.m_clients.end(); ++it)
    {
        if( FD_ISSET( *it, &m_sd.m_temporary) )
        {
            reciveMSG( *it );
            m_sd.m_activity--;
        }
        if( !m_sd.m_activity )
        {
            break;
        }
        //_server->m_sd.m_begin=ListItrNext(_server->m_sd.m_begin);
    }
}

template <typename UserClass>
void Server<UserClass>::Run(/*Server* _server, void* _item*/)
{
    g_flag=1;
    while(g_flag)
    {
        m_sd.m_temporary = m_sd.m_master;

        m_sd.m_activity = select(MAX_CHANNELS+1, &m_sd.m_temporary, 0, 0, 0);

        if(m_sd.m_activity < 0)
        {
            throw "select" ;
            //return SERVER_RUN_ERROR;
        }

        checkNewClient();

        checkNewMSG();

       /* if(ListSize(_server->m_sd.m_clients)==0)
        {
            g_flag=0;  
        }*/
    }
//return SERVER_SUCCESS;
}



}

#endif

