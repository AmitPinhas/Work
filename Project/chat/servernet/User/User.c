#include <string.h>		/* strlen , strcmp */
#include <stdlib.h>		/* allocation */
#include <stdio.h>		/* file */
#include "User.h"
#include "HashMap.h"

/* --------------------------- define ------------------------------ */
#define HASH_CAPACITY		300
#define NOT_EQUAL			0
#define EQUAL_KEY			1 
#define EQUAL				0  
#define OFFLINE				0
#define ACTIVE				1
#define STOP				0
#define CONTINUE            1
#define NO_SOCKET_CLIENT	-1
#define SIGN_UP_FILE		"sign_up.txt"

/* ---------------------------- macro ------------------------------ */ 
#define USER_NAME(SignUp)	( (SignUp)->m_userName.m_value )
#define PASSWORD(SignUp)	( (SignUp)->m_password.m_value )


/* --------------------------- struct ------------------------------ */
struct User{
	HashMap *m_users ;	
};

typedef struct{
	char	m_userName[VALUE_LEN] ;
	char	m_password[VALUE_LEN] ;
	int		m_socketClient ;
}UserArgs;

/* --------------------- statements locl func ---------------------- */
size_t HashUser(const void* _userName) ;
int EqualUser(const void* _userName1, const void* _userName2) ;
static RespType CheckParam(SignUp *_signUp) ;
static UserArgs* CreateUserArgs(char *_userName, char *_password, int _socketClient) ;
static RespType RespTypeError(MapResult _error) ;
void DestroyUserArgs(void* _userArgs) ;
static void InitHashFromFile(HashMap *_users) ;
static void EnterClientToHash(HashMap *_users, FILE *_fileSignUp) ;
static int	FindSocketClient(const void* _userName, void* _userArgs, void* _socketClient);

/* ============================= API =============================== */

/* ------------------------- User Create --------------------------- */
User* UserCreate()
{
	User *user;
	
	user = (User*) malloc(sizeof(User)) ;
	if ( NULL == user )
	{
		return NULL ;
	}
	
	user -> m_users = HashMapCreate(HASH_CAPACITY, HashUser, EqualUser);
	if ( NULL == user -> m_users )
	{
		free(user) ;
		return NULL ;
	}

	InitHashFromFile( user -> m_users ) ;
	
	return user ;
}


/* ------------------------- User Sign Up --------------------------- */
RespType UserSignUp(User *_user, SignUp *_signUp, int _socketClient, fd_set *_loginFds) 
{
	RespType result ;
	UserArgs *userArgs ;
	MapResult resultMap ;
	
	if ( (result = CheckParam( _signUp )) != SUCCESS )
	{
		return result ;
	} 
	
	userArgs = CreateUserArgs( USER_NAME(_signUp), PASSWORD(_signUp), _socketClient ) ;
	if ( NULL == userArgs )
	{
		return SERVER_ERROR ;
	}
	
	if ((resultMap = HashMapInsert(_user->m_users, userArgs->m_userName, userArgs)) != MAP_SUCCESS )
	{
		return RespTypeError( resultMap ) ;
	}

	FD_SET( _socketClient, _loginFds) ;	
	return SUCCESS ;
}

/* ---------------------- User Log In ------------------------------ */
RespType UserLogIn(User *_user, LogIn *_logIN, int _socketClient, fd_set *_loginFds)
{
	UserArgs *userArgs ;
	MapResult resultMap ;
	
	resultMap = HashMapFind(_user->m_users, _logIN->m_userName.m_value, (void**)&userArgs);
	if (resultMap == MAP_SUCCESS )
	{
		if ( 0 == ( strcmp(userArgs -> m_password ,  _logIN->m_password.m_value) ) )
		{
			if ( !(FD_ISSET( userArgs -> m_socketClient, _loginFds )) )
			{
				userArgs -> m_socketClient	=	_socketClient ;
				FD_SET( userArgs -> m_socketClient, _loginFds) ;
				return SUCCESS ;
			}
			else
			{
				return USER_ALREADY_IN_USE ;
			}	
		}
		else
		{
			return INVALID_PASSWORD ;
		}
	}
	else
	{
		return RespTypeError( resultMap ) ;
	} 
}


