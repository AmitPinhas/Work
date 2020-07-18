#ifndef _XOPEN_SOURCE
#define _XOPEN_SOURCE 500
#endif
#include <stdio.h> /* fprintf, open, close */
#include <stdlib.h> /* itoa */
#include <unistd.h> /* usleep, getpwd */
#include <fcntl.h> /* open, macro */
#include <string.h> /* strcat */
#include <sys/msg.h> /* msg types */ 
#include "../include/msgque.h"

#define MSQ_PERMISSION  0666
#define MSG_FAILED      -1
#define MSG_CHANNEL     12

static key_t CreateKey(const char* _path);
/******************************************************/
/************     Public      *************************/
/******************************************************/
ErrDefs MsgQueCreate(const char* _path, int* _msgId)
{
    key_t key;
	int id = 0;

    key = CreateKey(_path);
    if ((id = msgget(key, MSQ_PERMISSION | IPC_CREAT)) == MSG_FAILED)
    {
        return ERR_SYS_ERROR;
    }
	*_msgId = id;
    return ERR_OK;
}

ErrDefs MsgQueDestroy (int _msgId)
{
    if (msgctl(_msgId, IPC_RMID, NULL) == MSG_FAILED) 
    {
        return ERR_SYS_ERROR;
    }
    return ERR_OK;
}

ErrDefs MsgQueWrite(int _msgId, MsgBuf _buff)
{
    _buff.m_type = MSG_CHANNEL;
	/* Write and send a msg */
    if (msgsnd(_msgId, &_buff, sizeof(_buff.m_pid), 0) == MSG_FAILED)
	{
		perror("msgrcv");
		return ERR_SYS_ERROR;
	}
	return ERR_OK;
}

ErrDefs MsgQueRead(int _msgId, MsgBuf* _buff)
{
	if (msgrcv(_msgId, _buff, sizeof(_buff->m_pid), MSG_CHANNEL, 0) == MSG_FAILED)
	{
		perror("msgrcv");
		return ERR_SYS_ERROR;
	}
	return ERR_OK;
}

/******************************************************/
/************     Locals      *************************/
/******************************************************/
static key_t CreateKey(const char* _path)
{
	key_t key;
	
	key = ftok(_path, 'A');
	return key;
}