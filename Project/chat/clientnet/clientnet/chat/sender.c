#ifndef _DEFAULT_SOURCE
#define _DEFAULT_SOURCE
#endif
#include <stdio.h> /* fgets */ 
#include <string.h> /* memset */
#include <arpa/inet.h> /* struct sockaddr_in*/
#include <errno.h> /* errno, EAGAIN, EWOULDBLOCK*/
#include <unistd.h> /* getpid */ 
#include "sender.h" /* include */
#include "../include/msgque.h" /* msgque send */
#include "../../include/chatprotocol.h" /* MSG typedef */
#include "../../include/protocol.h" /* ProtocolPackMsgData */


#define ADRESS_SIZE 	16
#define TRUE            1		
#define FAILED 			-1
#define ILLIGAL_INPUT    "Illigal input"
#define BUFF_SIZE 		600
#define NAME_SIZE		50

#define ERROR_LOGGED(_errFunc, _err)	if(_errFunc) _errFunc((_err))   



struct ChatSender {
	int 					m_socket;
	char					m_adress[ADRESS_SIZE];
	size_t 					m_port;
	int						m_msgId;
	char					m_buffer[BUFF_SIZE]; 
	char					m_msg[VALUE_LEN];
	struct sockaddr_in 		m_sin;
	char					m_name[NAME_SIZE];
	int						n_nameLen;
};

static NetErr ServerInit(ChatSender* _sender, size_t _port, const char* _groupAdrr, const char* _name, int _msgId);
static NetErr SetRecvSocket(ChatSender* _sender);
static void SetSin(ChatSender* _sender);
static NetErr SendPid(ChatSender* _sender);
static int CreateMsg(ChatSender* _sender, int _msgLen);
static int IsLegalInput(const char* _name, char* _len);
static void ClearStdin();
/******************************************************/
/***************     API      *************************/
/******************************************************/

ChatSender* ChatSenderCreate (size_t _port, const char* _groupAdrr, const char* _name, int _msgId)
{
	ChatSender* newSender = NULL;

	if (NULL == (newSender = (ChatSender*) malloc (sizeof(ChatSender))))
	{
		return NULL;
	}
	
	ServerInit(newSender, _port, _groupAdrr, _name, _msgId);
	printf("Send msessages here\n");
	SendPid(newSender);
	return newSender;
}

void ChatSenderDestroy(ChatSender** _sender)
{
	free(*_sender);
	*_sender = NULL;
	return;
}

NetErr ChatSenderRun(ChatSender* _sender)
{
	char msgLen;
	int bufLen = 0;

	if (NULL == _sender)
	{
		return NET_ERR_NOT_INITIALIZED;
	}

	while (1)
	{
		fgets(_sender->m_msg, VALUE_LEN - 1, stdin);
		if(FAILED == IsLegalInput(_sender->m_msg, &msgLen))
		{
			continue; 
		}
		bufLen = CreateMsg(_sender, (int) msgLen);
		
		ChatSenderSendMessage(_sender, _sender->m_buffer, bufLen);
	}
	return NET_ERR_SUCCESS;
}

NetErr ChatSenderSendMessage(ChatSender* _sender, const char* _msg, int _msgSize)
{
	int sentBytes = 0;
	
	sentBytes = sendto (_sender->m_socket, _msg, _msgSize, 0, (struct sockaddr*) &_sender->m_sin, sizeof(_sender->m_sin));
	
	if (sentBytes < 0)
	{
		perror("failed");
		return NET_ERR_TRANSMITION_FAILED;
	}
	return NET_ERR_SUCCESS;
}

/******************************************************/
/***************     Local      ***********************/
/******************************************************/
static NetErr ServerInit(ChatSender* _sender, size_t _port, const char* _groupAdrr, const char* _name, int _msgId)
{
	_sender->m_port = _port;
	_sender->m_msgId = _msgId;
	strcpy(_sender->m_adress, _groupAdrr);
	strcpy(_sender->m_name, _name);
	_sender->n_nameLen = strlen(_sender->m_name);

	if (NET_ERR_SUCCESS != SetRecvSocket(_sender))
	{
		return NET_ERR_SOCKET_FAILED;
	}
	
	return NET_ERR_SUCCESS;
}

static NetErr SetRecvSocket(ChatSender* _sender)
{
	if ((_sender->m_socket = socket(AF_INET, SOCK_DGRAM , 0)) < 0)
	{
		return NET_ERR_SOCKET_FAILED;
	}
	SetSin(_sender);
	return NET_ERR_SUCCESS;
}

static void SetSin(ChatSender* _sender)
{
    memset(&_sender->m_sin, 0, sizeof(_sender->m_sin));
	_sender->m_sin.sin_family = AF_INET;
	_sender->m_sin.sin_addr.s_addr = inet_addr(_sender->m_adress);
	_sender->m_sin.sin_port = htons(_sender->m_port);
    return;
}

static NetErr SendPid(ChatSender* _sender)
{
	MsgBuf _msg;
	_msg.m_pid = getpid();
	if (ERR_OK != MsgQueWrite(_sender->m_msgId, _msg))
	{
		return NET_ERR_SYS;
	}
	return NET_ERR_SUCCESS;
}

static int CreateMsg(ChatSender* _sender, int _msgLen)
{
	MsgData msgD;
	
	msgD.m_type = MSG_DATA;
	msgD.m_length = 0;
	msgD.m_userName.m_type = NAME;
	msgD.m_userName.m_length = _sender->n_nameLen;
	strcpy(msgD.m_userName.m_value, _sender->m_name);
	msgD.m_message.m_type = MSG;
	msgD.m_message.m_length = _msgLen;
	strcpy(msgD.m_message.m_value, _sender->m_msg);
	msgD.m_message.m_value[_msgLen -1] = '\0';
	return ProtocolPackMsgData(&msgD, _sender->m_buffer);
}

static int IsLegalInput(const char* _name, char* _len)
{
    *_len = strlen(_name);

    if(0 >= *_len)
    {
        printf("%s\n", ILLIGAL_INPUT);
		ClearStdin();
        return FAILED;
    }
    return TRUE;
}

static void ClearStdin()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF) 
    { 

    }
    return;
}