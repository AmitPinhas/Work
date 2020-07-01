#ifndef _XOPEN_SOURCE
#define _XOPEN_SOURCE 500
#endif

#include <stdlib.h>			/* allocation */
#include <stdio.h>			/* file */
#include <string.h>			/* strcpy */
#include <sys/select.h>		/* fd_set */
#include <signal.h>			/* sigaction */
#include <unistd.h>			/* write */
#include "ServerManager.h"
#include "User.h"
#include "protocol.h" 
#include "Group.h"
#include "log.h"

/* --------------------------- define ------------------------------ */
#define BIT_TYPE				0
#define SERVER_PORT				2727
#define SIZE_QUEUE				1000
#define MAX_CLIENTS				1000
#define LENGTH_RESPONSE			1
#define SIZE_IP					11     
#define RESP_GROUPS_LIST_LENGTH	1
#define EMPTY					0
#define RESP_GROUP_LENGTH		0
#define SIGN_UP_FILE            "sign_up.txt"
#define LOG_FILE                "log.txt"
#define OK                      1
#define FAIL					0

/* ---------------------------- macro ------------------------------ */
#define SERVER_NET(Server)	(((ServerManager*)(Server))->m_serverNet)
#define USERS(Server)		(((ServerManager*)(Server))->m_users)
#define GROUPS(Server)		(((ServerManager*)(Server))->m_groups)
#define LOGIN_FDS(Server)	(((ServerManager*)(Server))->m_loginFds) 

/* --------------------------- struct ------------------------------ */
struct ServerManager{
	Server *m_serverNet ;
	User   *m_users ;
	Group  *m_groups ;
	fd_set	m_loginFds ;
};


/*-------------------------- global var ---------------------------- */
static ServerManager *g_serverManager ;
static struct sigaction m_oldAction ;

/* --------------------- statements locl func ---------------------- */
static void ServerSignUp(void *_serverManager, int _socketClient, char *_msg, int *_sizeMsg , char *_response) ;
static void InitServerNetArgs(ServerManager* _serverManager, ServerArgs *_serverNetArgs) ;
static void InitResponse(Response *_response, RespType _result) ;
static void ServerLogIn(void *_serverManager, int _socketClient, char *_msg, int *_sizeMsg, char *_response) ;
static void ServerCreateGroup(void *_serverManager, int _socketClient, char *_msg, int *_sizeMsg , char *_response) ;
static void InitResponseGroup(RespGroup *_respGroup, RespType _result, char *_ip) ;
static void InitIpNumber(IpNumber *_ipNumber, char *_ip) ;
static void ServerReqGroupList(void *_serverManager, int _socketClient, char *_msg, int *_sizeMsg , char *_response)  ;
static void	InitRespGroupsList(RespGroupsList *_respGroupsList, size_t _sizeGroup) ;
static void	ServerJoinGroup(void *_serverManager, int _socketClient, char *_msg, int *_sizeMsg , char *_response) ;
static void	ServerLeaveGroup(void *_serverManager, int _socketClient, char *_msg, int *_sizeMsg , char *_response) ;
static void	ServerLogOut(void *_serverManager, int _socketClient, char *_msg, int *_sizeMsg , char *_response) ;
static int	ServerClientLeft(int _socketClient, void* _serverManager) ;
static int	MsgReciveAndSend(void *_serverManager, int _socketClient, char *_msg, int _sizeMsg) ;
static void SaveDetails(char *_userName, char *_password, char _response) ;
static void	LogResponse(char _response);
static void CheckTypeReciveMsg(void *_serverManager, int _socketClient, char *_msg, char *_responseMsg, int *_sizeResponseMsg ) ;
static FILE* CleanLogFile() ;
static void LogAction( char *_action ) ;
static void LogUserName( char *_userName ) ;
static void LogPassword( char *_password ) ;
static void LogGroupName( char *_groupName ) ;
static void LogIp( char *_ip ) ;
static int InitSigintDestroy( ServerManager *_serverManager ) ;
static void sigintHandler(int _sig ); 
		
/* ============================== API ============================= */

