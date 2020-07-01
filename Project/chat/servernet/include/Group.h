#ifndef __GROUP_H__
#define __GROUP_H__

#include <sys/select.h>		/* fd_set */
#include "chatprotocol.h"

typedef struct Group Group ;

/*
	Description -	make pointer to group
	Input		-	no input
	Output		-	a) pointer to group
				 	b) null
	Error		-	null : allocation failed 	  		
*/
Group* GroupCreate() ;

/*
	Description -	creat new group
	Input		-	a) pointer to group
					b) int socket client
					c) pointer to char* ip
					d) pointer to fd_set login users
					e) pointer to create group
	Output		-	SERVER_ERROR / INVALID_GROUP_ID / MULTI_ADDRESS_DEPLETED / SUCCESS
	Error		-	a) SERVER_ERROR - user offline
					b) INVALID_GROUP_ID - group name empty or already exist
					c) MULTI_ADDRESS_DEPLETED - empty ip pool	  		
*/
RespType GroupNew(Group *_groups, CreateGroup *_createGroup, int _socketClient , char *_ip, fd_set *_loginFds) ;

/*
	Description -	join group
	Input		-	a) pointer to group
					b) int socket client
					c) pointer to char* ip
					d) pointer to fd_set login users
					e) pointer to join group
	Output		-	SERVER_ERROR / INVALID_GROUP_ID / SUCCESS
	Error		-	a) SERVER_ERROR - user offline or alreay in the group
					b) INVALID_GROUP_ID - group name empty or not exist	  		
*/
RespType GroupJoin(Group *_groups, JoinGroup *_joinGroup, int _socketClient ,char *_ip, fd_set *_loginFds) ;

/*
	Description -	leave group
	Input		-	a) pointer to group
					b) int socket client
					c) pointer to fd_set login users
					d) pointer to leave group
	Output		-	SERVER_ERROR / INVALID_GROUP_ID / SUCCESS
	Error		-	a) SERVER_ERROR - user offline 
					b) INVALID_GROUP_ID - user not in this group	  		
*/
RespType GroupLeave(Group *_groups, LeaveGroup *_leaveGroup, int _socketClient, fd_set *_loginFds) ;

/*
	Description -	leave all groups
	Input		-	a) pointer to group
					b) int socket client
	Output		-	no output
	Error		-	no error 	  		
*/
void GroupLeaveAll(Group *_groups, int _socketClient) ;

/*
	Description -	list groups
	Input		-	a) pointer to group
					b) int socket client
					c) pointer to name
					d) pointer to fd_set login users					
	Output		-	num of groups
	Error		-	no error 	  		
*/
size_t GroupReqList(Group *_groups, Name *_nameGroups, int _socketClient, fd_set *_loginFds) ;

/*
	Description -	num of groups
	Input		-	a) pointer to group					
	Output		-	num of groups
	Error		-	no error 	  		
*/
size_t GroupSize(Group *_groups) ;

/*
	Description -	destroy group
	Input		-	a) pointer to group					
	Output		-	no output
	Error		-	no error 	  		
*/
void GroupDestroy(Group *_groups) ;

#endif /* __GROUP_H__ */
