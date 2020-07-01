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

#include "PingPong.h"

const char USAGE[]		="Usage: %s [-v] [-f name] [-s msec]\n";
const char ERR_FTOK[]	="ERROR getting key for %s!\n";
const char ERR_MSGGET[]	="ERROR getting queue %s = 0x%8x!\n";
const char ERR_MSGSND[]	="ERROR sending message [%d, %d, %s]!\n";
const char ERR_MSGRCV[]	="ERROR receiving message ";

const char ECHO_SEND[]	="SENT message [%2d, %d, %s]\n";
const char ECHO_RECV[]	="RECV message [%2d, %d, %d, %s]\n";
const char ECHO_NOMSG[]	="DONE neither messages nor Ping[s]\n";
const char ECHO_DONE[]	="DONE after %d messages\n";

int main(int argc, char **argv)
{
	key_t	msgKey;
	int  	mQ;
	msgbuf	snd;
	msgbuf	rcv;
	int		noBytes;
	int 	msgCount = 0;

	char* msqName	= MSGQUE_NAME_DEFAULT;
	int  sleepTime	= 0;
	int	 verbose	= 0;
	int  opt;
	long msgTypeRcv	= - MSG_TYPE_REGISTRAR;

	pid_t pid = getpid();

/*	Parse the options */
    while (-1 != (opt = getopt(argc, argv, "vf:s:"))) {
        switch (opt) {
		case 'v':	/* verbose (echo) */
			verbose = 1;
			break;
        case 'f':	/* MsgQue name */
            msqName = optarg;
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
	if (-1 == (mQ = msgget(msgKey, PERMIS))) {
		fprintf(stderr, ERR_MSGGET, msqName, msgKey);
		return errno;
	}

/*	read the messages and echo them back
 *  check registrar if not empty
 */
	/* setup the message data */
	snd.m_type	= MSG_TYPE_PONG;
	snd.m_procID= pid;
	
	while (1) {
		/* read message from PING or REGISTRAR */
		if (-1 == (noBytes = msgrcv(mQ, &rcv, sizeof(rcv)-sizeof(rcv.m_type),
									msgTypeRcv, IPC_NOWAIT | MSG_NOERROR))) {
			if (errno == ENOMSG) {
				if (verbose)
					fprintf(stdout, ECHO_NOMSG);
				break;
			} else {
				perror(ERR_MSGRCV);
				return errno;
			}
		}

		/* return back REGISTRAR message */
		if (rcv.m_type == MSG_TYPE_REGISTRAR) {
			if (-1 == msgsnd(mQ, &rcv, noBytes, IPC_NOWAIT)) {
				fprintf(stderr, ERR_MSGSND, (int)rcv.m_type, rcv.m_procID, MSGQUE_REGISTRAR);
				return errno;
			}
			
			if (verbose)
				fprintf(stdout, ECHO_SEND, (int)rcv.m_type, rcv.m_procID, MSGQUE_REGISTRAR);
		} else {
		/* normal message -> echo it back to sender queue */
			msgCount++;
			noBytes -= sizeof(rcv.m_procID);/* adjust noBytes with m_procID */
			rcv.m_message[noBytes] = '\0';	/* make sure the message is null-terminated */
			
			if (verbose)
				fprintf(stdout, ECHO_RECV, (int)rcv.m_type, rcv.m_procID, noBytes, rcv.m_message);
	
			/* copy the request into the response */
			memcpy(snd.m_message, rcv.m_message, noBytes+1);
			
			/* message size is without the message type */
			noBytes += sizeof(snd.m_procID);
			if (-1 == msgsnd(mQ, &snd, noBytes, 0)) {
				fprintf(stderr, ERR_MSGSND, (int)snd.m_type, snd.m_procID, snd.m_message);
				return errno;
			}
			/* echo the message to stdout */
			if (verbose)
				fprintf(stdout, ECHO_SEND, (int)snd.m_type, snd.m_procID, snd.m_message);
		}

		/* sleep awhile */
		usleep(sleepTime);
	}
	
	/* we are done */
	if (verbose)
		fprintf(stderr, ECHO_DONE, msgCount);

	return errno;
}