/* ---------------------- Server Manager Create ------------------- */
ServerManager* ServerManagerCreate() 
{
	ServerManager *serverManager ;
	ServerArgs serverNetArgs ;	
	
	if ( NULL == CleanLogFile() )
	{
		return NULL ;
	}		
	
	if ( NULL == (serverManager = (ServerManager*) malloc(sizeof(ServerManager))) )
	{
		return NULL ;
	}
	
	InitServerNetArgs(serverManager ,&serverNetArgs) ;
	if ( NULL == (serverManager-> m_serverNet = ServerCreate( &serverNetArgs )) )
	{
		free(serverManager) ;
		return NULL ;		
	}
	
	if ( NULL == (serverManager -> m_users = UserCreate()) )
	{
		ServerDestroy(&(serverManager-> m_serverNet)) ;		
		free(serverManager) ;
		return NULL ;
	}
	
	if ( NULL == (serverManager -> m_groups = GroupCreate() ) )
	{
		ServerDestroy(&(serverManager-> m_serverNet)) ;			
		UserDestroy( serverManager -> m_users ) ;
		free(serverManager) ;
		return NULL ;
	}	
	
	if ( FAIL == InitSigintDestroy( serverManager ) )
	{
		ServerDestroy(&(serverManager-> m_serverNet)) ;			
		UserDestroy( serverManager -> m_users ) ;
		free(serverManager) ;	
		return NULL ;
	} 	
	
	
	FD_ZERO( &(serverManager -> m_loginFds) ) ;	
	return serverManager ;
}

/* ----------------------- Server Mangement Run ----------------------- */
void ServerMangementRun(ServerManager* _serverManager)
{
	if ( _serverManager != NULL )
	{	
		ServerRun(_serverManager->m_serverNet);
	}
	
	return ;
}

/* --------------------- Server Manager Destroy ---------------------- */
void ServerManagerDestroy(ServerManager **_serverManager)
{
	if ( (_serverManager != NULL) && (*_serverManager != NULL) )
	{
		ServerDestroy( &((*_serverManager)-> m_serverNet) ) ;			
		UserDestroy( (*_serverManager) -> m_users ) ;		
		GroupDestroy( (*_serverManager) -> m_groups ) ;		
		free(*_serverManager) ;
		*_serverManager = NULL ;	
	} 
			
	return ;
}

/* ========================= local func ============================= */

/* -------------------- Msg Recive And Send ------------------------- */
int MsgReciveAndSend(void *_serverManager, int _socketClient, char *_msg, int _sizeMsg)
{
	char	responseMsg[VALUE_LEN]	=	{ EMPTY } ;
	int		sizeResponseMsg			=	EMPTY ;

	CheckTypeReciveMsg( _serverManager, _socketClient, _msg, responseMsg, &sizeResponseMsg ) ;

	SendMessage(SERVER_NET(_serverManager), _socketClient, responseMsg, sizeResponseMsg) ;
	
	return OK ;
}


/* --------------------------- Sign Up ------------------------------ */
static void ServerSignUp(void *_serverManager, int _socketClient, char *_msg, int *_sizeMsg, char *_response) 
{
	SignUp signUp ;
	Response responseTLV ;
	RespType resultSignUp ;

	LogAction( "\nSign Up" ) ;
	
	ProtocolUnpackSignup(&signUp, _msg) ;

	LogUserName( signUp.m_userName.m_value ) ;
	LogPassword( signUp.m_password.m_value ) ;
		
	resultSignUp = UserSignUp(USERS(_serverManager), &signUp, _socketClient, &LOGIN_FDS(_serverManager));

	InitResponse( &responseTLV, resultSignUp) ;

	LogResponse(responseTLV.m_value);	
	
	SaveDetails(signUp.m_userName.m_value, signUp.m_password.m_value, responseTLV.m_value) ; 		
	
	*_sizeMsg  = ProtocolPackResponse (&responseTLV, _response) ;

	return ;
}

/* ---------------------- Init Server Net Args -------------------- */
static void InitServerNetArgs(ServerManager* _serverManager, ServerArgs *_serverNetArgs) 
{	
	_serverNetArgs-> m_portNum			= SERVER_PORT ;
	_serverNetArgs-> m_sizeListenQueue	= SIZE_QUEUE ;
	_serverNetArgs-> m_maxCLients		= MAX_CLIENTS ;
	_serverNetArgs-> m_funcNewClient	= NULL ;
	_serverNetArgs-> m_funcClientLeft	= ServerClientLeft ;	
	_serverNetArgs-> m_funcError		= NULL ;	
	_serverNetArgs-> m_funcNewMsg		= MsgReciveAndSend ;	
	_serverNetArgs-> m_context 			= _serverManager;
			
	return ;			 
}

