#ifndef __PINGPONG_H__
#define __PINGPONG_H__

#define PING_TYPE     11
#define PONG_TYPE     30
#define EOF_TYPE      10
#define EOF_MSG       "bye bye"
#define FLAG_FTOK     'B'
#define FLAG_MSG_GET  0644


/* ----- MyMsgbuf ----- */
typedef struct{
    long mtype;
    char mtext[200];
}MyMsgbuf;


#endif /* __PINGPONG_H__ */
