#include "socket.hpp"

#include <netinet/in.h>						/* inet_addr */
#include <arpa/inet.h>						/* inet_addr */
#include <string.h>							/* memset */
#include <fcntl.h>							/* fcntl */

namespace advcpp
{
Socket::Socket(int a_domain, int a_type, int a_protocol)
: m_socket(socket(a_domain, a_type, a_protocol))
{
}

Socket::Socket(size_t a_socketNum)
: m_socket(static_cast<int>(a_socketNum))
{
}

void Socket::Setsockopt()
{
    int optVal = 1 ;
	
    setsockopt( m_socket, SOL_SOCKET, SO_REUSEADDR, &optVal, sizeof(optVal)) ;
}

void Socket::Bind(int a_portNum)
{
     struct sockaddr_in sin ; 

     memset(&sin, 0, sizeof(sin));
     sin.sin_family = AF_INET;
     sin.sin_addr.s_addr = INADDR_ANY;
     sin.sin_port = htons( a_portNum ); 
     bind ( m_socket, (struct sockaddr *) &sin, sizeof(sin) );
}

void Socket::Listen(int a_sizeListenQueue)
{
    listen( m_socket, a_sizeListenQueue );
}

void Socket::NonBlock()
{
	int flags ;
        
	flags = fcntl( m_socket, F_GETFL );
       
	fcntl( m_socket, F_SETFL, flags | O_NONBLOCK );
}

void Socket::Send(void* a_msg, int a_sizeMsg, int a_flag)
{
    send(m_socket, a_msg, a_sizeMsg, a_flag);
}

int Socket::MySocket()
{
    return m_socket;
}

void Socket::Connect(size_t a_portNum, const char* a_ip)
{
    struct sockaddr_in sin ;  

    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = inet_addr(a_ip);
    sin.sin_port = htons(a_portNum);        
        
	connect(m_socket, (struct sockaddr *) &sin, sizeof(sin));       
}
} // namespace advcpp
