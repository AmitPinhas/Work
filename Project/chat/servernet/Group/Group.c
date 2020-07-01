#include <stdlib.h>			/* allocation */
#include <string.h>			/* strlen, strcmp, strcpy */
#include "list.h"
#include "Group.h"
#include "HashMap.h"
#include "IpHandler.h"
#include "list_functions.h"

/* --------------------------- define ------------------------------ */
#define HASH_CAPACITY	5
#define NOT_EQUAL		0
#define EQUAL_KEY		1 
#define EQUAL			0 
#define SIZE_IP			11    
#define CONTINUE		1     
#define EMPTY_NAME		0 
#define EMPTY_GROUP		0

/* --------------------------- struct ------------------------------ */
struct Group{
	HashMap		*m_groups ;
	IpHandler	*m_ipPool ;
};

typedef struct{
	char m_groupName[VALUE_LEN] ;
	char m_ip[SIZE_IP] ;
	List *m_socketClients ;
}GroupArgs;

typedef struct{
	Group	*m_group ;
	int		m_socketClient ;	
}ContextLeaveAll;

typedef struct{
	int		m_index ;
	Name*	m_nameGroups ;
}GroupListArgs;

/* --------------------- statements locl func ---------------------- */
static	size_t	HashGroup(const void* _groupName) ;
static	int		EqualGroup(const void* _userGroup1, const void* _userGroup2) ;
static	GroupArgs* CreateGroupArgs(CreateGroup *_createGroup, int _socketClient, char *_ip) ;
static	RespType RespTypeError(MapResult _error) ;
static	int		InsertGroupName(const void* _groupName, void* _GroupArgs, void* _groupListArgs) ;
static	int		FindSocketClient(void * _element, void* _mySocketClient);
static	int		LeaveAllGroups(const void* _groupName, void* _groupArgs, void* _contextLeaveAll);
static	int*	CreateSocket(int _socketClient);
static	void	DestroyGroupArgs(void *_groupArgs) ;
static	void	DestroySocket(void *_socket) ;

/*===================================================================*/
/* ============================= API =============================== */
/*===================================================================*/

/* ------------------------- Group Create -------------------------- */
Group* GroupCreate()
{
	Group *group ;
	
	group = (Group*) malloc(sizeof(Group)) ;
	if ( NULL == group )
	{
		return NULL ;
	}
	
	group -> m_groups = HashMapCreate(HASH_CAPACITY, HashGroup, EqualGroup);
	if ( NULL == group -> m_groups )
	{
		free(group) ;
		return NULL ;
	}
	
	group -> m_ipPool = IpHandlerCreate() ;
	if ( NULL == group -> m_ipPool )
	{
		HashMapDestroy(&(group -> m_groups), NULL, NULL) ;
		free(group) ;
		return NULL ;
	}
	
	return group ;	
}

/* ---------------------- Group Destroy ------------------------- */
void GroupDestroy(Group *_groups) 
{
	IpHandlerDestroy(_groups -> m_ipPool) ;
	HashMapDestroy(&(_groups -> m_groups), NULL, DestroyGroupArgs);
	return ;
}

/* ------------------------ Group New --------------------------- */
RespType GroupNew(Group *_groups, CreateGroup *_createGroup, int _socketClient , char *_ip, fd_set *_loginFds)
{	
	GroupArgs *groupArgs ;
	MapResult resultMap ;
	char *ip ;
	
	if ( !(FD_ISSET( _socketClient , _loginFds)) )
	{
		return SERVER_ERROR ;
	}
	
	if ( EMPTY_NAME == strlen( _createGroup->m_groupName.m_value ) )
	{
		return INVALID_GROUP_ID ;
	}
	
	resultMap = HashMapFind(_groups->m_groups,_createGroup->m_groupName.m_value, (void**)&groupArgs);	
	if ( MAP_SUCCESS == resultMap )
	{
		return INVALID_GROUP_ID ;
	}
	
	ip = IpHandlerGetIp(_groups->m_ipPool) ;
	if ( NULL == ip )
	{
		return MULTI_ADDRESS_DEPLETED ;
	}
	
	groupArgs = CreateGroupArgs(_createGroup, _socketClient, ip) ;
	
	if ( (resultMap = HashMapInsert(_groups->m_groups, groupArgs->m_groupName, groupArgs)) != MAP_SUCCESS)
	{
		return RespTypeError( resultMap ) ;
	}
	
	strcpy ( _ip, ip ) ;
	
	return SUCCESS ;
}


