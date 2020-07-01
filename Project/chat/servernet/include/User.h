#ifndef __USER_H__
#define __USER_H__

#include <sys/select.h>		/* fd_set */
#include "chatprotocol.h"
#include "Group.h"

typedef struct User User ;

/*
	Description -	make pointer to user
	Input		-	no input
	Output		-	a) pointer to user
				 	b) null
	Error		-	null : allocation failed 	  		
*/
User* UserCreate();

/*
	Description -	user sign up
	Input		-	a) pointer to user
					b) pointer to sign up
					c) socket client int
	Output		-	INVALID_USERNAME / INVALID_PASSWORD / SERVER_ERROR / SUCCESS
					EXISTING_USERNAME
	Error		-	INVALID_USERNAME	: empty user name 
					INVALID_PASSWORD	: empty password	  	
					SERVER_ERROR		: allocation failed	
					EXISTING_USERNAME   : user name already exist 
*/
RespType UserSignUp(User *_user, SignUp *_signUp, int _socketClient, fd_set *_loginFds) ;

/*
	Description -	user log in
	Input		-	a) pointer to user
					b) pointer to log in
					c) socket client int
					d) pointer to fd_set login
	Output		-	INVALID_USERNAME / INVALID_PASSWORD / USER_ALREADY_IN_USE / SUCCESS
					EXISTING_USERNAME
	Error		-	INVALID_USERNAME		: user name not sign up
					INVALID_PASSWORD		: wrong password	  	
					USER_ALREADY_IN_USE		: user already log in
*/
RespType UserLogIn(User *_user, LogIn *_logIN, int _socketClient, fd_set *_loginFds) ;

/*
	Description -	user log out
	Input		-	a) pointer to user
					b) pointer to log out
					c) socket client int
					d) pointer to fd_set login
	Output		-	INVALID_USERNAME / SUCCESS
					EXISTING_USERNAME
	Error		-	INVALID_USERNAME		: user name not log in
*/
RespType UserLogOut(User *_user, LogOut *_logOut, int _socketClient, fd_set *_loginFds) ;

/*
	Description -	client left
	Input		-	a) pointer to user
					b) socket client int
					c) pointer to group
					d) pointer to fd_set login
	Output		-	no output
	Error		-	no error	  		
*/
void UserClientLeft(User *_user, int _socketClient, Group *_groups, fd_set *_loginFds) ;

/*
	Description -	destroy user
	Input		-	pointer to user
	Output		-	no output
	Error		-	no error	  		
*/
void UserDestroy(User *_user) ;

#endif /* __USER_H__ */
