#ifndef __PINGPONG_H__
#define __PINGPONG_H__

#define MSGQUE_NAME_DEFAULT "ping-pong-MSQ"
#define MSGQUE_REGISTRAR	"REGISTRAR"
#define PERMIS 0666

#define MSG_LEN 			252
/* The values of message types are imporant - the registrar MUST be between other two */
#define MSG_TYPE_PING		  5
#define MSG_TYPE_REGISTRAR	  7
#define MSG_TYPE_PONG	  	  9

typedef struct msgbuf
{
	long  m_type;
	pid_t m_procID;
	char  m_message[MSG_LEN];
} msgbuf;

#endif /* __PINGPONG_H__ */