/* -------------------- Group Req List ---------------------------- */
size_t GroupReqList(Group *_groups, Name *_nameGroups, int _socketClient, fd_set *_loginFds)
{
	GroupListArgs groupListVar ;

	if ( !(FD_ISSET( _socketClient , _loginFds)) )
	{
		return SERVER_ERROR ;
	}
	
	groupListVar.m_index		= 0 ;
	groupListVar.m_nameGroups	= _nameGroups ;
	
	return HashMapForEach(_groups->m_groups, InsertGroupName, &groupListVar) ;
}


/* ---------------------- Group Join ------------------------------ */
RespType GroupJoin(Group *_groups, JoinGroup *_joinGroup, int _socketClient , char *_ip, fd_set *_loginFds) 
{
	MapResult resultMap ;
	GroupArgs *groupArgs ;	
	ListItr beginItr, removeItr, endItr ; 
	int *socketClient ;	

	if ( !(FD_ISSET( _socketClient , _loginFds)) )
	{
		return SERVER_ERROR ;
	}
	
	resultMap = HashMapFind(_groups->m_groups,_joinGroup->m_groupName.m_value, (void**)&groupArgs);
	if ( resultMap != MAP_SUCCESS )
	{	
		return INVALID_GROUP_ID ;
	}
	else
	{
		beginItr	= ListItrBegin( groupArgs->m_socketClients );
		endItr		= ListItrEnd( groupArgs->m_socketClients );
		removeItr = ListItrFindFirst(beginItr, endItr, FindSocketClient, &_socketClient);
		if ( ! ListItrEquals(removeItr, endItr) )
		{		
			return SERVER_ERROR ; 
		}	
		strcpy( _ip, groupArgs -> m_ip ) ;
		socketClient = CreateSocket( _socketClient ) ;
		ListPushHead(groupArgs->m_socketClients, socketClient);
		return SUCCESS ;
	}		
}


/* --------------------------- Group Leave ------------------------ */
RespType GroupLeave(Group *_groups, LeaveGroup *_leaveGroup, int _socketClient, fd_set *_loginFds) 
{
	MapResult resultMap ;
	GroupArgs *groupArgs ;	
	ListItr beginItr, removeItr, endItr; 

	if ( !(FD_ISSET( _socketClient , _loginFds)) )
	{
		return SERVER_ERROR ;
	}
	
	resultMap = HashMapFind(_groups->m_groups,_leaveGroup->m_groupName.m_value, (void**)&groupArgs);
	if ( resultMap != MAP_SUCCESS )
	{
		return INVALID_GROUP_ID ;
	}
	else
	{	
		beginItr	= ListItrBegin( groupArgs->m_socketClients );
		endItr		= ListItrEnd( groupArgs->m_socketClients );
		removeItr = ListItrFindFirst(beginItr, endItr, FindSocketClient, &_socketClient);
		if ( ! ListItrEquals(removeItr, endItr) )
		{ 
			ListItrRemove(beginItr);
			
			if ( EMPTY_GROUP == ListSize(groupArgs->m_socketClients) )
			{
				HashMapRemove(_groups->m_groups, _leaveGroup->m_groupName.m_value, (void**)&groupArgs);
				IpHandlerRuturnIp(_groups->m_ipPool, groupArgs -> m_ip) ;
			}
			return SUCCESS ;			
		}		
		else
		{
			return INVALID_GROUP_ID ;
		}
	}		
}



/* ------------------ Group Leave All --------------------- */
void GroupLeaveAll(Group *_groups, int _socketClient) 
{
	ContextLeaveAll context ;
	context.m_group = _groups ;
	context.m_socketClient = _socketClient ;
	HashMapForEach(_groups->m_groups, LeaveAllGroups, &context);
		
	return ;
}

/* ------------------ Group Size -------------------------- */
size_t GroupSize(Group *_groups) 
{
	return HashMapSize(_groups->m_groups);
}
/*====================================================================*/
/* ========================= local func ============================= */
/*====================================================================*/

/* -------------------------- Hash Group ----------------------------- */
size_t HashGroup(const void* _groupName) 
{
	int sum = 0, i ;
	char *groupName = (char*)_groupName ;
	
	for ( i = 0 ; groupName[i] != '\0' ; ++i )
	{
		sum += groupName[i] ;
	}
	
	return sum ;
}


/* ------------------------- Equal Group ----------------------------- */
int EqualGroup(const void* _userGroup1, const void* _userGroup2) 
{

	if ( EQUAL ==  ( strcmp((char*)_userGroup1, (char*)_userGroup2) ) ) 
	{
		return EQUAL_KEY ;
	}
	
	return NOT_EQUAL ;
	
}