/* ------------------------ Init Response ----------------------- */
static void InitResponse(Response *_response, RespType _result) 
{
	_response -> m_type   = RESPONSE ;
	_response -> m_length = LENGTH_RESPONSE ;
	_response -> m_value  = _result ;
	
	return ;
}

/* ----------------------- Server Log In ------------------------ */
static void ServerLogIn(void *_serverManager, int _socketClient, char *_msg, int *_sizeMsg , char *_response) 
{
	LogIn logIn ;
	Response responseTLV ;
	RespType resultlogIn ;

	LogAction("\nLog In");
	
	ProtocolUnpackLogIn(&logIn, _msg) ;
	
	LogUserName( logIn.m_userName.m_value );
	LogPassword( logIn.m_password.m_value );
		
	resultlogIn = UserLogIn(USERS(_serverManager), &logIn, _socketClient, &LOGIN_FDS(_serverManager));
	
	InitResponse( &responseTLV, resultlogIn) ;
	
	LogResponse(responseTLV.m_value);	
	
	*_sizeMsg  = ProtocolPackResponse (&responseTLV, _response) ;

	return ;
}

/* ----------------- Server Create Group ----------------------- */
static void ServerCreateGroup(void *_serverManager, int _socketClient, char *_msg, int *_sizeMsg , char *_response) 
{
	CreateGroup createGroup ;
	RespGroup respGroupTLV ;
	RespType resultCreatGroup ;		
	char ip[SIZE_IP] = { EMPTY } ;

	LogAction("\nCreate Group");
	
	ProtocolUnpackCreateGroup(&createGroup, _msg) ;

	LogGroupName( createGroup.m_groupName.m_value ) ;
	
	resultCreatGroup =  GroupNew(GROUPS(_serverManager), &createGroup, _socketClient , ip, &LOGIN_FDS(_serverManager)) ;
	
	InitResponseGroup(&respGroupTLV, resultCreatGroup, ip) ;

	LogResponse(respGroupTLV.m_resp.m_value);
	LogIp( respGroupTLV.m_ip.m_value ) ;		
	
	*_sizeMsg  = ProtocolPackRespGroup (&respGroupTLV, _response) ;
	
	return ;
}


/* ------------- Init Response Group -------------------------- */
static void InitResponseGroup(RespGroup *_respGroup, RespType _result, char *_ip) 
{
	_respGroup -> m_type	= RESP_GROUP ;
	_respGroup -> m_length	= RESP_GROUP_LENGTH ;
	InitResponse(&_respGroup -> m_resp, _result) ;
	InitIpNumber(&_respGroup -> m_ip, _ip) ;
	
	return ;
}


/* ------------- Init Ip Number ----------------------------- */
static void InitIpNumber(IpNumber *_ipNumber, char *_ip) 
{
	_ipNumber -> m_type		=	IP_NUMBER ;
	_ipNumber -> m_length	=	SIZE_IP ;
	strcpy( _ipNumber -> m_value , _ip ) ;
		
	return ;
}


/* -------- Server Req Group List -------------------------- */
static void ServerReqGroupList(void *_serverManager, int _socketClient, char *_msg, int *_sizeMsg , char *_response) 
{
	RespGroupsList respGroupListTLV ;	
	size_t numGroups ; 

	LogAction("\nReq Group List");
	
	numGroups = GroupSize(GROUPS(_serverManager)) ;
	
	InitRespGroupsList( &respGroupListTLV, numGroups) ;
	
	GroupReqList(GROUPS(_serverManager), respGroupListTLV.m_groups, _socketClient, &(LOGIN_FDS(_serverManager))) ;
					
	*_sizeMsg =  ProtocolPackRespGroupsList (&respGroupListTLV, _response) ; 	

	return ;
}

/* ------------- Init Resp Groups List ------------------------- */
static void InitRespGroupsList(RespGroupsList *_respGroupsList, size_t _sizeGroup) 
{
	_respGroupsList -> m_type	= RESP_GROUPS_LIST ;
	_respGroupsList -> m_length = RESP_GROUPS_LIST_LENGTH ;
	_respGroupsList -> m_value	= _sizeGroup ;	
	
	return ;
}


