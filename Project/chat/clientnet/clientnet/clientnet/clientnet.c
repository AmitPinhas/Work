#ifndef _XOPEN_SOURCE
#define _XOPEN_SOURCE 500
#endif
#include <stdio.h> /* printf */ 
#include <stdlib.h> /* malloc */
#include <unistd.h> /* close */
#include <string.h> /* memset, strcpy */
#include <arpa/inet.h> /* struct sockaddr_in*/

#include "../include/clientnet.h" /* Clientnet typedef*/

#define FAILED 			-1
#define SUCCESS 		1
#define IP_CHAR_SIZE    15

struct Clientnet {
	int 		m_socket;
    char        m_serverIp[IP_CHAR_SIZE];
	size_t 		m_port;
};

static ClientErr InitClientnet (Clientnet* _clientnet, const char* _serverIp, size_t _serverPort);
static ClientErr CheckTransmitionStatus (int _status);
static int Connect (Clientnet* _clientnet, struct sockaddr_in _sin);
/******************************************************/
/************     Public      *************************/
/******************************************************/
Clientnet* ClientnetCreate(const char* _serverIp, size_t _serverPort)
{
    Clientnet* newClientnet = NULL;

    if (NULL == _serverIp)
	{
		return NULL;
	}
	
	if (NULL == (newClientnet = (Clientnet*) malloc (sizeof(Clientnet))))
    {
        return NULL;
    }

    if (CLIENT_SUCCESS != InitClientnet(newClientnet, _serverIp, _serverPort))
	{
		free(newClientnet);
		return NULL;
	}
    return newClientnet;
}

void ClientnetDestroy (Clientnet** _clientnet)
{
    if (NULL != _clientnet && NULL != *_clientnet)
    {
        free(*_clientnet);
        *_clientnet = NULL;
    }
    return;
}

ClientErr ClientnetSendMsg (Clientnet* _clientnet ,char* _msg, size_t _msgSize)
{
    int sentBytes = 0;
    ClientErr status = CLIENT_SUCCESS;
	
	sentBytes = send (_clientnet->m_socket, _msg, _msgSize , 0);
	status = CheckTransmitionStatus(sentBytes);
	return status;
}

ClientErr ClientnetRecieveMsg(Clientnet* _clientnet, char* _buff, size_t _buffSize)
{
	int readBytes = 0;
    ClientErr status = CLIENT_SUCCESS;
	
	readBytes = recv(_clientnet->m_socket, _buff, _buffSize, 0);
    status = CheckTransmitionStatus(readBytes);
	return status;
}

/******************************************************/
/************     Locals      *************************/
/******************************************************/
static ClientErr InitClientnet (Clientnet* _clientnet, const char* _serverIp, size_t _serverPort)
{
	struct sockaddr_in sin;
	
    /* set clientnet data*/
    strcpy(_clientnet->m_serverIp, _serverIp);
    _clientnet->m_port = _serverPort;
    
    /* Set clientnet socket */
    _clientnet->m_socket = socket(AF_INET, SOCK_STREAM , 0);
	if (Connect(_clientnet, sin) == FAILED)
	{	
		/* TODO: add logging */
        perror("connect failed");
		return CLIENT_CONNECTION_ERROR;
	}	
	return CLIENT_SUCCESS;
}

static ClientErr CheckTransmitionStatus (int _status)
{
    if (_status == 0)
	{
		return CLIENT_CLOSE_SOCKET;
	}
	else if (_status < 0)
	{
		return CLIENT_TRANSMITION_FAILED;
	}
    return CLIENT_SUCCESS;
}

static int Connect (Clientnet* _clientnet, struct sockaddr_in _sin)
{
	memset(&_sin, 0, sizeof(_sin));
	
	_sin.sin_family = AF_INET;
	_sin.sin_addr.s_addr = inet_addr(_clientnet->m_serverIp);
	_sin.sin_port = htons(_clientnet->m_port);
	
	if (connect(_clientnet->m_socket, (struct sockaddr*) &_sin, sizeof(_sin)) < 0)
	{
		return FAILED;
	}
	return SUCCESS;
}

