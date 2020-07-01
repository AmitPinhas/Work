#ifndef __IPHANDLER_H__
#define __IPHANDLER_H__


typedef struct IpHandler IpHandler ;

/*
	Description -	make pointer to ipHandler
	Input		-	no input
	Output		-	a) pointer to ipHandler
				 	b) null
	Error		-	null : allocation failed 	  		
*/
IpHandler* IpHandlerCreate() ;

/*
	Description -	return ip to ip pool
	Input		-	a) pointer to ip pool
					b) pointer to char ip address
	Output		-	no output
	Error		-	no error  		
*/
void IpHandlerRuturnIp(IpHandler *_ipHandler, char* _ipAddress) ;

/*
	Description -	get ip from ip pool
	Input		-	a) pointer to ip pool
	Output		-	pointer to char ip / null
	Error		-	null : empty ip pool 		
*/
char* IpHandlerGetIp(IpHandler *_ipHandler) ;

/*
	Description -	destroy ipHandler
	Input		-	a) pointer to ipHandler					
	Output		-	no output
	Error		-	no error 	  		
*/
void IpHandlerDestroy(IpHandler *_ipHandler) ;

#endif /* __IPHANDLER_H__ */
