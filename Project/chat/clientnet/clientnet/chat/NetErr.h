#ifndef __NET_ERR_H__
#define __NET_ERR_H__

typedef enum NetErr {
    NET_ERR_SUCCESS,
    NET_ERR_NOT_INITIALIZED,            /* server is not intilized */
    NET_ERR_ALLOCATION_FAILED,          /* failed to allocate space for new client */
    NET_ERR_SERVER_BUSY,                /* To much clients logged in */
    NET_ERR_SYS,                        /* System call failed */
    NET_ERR_TRANSMITION_FAILED,         /* Failed to send messgae */
    NET_ERR_SOCKET_CLOSED,              /* Socket closed by client */
    NET_ERR_SOCKET_TIMEOUT,             /* Socket reached timeout given by user */
    NET_ERR_SOCKET_FAILED               /* Socket define failed */

}NetErr;

#endif /* NetErr.h */