/* ---------------- Server Join Group --------------------------- */
static void ServerJoinGroup(void *_serverManager, int _socketClient, char *_msg, int *_sizeMsg , char *_response) 
{
	JoinGroup joinGroup ;
	RespType resultJoinGroup ;	
	RespGroup respGroupTLV ;	
	char ip[SIZE_IP] = { EMPTY } ;
			
	LogAction("\nJoin Group");
	
	ProtocolUnpackJoinGroup(&joinGroup, _msg);
	
	LogGroupName( joinGroup.m_groupName.m_value );
	
	resultJoinGroup = GroupJoin(GROUPS(_serverManager), &joinGroup, _socketClient , ip, &LOGIN_FDS(_serverManager)) ;	
	
	InitResponseGroup(&respGroupTLV, resultJoinGroup, ip) ;

	LogResponse( respGroupTLV.m_resp.m_value ) ;
	LogIp( respGroupTLV.m_ip.m_value ) ;		
	
	*_sizeMsg  = ProtocolPackRespGroup (&respGroupTLV, _response) ;
	
	return ;		
}


/* ---------------- Server Leave Group -------------------- */
static void ServerLeaveGroup(void *_serverManager, int _socketClient, char *_msg, int *_sizeMsg , char *_response) 
{
	LeaveGroup leaveGroup ;
	RespType resultLeaveGroup ;	
	Response responseTLV ;

	LogAction("\nLeave Group");
	
	ProtocolUnpackLeaveGroup(&leaveGroup, _msg);
	
	LogGroupName( leaveGroup.m_groupName.m_value );	
	
	resultLeaveGroup = GroupLeave(GROUPS(_serverManager), &leaveGroup, _socketClient, &LOGIN_FDS(_serverManager)) ;	

	InitResponse( &responseTLV, resultLeaveGroup) ;	
	
	LogResponse(responseTLV.m_value);
	
	*_sizeMsg  = ProtocolPackResponse (&responseTLV, _response) ;			
	
	return ;		
}


/* --------------------- Server Log Out -------------------- */
static void ServerLogOut(void *_serverManager, int _socketClient, char *_msg, int *_sizeMsg , char *_response)
{
	LogOut logOut ;
	Response responseTLV ;
	RespType resultlogOut ;

	LogAction("\nLog Out");
	
	ProtocolUnpackLogOut(&logOut, _msg) ;
	
	LogUserName( logOut.m_userName.m_value );
		
	resultlogOut = UserLogOut(USERS(_serverManager), &logOut, _socketClient, &LOGIN_FDS(_serverManager));
	
	if ( SUCCESS == resultlogOut )
	{
		GroupLeaveAll(GROUPS(_serverManager), _socketClient) ;		
	}
	
	InitResponse( &responseTLV, resultlogOut) ;
	
	LogResponse(responseTLV.m_value);	
	
	*_sizeMsg  = ProtocolPackResponse (&responseTLV, _response) ;

	return ;	
}


/* ---------------- Server Client Left ----------------------- */
static int ServerClientLeft(int _socketClient, void* _serverManager) 
{
	UserClientLeft( USERS(_serverManager), _socketClient, GROUPS(_serverManager), &LOGIN_FDS(_serverManager) ) ;
	
	return OK ;
}

/* ------------------ Save Details --------------------------- */
static void SaveDetails(char *_userName, char *_password, char _response) 
{
	FILE *fileSignUp;	
	
	if ( SUCCESS == _response )
	{	
		fileSignUp = fopen( SIGN_UP_FILE , "a");
		if ( NULL == fileSignUp )
		{
			return ;
		}	
		fprintf( fileSignUp , "%s %s\n", _userName, _password );
		
		fclose(fileSignUp) ;		
	}
	
	return ;	
}

/* ------------------------ Log Response ---------------------------- */
static void	LogResponse(char _response)
{
	int response = _response ;
	char strResponse[VALUE_LEN] = { EMPTY } ;
	
	switch(response)
	{
		case SUCCESS				:
										strcpy( strResponse, "Success" );
										break;
		case INVALID_USERNAME		:
										strcpy( strResponse, "invalid username" );
										break;
		case INVALID_PASSWORD		:
										strcpy( strResponse, "invalid password" );
										break;	
		case EXISTING_USERNAME		:
										strcpy( strResponse, "existing username" );
										break;	
		case INVALID_GROUP_ID		:
										strcpy( strResponse, "invalid group id" );
										break;	
		case USER_ALREADY_IN_USE	:
										strcpy( strResponse, "user already in use" );
										break;
		case SERVER_ERROR			:
										strcpy( strResponse, "server error" );
										break;
		case MULTI_ADDRESS_DEPLETED	:
										strcpy( strResponse, "multi addreess depleted" );
										break;																		
																																																
		default						:
										break;
	}
	
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpedantic"
	LOG( strResponse , OK );
#pragma GCC diagnostic pop

	return ;
}


