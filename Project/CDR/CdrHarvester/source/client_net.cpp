#include "client_net.hpp"

namespace advcpp
{


client_net::client_net(const char* a_ip, size_t a_port)
:   m_sin()
{
    memset(&m_sin, 0, sizeof(m_sin));
	m_sin.sin_family = AF_INET;
	m_sin.sin_addr.s_addr = inet_addr(a_ip);
	m_sin.sin_port = htons(a_port);

	m_serverSock = socket(AF_INET, SOCK_STREAM, 0);
	if (m_serverSock < 0)
	{
		XTHROW(ClientNetExeption, "socket error");
		
	}
	if (connect(m_serverSock, (struct sockaddr *) &m_sin, sizeof(m_sin)) < 0)
	{
		XTHROW(ClientNetExeption, "connect error");
	}

}


void client_net::MsgSend(void* a_buff, int a_size)
{
    if (a_buff == 0)
    {
        XTHROW(ClientNetExeption, "msg pointer is null");
    }

	int bytes;
	bytes = send(m_serverSock, a_buff, a_size, 0);
	if (bytes <= 0)
	{
		XTHROW(ClientNetExeption, "send error");
	}
	return;
}



void client_net::MsgRecive(void* a_buff, int a_size)
{
    if (a_buff == 0)
    {
        XTHROW(ClientNetExeption, "msg pointer is null");
    }

	int bytes;
	
	bytes = recv(m_serverSock, a_buff, a_size, 0);
	if (bytes <= 0)
	{
		XTHROW(ClientNetExeption, "recive error");
	}
	return;
}

}//advcpp namespace