/* ------------------------ User Log Out ---------------------------- */
RespType UserLogOut(User *_user, LogOut *_logOut, int _socketClient, fd_set *_loginFds) 
{
	UserArgs *userArgs ;
	MapResult resultMap ;
	
	resultMap = HashMapFind(_user->m_users, _logOut->m_userName.m_value, (void**)&userArgs);
	if ( resultMap != MAP_SUCCESS )
	{
		return INVALID_USERNAME ;
	}
	else
	{
		if ( !(FD_ISSET(userArgs -> m_socketClient, _loginFds)) )
		{
			return INVALID_USERNAME ;
		}	
		FD_CLR( userArgs -> m_socketClient, _loginFds) ;
		userArgs -> m_socketClient = NO_SOCKET_CLIENT ;
		return SUCCESS ;
	}
}

/* ------------------------ User Destroy ---------------------------- */
void UserDestroy(User *_user) 
{
	HashMapDestroy( &(_user->m_users), NULL, DestroyUserArgs) ;
	return ;
}

/* --------------------- User Client Left ---------------------------- */
void UserClientLeft(User *_user, int _socketClient, Group *_groups, fd_set *_loginFds)
{
	FD_CLR( _socketClient, _loginFds) ;
	HashMapForEach(_user->m_users, FindSocketClient, &_socketClient);
	GroupLeaveAll(_groups, _socketClient) ;
	return ;
}

/* ========================= local func ============================= */

/* -------------------------- Hash User ----------------------------- */
size_t HashUser(const void* _userName) 
{
	int sum = 0, i ;
	char *userName = (char*)_userName ;
	
	for ( i = 0 ; userName[i] != '\0' ; ++i )
	{
		sum += userName[i] ;
	}
	
	return sum ;
}


/* ------------------------- Equal User ----------------------------- */
int EqualUser(const void* _userName1, const void* _userName2) 
{

	if ( EQUAL ==  ( strcmp((char*)_userName1, (char*)_userName2) ) ) 
	{
		return EQUAL_KEY ;
	}
	
	return NOT_EQUAL ;
	
}

/* ------------------------ Check Param ------------------------------ */
static RespType CheckParam(SignUp *_signUp) 
{
	if ( 0 == strlen( USER_NAME(_signUp) ) )
	{
		return INVALID_USERNAME ;
	}
	
	if ( 0 == strlen ( PASSWORD(_signUp) ) )
	{
		return INVALID_PASSWORD ;
	}
	
	return SUCCESS ;
}

/* --------------------- Create User Args ---------------------------- */
static UserArgs* CreateUserArgs(char *_userName, char *_password, int _socketClient) 
{
	UserArgs *userArgs ;
	
	userArgs = (UserArgs*) malloc(sizeof(UserArgs)) ;
	if ( NULL == userArgs )
	{
		return NULL ;
	}
	
	strcpy( userArgs -> m_userName , _userName ) ;
	strcpy( userArgs -> m_password , _password ) ;
	userArgs -> m_socketClient = _socketClient ;
	
	return userArgs ;	
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


/* -------------------- Destroy User Args ---------------------- */
void DestroyUserArgs(void* _userArgs) 
{
	free( _userArgs ) ;
	return ;
}


/* ------------------ Init Hash From File ---------------------- */
static void InitHashFromFile(HashMap *_users) 
{
	FILE *fileSignUp;	
		
	fileSignUp = fopen( SIGN_UP_FILE , "r");
	if ( NULL == fileSignUp )
	{
		return ;
	}
	
	while ( !feof( fileSignUp ) )
	{
		EnterClientToHash(_users, fileSignUp ) ;
	}
	
	EnterClientToHash(_users, fileSignUp ) ;	
	
	fclose( fileSignUp ) ;
	
	return ;
}


/* ---------------- Enter Client To Hash ------------------- */
static void EnterClientToHash(HashMap *_users, FILE *_fileSignUp)
{
	UserArgs *userArgs ;
	char userName[VALUE_LEN], password[VALUE_LEN] ;
		
	fscanf( _fileSignUp, "%s %s", userName, password) ;
	userArgs = CreateUserArgs( userName, password, NO_SOCKET_CLIENT ) ;	
	HashMapInsert(_users, userArgs->m_userName, userArgs) ;	
	
	return ;
}

/* --------------- Find Socket Client --------------------- */
static int FindSocketClient(const void* _userName, void* _userArgs, void* _socketClient)
{
	if ( ((UserArgs*)_userArgs)-> m_socketClient == *((int*)_socketClient) )
	{
		((UserArgs*)_userArgs) -> m_socketClient = NO_SOCKET_CLIENT ;
		return STOP ;
	}
	return CONTINUE ;
}