/* ------------------- Create Group Args ---------------------------- */
static GroupArgs* CreateGroupArgs(CreateGroup *_createGroup, int _socketClient, char *_ip) 
{
	GroupArgs *groupArgs ;
	int *socketClient ;
	
	socketClient = (int*) malloc(sizeof(int) );
	if ( NULL == socketClient )
	{
		return NULL ;
	}
	
	*socketClient = _socketClient ;
	
	groupArgs = (GroupArgs*) malloc(sizeof(GroupArgs)) ;
	if ( NULL == groupArgs )
	{
		return NULL ;
	}
	
	strcpy( groupArgs->m_groupName , _createGroup->m_groupName.m_value ) ;
	strcpy( groupArgs->m_ip, _ip ) ;
	
	groupArgs -> m_socketClients = ListCreate();
	if ( NULL == groupArgs -> m_socketClients )
	{
		free(groupArgs) ;
		return NULL ;
	}
	
	ListPushHead(groupArgs -> m_socketClients, socketClient);
	
	return groupArgs ;
}


/* ---------------------- Sign Up Error -------------------------- */
static RespType RespTypeError(MapResult _error) 
{
	switch(_error)
	{
		case MAP_KEY_DUPLICATE_ERROR	:
											return EXISTING_USERNAME ;
		case MAP_KEY_NULL_ERROR     	:
											return INVALID_USERNAME ;
		case MAP_KEY_NOT_FOUND_ERROR    :
											return INVALID_USERNAME ;										
		default                     	:
											return SERVER_ERROR	;										
	}
}


/* ------------------- Insert Group Name ----------------------- */
int	InsertGroupName(const void* _groupName, void* _GroupArgs, void* _groupListArgs) 
{
	GroupListArgs *groupListVar = (GroupListArgs*)_groupListArgs ;
	int index = groupListVar -> m_index ;
	Name *nameGroups = groupListVar -> m_nameGroups ;
	char *groupName = (char*)_groupName ;
	
	nameGroups[index].m_type	= NAME ;
	nameGroups[index].m_length	= strlen( groupName ) ;
	strcpy ( nameGroups[index].m_value , groupName ) ; 
	
	groupListVar -> m_index++ ;
			
	return CONTINUE ;
}


/* ----------------- Find Socket Client ----------------------- */
static int FindSocketClient(void * _element, void* _mySocketClient)
{
	return ( (*((int*)_element)) == (*((int*)_mySocketClient)) ) ;
}


/* ------------------ Leave All Groups ------------------------ */
static int	LeaveAllGroups(const void* _groupName, void* _groupArgs, void* _contextLeaveAll)
{
	ListItr removeItr, beginItr, endItr ;
	GroupArgs *groupArgs ;	
	beginItr	= ListItrBegin( ((GroupArgs*)_groupArgs)->m_socketClients );
	endItr		= ListItrEnd( ((GroupArgs*)_groupArgs)->m_socketClients );
	
	removeItr = ListItrFindFirst(beginItr, endItr, FindSocketClient, &((ContextLeaveAll*)_contextLeaveAll)->m_socketClient);	
	if ( ! ListItrEquals(removeItr, endItr) )
	{
		ListItrRemove(removeItr);
		if ( EMPTY_GROUP == ListSize(((GroupArgs*)_groupArgs)->m_socketClients) )
		{	
			HashMapRemove(((ContextLeaveAll*)_contextLeaveAll)->m_group->m_groups, ((GroupArgs*)_groupArgs)->m_groupName, (void**)&groupArgs);
			IpHandlerRuturnIp(((ContextLeaveAll*)_contextLeaveAll)->m_group->m_ipPool, groupArgs -> m_ip) ;
		}
	}			
	
	return CONTINUE ;
}


/* ----------------------- Create Socket --------------------- */
static int* CreateSocket(int _socketClient)
{
	int *socketClient ;
	
	socketClient = (int*) malloc(sizeof(int) );
	if ( NULL == socketClient )
	{
		return NULL ;
	}
	
	*socketClient = _socketClient ;
	
	return socketClient ;
}

/* ------------------- Destroy Socket ----------------------- */
static void	DestroySocket(void *_socket) 
{
	free ( _socket ) ;
	return ;
}
/* ------------------- Destroy GroupArgs ----------------- */
static void	DestroyGroupArgs(void *_groupArgs) 
{
	GroupArgs *groupArgs = (GroupArgs*)_groupArgs ;

	ListDestroy(&(groupArgs -> m_socketClients), DestroySocket);	
	free ( _groupArgs ) ;
	
	return ;
}
