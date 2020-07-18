#include "../include/msgque.h"
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
    int msgId = 0;
    MsgBuf msg;
    MsgBuf test;
    
    msg.m_pid = getpid();
    printf("%d\n", msg.m_pid);
    MsgQueCreate(".", &msgId);

    MsgQueWrite(msgId, MSG_CHANNEL, msg);

    MsgQueRead(msgId, MSG_CHANNEL, &test);

    printf("%d\n", test.m_pid);
}