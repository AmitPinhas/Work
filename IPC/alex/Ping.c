/*
 *	Author:				Alex Katz
 *  Creation date:		14.03.2012 (H9-Y21) 
 *  Last modification:	02.09.2012
 * 	Description: 
 * 		MessageQueue PingPong with multiple readers and writers
 * 		Uses special message type as Registrar for Ping processes
 *  	The Registrar acts as a semaphore with each Ping writing a message on startup and removing it prior to exit
 *		At least one Ping has to be run before any Pong
 * 
 * 
 */ 
/* for SYSV IPC getopt & usleep */
#ifndef _XOPEN_SOURCE
#define _XOPEN_SOURCE 500
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <errno.h>
#include <time.h>
/*
 * UI messages
 */
const char USAGE[]	="Usage: %s [-c] [-d] [-v] [-f name] [-n number of messages] [-s msec]\n";
const char ERR_FTOK[]	="ERROR getting key for %s!\n";
const char ERR_MSGGET[]	="ERROR getting queue %s = 0x%8x!\n";
const char ERR_MSGDEL[]	="ERROR deleting queue %s = 0x%8x!\n";
const char ERR_MSGSND[]	="ERROR sending message [%d, %d, %s]!\n";
const char ERR_MSGRCV[]	="ERROR receiving message [%d]!\n";

const char ECHO_SEND[]	="SENT message [%2d, %d, %s]\n";
const char ECHO_RECV[]	="RECV message [%2d, %d, %d, %s]\n";
const char ECHO_DEL[]	="MSGQUE %s = %x marked for deletion\n";
const char ECHO_REG[]	="REGISTER with pid = %d\n";
const char ECHO_UNREG[]	="deREGISTER with pid = %d\n";

/*
 * Defaults
 */
#define MSG_NUM_DEFAULT 16

/*
 * Common definitions
 */
#include "PingPong.h"

/*
 * Registrar message
 */
typedef struct regbuf
{
	long	m_type;
	int 	m_procID;
} regbuf;


int main(int argc, char **argv)
{
	int  i;
	key_t  msgKey;
	int  mQ;
	msgbuf snd;
	msgbuf rcv;
	regbuf reg;
	int	noBytes;

	int  createMQ	= PERMIS;
	int	 deleteMQ	= 0;
	char* msqName	= MSGQUE_NAME_DEFAULT;
	int  noMsgs 	= MSG_NUM_DEFAULT;
	int  sleepTime	= 0;
	int	 verbose	= 0;
	int  opt;

	pid_t pid = getpid();

/*	Parse the options */
	while (-1 != (opt = getopt(argc, argv, "vcdf:n:s:"))) {
		switch (opt) {
		case 'v':	/* verbose (echo) */
			verbose = 1;
			break;
		case 'c':	/* MsgQue create flag */
			createMQ |= IPC_CREAT | IPC_EXCL;
			break;
		case 'd':	/* MsgQue delete flag */
			deleteMQ = 1;
			break;
		case 'f':	/* MsgQue name */
			msqName = optarg;
			break;
		case 'n':	/* number of messages to send */
			noMsgs = atoi(optarg);
			break;
		case 's':	/* millisecond to sleep between messages */
			sleepTime = atoi(optarg) * 1000;
			break;
		default: /* '?' */
			fprintf(stderr, USAGE, argv[0]);
			return EXIT_FAILURE;
		}
	}


/*  make the key */
	if (-1 == (msgKey = ftok(msqName, 1))) {
		fprintf(stderr, ERR_FTOK, msqName);
		return errno;
	}

/*  create or open message queue */
	if (-1 == (mQ = msgget(msgKey, createMQ))) {
		fprintf(stderr, ERR_MSGGET, msqName, msgKey);
		return errno;
	}

/*  register Ping with the message queue */
	if (verbose)
		fprintf(stdout, ECHO_REG, pid);

	reg.m_type  = MSG_TYPE_REGISTRAR;
	reg.m_procID= pid;
	if (-1 == msgsnd(mQ, &reg, sizeof(reg) - sizeof(reg.m_type), IPC_NOWAIT)) {
		fprintf(stderr, ERR_MSGSND, (int)reg.m_type, reg.m_procID, MSGQUE_REGISTRAR);
		return errno;
	}
		
/*  write messages to the queue and echo to the screen */
	/* setup the message data */
	snd.m_type	= MSG_TYPE_PING;
	snd.m_procID= (long) pid;

	for (i=1; i<=noMsgs; i++) {
		/* make the message */
		sprintf(snd.m_message, "Message #%2d", i);

		/* message size is without the message type */
		if (-1 == msgsnd(mQ, &snd, strlen(snd.m_message)+sizeof(snd.m_procID), 0)) {
			fprintf(stderr, ERR_MSGSND, (int)snd.m_type, snd.m_procID, snd.m_message);
			return errno;
		}
		
		/* echo the message to stdout and sleep a while */
		if (verbose)
			fprintf(stdout, ECHO_SEND, (int)snd.m_type, snd.m_procID, snd.m_message);
			
			
		/* read the response and echo it */
		if (-1 == (noBytes = msgrcv(mQ, &rcv, sizeof(rcv)-sizeof(rcv.m_type), MSG_TYPE_PONG, MSG_NOERROR))) {
			fprintf(stderr, ERR_MSGRCV, MSG_TYPE_PONG);
			return errno;
		}
		noBytes -= sizeof(rcv.m_procID);/* adjust noBytes with m_procID */
		rcv.m_message[noBytes] = '\0';	/* make sure the message is null-terminated */
		if (verbose)
			fprintf(stdout, ECHO_RECV, (int)rcv.m_type, rcv.m_procID, noBytes, rcv.m_message);

		/* simulate some work */
		if (sleepTime)
			usleep(sleepTime);
	}

/* we are done - remove message from REGISTRAR */
	if (-1 == msgrcv(mQ, &reg, sizeof(reg) - sizeof(reg.m_type), MSG_TYPE_REGISTRAR, MSG_NOERROR)) {
		fprintf(stderr, ERR_MSGRCV, MSG_TYPE_REGISTRAR);
		return errno;
	}
	
	if (verbose)
		fprintf(stdout, ECHO_UNREG, reg.m_procID);

/*  delete the message queue if requested */
	if (deleteMQ) {
		if (-1 == msgctl(mQ, IPC_RMID, NULL))
			fprintf(stderr, ERR_MSGDEL, msqName, msgKey);

		if (verbose)
			fprintf(stdout, ECHO_DEL, msqName, msgKey);
	}

	return 0;
}
