#include <stdlib.h>		/* allocation */
#include <string.h>		/* strcpy , strcat */     
#include <stdio.h>		/* sprintf */
#include "IpHandler.h"	
#include "queue.h"
#include "ADTDefs.h"

/* --------------------------- define ------------------------------ */
#define QUEUE_SIZE		100
#define SIZE_IP			11    
#define IP				"224.0.0." 
#define SIZE_LAN		3
#define NUM_ADDRESS		100
#define LAST_NUM		80

/* --------------------------- struct ------------------------------ */
struct IpHandler{
	Queue *m_ipPool ;	
};

/* --------------------- statements locl func ---------------------- */
static void InitQueue(Queue *_ipPool) ;
static char* CreateIp() ;
static void DestroyIp(void *_ip) ;

/*===================================================================*/
/* ============================= API =============================== */
/*===================================================================*/

/* --------------------- IpHandler Create -------------------------- */
IpHandler* IpHandlerCreate() 
{
	IpHandler *ipHandler ;
	
	ipHandler = (IpHandler*) malloc(sizeof(IpHandler)) ;
	if ( NULL == ipHandler )
	{
		return NULL ;
	}
	
	ipHandler -> m_ipPool = QueueCreate (QUEUE_SIZE);
	if ( NULL == ipHandler -> m_ipPool )
	{
		free(ipHandler) ;
		return NULL ;
	}
	
	InitQueue( ipHandler -> m_ipPool ) ;
	
	return ipHandler ;	
		
}
 
/* ------------------- Ip Handler Ruturn Ip ------------------------- */
void IpHandlerRuturnIp(IpHandler *_ipHandler, char* _ipAddress) 
{
	QueueInsert(_ipHandler->m_ipPool, _ipAddress);
	return ;
}



/* -------------------- Ip Handler Get Ip --------------------------- */
char* IpHandlerGetIp(IpHandler *_ipHandler) 
{
	char *ip ;
	
	if ( QueueRemove(_ipHandler->m_ipPool, (void**) &ip) != ERR_OK )
	{
		return NULL ;
	}
	
	return ip ;
}

/* ------------------- Ip Handler Destroy --------------------------- */
void IpHandlerDestroy(IpHandler *_ipHandler) 
{
	QueueDestroy(_ipHandler->m_ipPool, DestroyIp);
	return ;
}

/*====================================================================*/
/* ========================= local func ============================= */
/*====================================================================*/

/* ------------------------- Init Queue ------------------------------ */
static void InitQueue(Queue *_ipPool) 
{
	char *ip ;
	int i ;
	
	for ( i = 0 ; i < NUM_ADDRESS ; ++i )
	{	
		ip = CreateIp() ;
	
		QueueInsert(_ipPool, ip);
	}	
	
	return ;
}


/* ------------------------ Create Ip ------------------------------- */
static char* CreateIp() 
{
	char *ip ;
	static int lan = LAST_NUM ;
	char numLan[SIZE_LAN] ;
	
	ip = (char*) malloc( SIZE_IP ) ;
	if ( NULL == ip )
	{
		return NULL ;
	}
	
	strcpy( ip , IP ) ;
	
	sprintf( numLan , "%d" , lan++ );
	
	strcat ( ip , numLan ) ;
	
	ip[SIZE_IP-1] = '\0' ;
	
	return ip ;
	
}

/* ---------------------- Destroy Ip ------------------------------- */
static void DestroyIp(void *_ip) 
{
	free ( _ip ) ;
	return ;
}
