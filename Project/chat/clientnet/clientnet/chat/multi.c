#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif
#include <string.h> /* memset */
#include <stdio.h> /* perror printf */
#include <arpa/inet.h> /* struct sockaddr_in*/
#include <netinet/in.h>
#include <errno.h> /* errno, EAGAIN, EWOULDBLOCK*/
#include <unistd.h> /* getpid */ 
#include "multi.h" /* include */
#include "../include/msgque.h" /* msgque send */
#include "../../include/chatprotocol.h" /* MSG typedef */
#include "../../include/protocol.h" /* ProtocolUnpackMsgData */

#define ADRESS_SIZE 	16
#define FAILED 			-1
#define BUFF_SIZE		500 /* VALUE LEN * 2*/
#define SERVER_ON		1

#define ERROR_LOGGED(_errFunc, _err)	if(_errFunc) _errFunc((_err))   

int g_run = SERVER_ON;

struct Multicast {
	int 					m_recvSocket;
	char					m_adress[ADRESS_SIZE];
	size_t 					m_port;
	char					m_buffer[BUFF_SIZE]; 
	struct sockaddr_in 		m_sin;
	int						m_msgId;
};

static NetErr MultiInit(Multicast* _multi);
static NetErr SetRecvSocket(Multicast* _multi);
static void SetSin(Multicast* _multi);
static NetErr Setmerq(Multicast* _multi);
static NetErr RecieveMessage(Multicast* _multi, int _sock);
static NetErr SendPid(Multicast* _multi);
static void PrintMsg(Multicast* _multi);
/******************************************************/
/***************     API      *************************/
/******************************************************/

Multicast* MultiCreate (size_t _port, const char* _groupAdrr, int _msgId)
{
	Multicast* newMulti = NULL;

	if (NULL == _groupAdrr)
	{
		return NULL;
	}
	
	if (NULL == (newMulti = (Multicast*) malloc (sizeof(Multicast))))
	{
		return NULL;
	}
	
	newMulti->m_port = _port;
	newMulti->m_msgId = _msgId;
	strcpy(newMulti->m_adress, _groupAdrr);
	MultiInit(newMulti);
	SendPid(newMulti);
	return newMulti;
}

void MultiDestroy(Multicast** _multi)
{
	free(*_multi);
	*_multi = NULL;
	return;
}

NetErr MultiRun(Multicast* _multi)
{
	if (NULL == _multi)
	{
		return NET_ERR_NOT_INITIALIZED;
	}
	while (g_run)
	{
		RecieveMessage(_multi, _multi->m_recvSocket);
	}
	return NET_ERR_SUCCESS;
}

/******************************************************/
/***************     Local      ***********************/
/******************************************************/
static NetErr MultiInit(Multicast* _multi)
{
	/* Setting Multi values and bind port */	
	if (NET_ERR_SUCCESS != SetRecvSocket(_multi))
	{
		return NET_ERR_SOCKET_FAILED;
	}
	if (NET_ERR_SUCCESS != Setmerq(_multi))
	{
		return NET_ERR_SOCKET_FAILED;
	}
	return NET_ERR_SUCCESS;
}

static NetErr SetRecvSocket(Multicast* _multi)
{
	int optval = 1;
	_multi->m_recvSocket = socket(AF_INET, SOCK_DGRAM , 0);

	SetSin(_multi);
	/* Release socket immidietly when close */
	if (setsockopt(_multi->m_recvSocket, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)) < 0 )
	{
		perror("socket failed");
		return NET_ERR_SOCKET_FAILED; 
	}

	if ((bind(_multi->m_recvSocket, (struct sockaddr*) &_multi->m_sin, sizeof(_multi->m_sin))) < 0)
	{
		perror("bind failed");
		return NET_ERR_SOCKET_FAILED;
	}
	return NET_ERR_SUCCESS;
}

static void SetSin(Multicast* _multi)
{
    memset(&_multi->m_sin, 0, sizeof(_multi->m_sin));
	_multi->m_sin.sin_family = AF_INET;
	_multi->m_sin.sin_addr.s_addr = inet_addr(_multi->m_adress);
	_multi->m_sin.sin_port = htons(_multi->m_port);
    return;
}

static NetErr Setmerq(Multicast* _multi)
{
	struct ip_mreq mreq;

	memset(&mreq, 0, sizeof(struct ip_mreq));
	mreq.imr_multiaddr.s_addr = inet_addr(_multi->m_adress);
    mreq.imr_interface.s_addr = htonl(INADDR_ANY);
    if (setsockopt(_multi->m_recvSocket, IPPROTO_IP, IP_ADD_MEMBERSHIP, (char*) &mreq, sizeof(mreq)) < 0){
        perror("setsockopt");
        return NET_ERR_SOCKET_FAILED;
    }
	return NET_ERR_SUCCESS;
}

static NetErr RecieveMessage(Multicast* _multi, int _sock)
{
	int readBytes = 0;
	int addrLen = sizeof(_multi->m_sin);
	readBytes = recvfrom(_multi->m_recvSocket, _multi->m_buffer, sizeof(MsgData), 0 ,(struct sockaddr *)  &_multi->m_sin,(socklen_t*) &addrLen);

	if (readBytes == 0)
	{
		/*ERROR_LOGGED(_multi->m_sd.m_errorFunc, ERR_SOCKET_CLOSED);*/
		return NET_ERR_SOCKET_CLOSED;
	}
	else if (readBytes < 0)
	{
		/*ERROR_LOGGED(_multi->m_sd.m_errorFunc, ERR_SYS);*/
		return NET_ERR_SOCKET_CLOSED;
	}
	_multi->m_buffer[readBytes] = '\0';
	PrintMsg(_multi);
	return NET_ERR_SUCCESS;
}

static NetErr SendPid(Multicast* _multi)
{
	MsgBuf _msg;
	_msg.m_pid = getpid();

	if (ERR_OK != MsgQueWrite(_multi->m_msgId, _msg))
	{
		return NET_ERR_SYS;
	}
	return NET_ERR_SUCCESS;
}

static void PrintMsg(Multicast* _multi)
{
	MsgData msgD;

	ProtocolUnpackMsgData(&msgD, _multi->m_buffer);
	printf("%s: %s\n",msgD.m_userName.m_value, msgD.m_message.m_value);
	return;
}





