/* ----------------------- Check Type Recive Msg --------------------------- */
static void CheckTypeReciveMsg(void *_serverManager, int _socketClient, char *_msg, char *_responseMsg, int *_sizeResponseMsg ) 
{
	Types	type	=	_msg[BIT_TYPE] ;
	
	switch(type)
	{
		case SIGNUP 		:
								ServerSignUp(_serverManager, _socketClient, _msg, _sizeResponseMsg , _responseMsg) ;
								break ;
		case LOGIN 			:
								ServerLogIn(_serverManager, _socketClient, _msg, _sizeResponseMsg, _responseMsg) ;
								break ;	
		case LOGOUT 			:
								ServerLogOut(_serverManager, _socketClient, _msg, _sizeResponseMsg , _responseMsg) ;
								break ;																
		case CREATE_GROUP 	:
								ServerCreateGroup(_serverManager, _socketClient, _msg, _sizeResponseMsg , _responseMsg) ;
								break ;
		case REQ_GROUP_LIST	:
								ServerReqGroupList(_serverManager, _socketClient, _msg, _sizeResponseMsg , _responseMsg) ;
								break ;	
		case JOIN_GROUP		:
								ServerJoinGroup(_serverManager, _socketClient, _msg, _sizeResponseMsg , _responseMsg) ;
								break ;
		case LEAVE_GROUP  	:	
								ServerLeaveGroup(_serverManager, _socketClient, _msg, _sizeResponseMsg , _responseMsg) ;
								break ;
		default				:
								break ;
	}
		
	return ;
}


/* ------------ CleanLogFile -------------- */
static FILE* CleanLogFile() 
{
		FILE *logFile;
		
		logFile = fopen(LOG_FILE , "w");
		if ( NULL == logFile )
		{
			return NULL ;
		}
		
		fclose( logFile ) ;
		
		return logFile ;
}

/* ----------- Log Action --------------- */
static void LogAction( char *_action ) 
{
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpedantic"
	LOG( _action, OK );
#pragma GCC diagnostic pop
	return ;
}


/* -------- Log User Name --------------- */
static void LogUserName( char *_userName ) 
{
	char userName[VALUE_LEN] = { EMPTY } ;
	
	sprintf(userName, "user name: %s" , _userName );

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpedantic"
	LOG( userName, OK );
#pragma GCC diagnostic pop
	
	return ;
}


/* ------- Log Password ---------------- */
static void LogPassword( char *_password ) 
{
	char password[VALUE_LEN] = { EMPTY } ;
	
	sprintf(password, "password : %s" , _password );

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpedantic"
	LOG( password, OK );
#pragma GCC diagnostic pop
	
	return ;
}


/* ------- Log Group Name -------------- */
static void LogGroupName( char *_groupName ) 
{
	char groupName[VALUE_LEN] = { EMPTY } ;
	
	sprintf(groupName, "group name: %s" , _groupName );

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpedantic"
	LOG( groupName, OK );
#pragma GCC diagnostic pop
	
	return ;
}


/* ------- Log Ip ------------------- */
static void LogIp( char *_ip ) 
{
	char ip[VALUE_LEN] = { EMPTY } ;
	
	sprintf(ip, "ip: %s" , _ip );

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpedantic"
	LOG( ip, OK );
#pragma GCC diagnostic pop
	
	return ;
}


/* ------------- Init Sigint ------- */
static int InitSigintDestroy( ServerManager *_serverManager ) 
{
	struct sigaction sa;

	sa.sa_handler = sigintHandler;
	sa.sa_flags = 0 ;
	sigemptyset(&sa.sa_mask);		

	if (-1 == sigaction(SIGINT, &sa, &m_oldAction))
	{
		return FAIL ;
	} 
	
	g_serverManager = _serverManager ;
	
	return OK ;
}

/* ----------- sigint Handler -------- */
static void sigintHandler(int _sig )
{
	write(0, " Destroy server, press again for exit\n", 38); 
	ServerManagerDestroy(&g_serverManager) ;
	sigaction(SIGINT, &m_oldAction, NULL) ;

	return ;
}
