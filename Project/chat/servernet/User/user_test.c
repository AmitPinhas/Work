#include <stdio.h>
#include <string.h>
#include "User.h"
#include "protocol.h"
#include "chatprotocol.h" 

int main()
{
	SignUp signUpVar, signUpNew ;
	LogIn logInVar, logInNew ;	
	LogOut LogOutVar, LogOutNew ;		
	char msg[VALUE_LEN] , msg2[VALUE_LEN] ;
	
	printf("Sign up Positive\n");
	
	signUpVar.m_type	= SIGNUP ;
	signUpVar.m_length	= 0 ;
	signUpVar.m_userName.m_type = NAME ;
	signUpVar.m_userName.m_length = 4 ;			
	strcpy(signUpVar.m_userName.m_value , "Amit" ) ;
	signUpVar.m_password.m_type = PASSWORD ;
	signUpVar.m_password.m_length = 4 ;		
	strcpy ( signUpVar.m_password.m_value , "1234" ) ;
	
	
	ProtocolPackSignup (&signUpVar, msg) ;
	
	ProtocolUnpackSignup(&signUpNew, msg) ;

	printf("type sign up %d\n" , signUpNew.m_type ) ;
	printf("length sign up %d\n" , signUpNew.m_length ) ;
	printf("type name %d\n" , signUpNew.m_userName.m_type );
	printf("length name %d\n" , signUpNew.m_userName.m_length );			
	printf("user name %s\n" , signUpNew.m_userName.m_value );
	printf("type pass %d\n" , signUpNew.m_password.m_type );
	printf("length pass %d\n" , signUpNew.m_password.m_length );	
	printf("password %s\n" , signUpNew.m_password.m_value );	
	
	printf("\nlog in Positive\n");	
	
	logInVar.m_type	= LOGIN ;
	logInVar.m_length	= 0 ;
	logInVar.m_userName.m_type = NAME ;
	logInVar.m_userName.m_length = 4 ;			
	strcpy(logInVar.m_userName.m_value , "Amit" ) ;
	logInVar.m_password.m_type = PASSWORD ;
	logInVar.m_password.m_length = 4 ;		
	strcpy ( logInVar.m_password.m_value , "1234" ) ;
	
	
	ProtocolPackLogIn (&logInVar, msg2) ;
	
	ProtocolUnpackLogIn(&logInNew, msg2) ;

	printf("type log In %d\n" , logInNew.m_type ) ;
	printf("length log In %d\n" , logInNew.m_length ) ;
	printf("type name %d\n" , logInNew.m_userName.m_type );
	printf("length name %d\n" , logInNew.m_userName.m_length );			
	printf("user name %s\n" , logInNew.m_userName.m_value );
	printf("type pass %d\n" , logInNew.m_password.m_type );
	printf("length pass %d\n" , logInNew.m_password.m_length );	
	printf("password %s\n" , logInNew.m_password.m_value );

	printf("\nlog Out Positive\n");	
	
	LogOutVar.m_type	= LOGOUT ;
	LogOutVar.m_length	= 0 ;
	LogOutVar.m_userName.m_type = NAME ;
	LogOutVar.m_userName.m_length = 4 ;			
	strcpy(LogOutVar.m_userName.m_value , "Amit" ) ;
	
	
	ProtocolPackLogOut (&LogOutVar, msg2) ;
	
	ProtocolUnpackLogOut(&LogOutNew, msg2) ;

	printf("type Log Out %d\n" , LogOutNew.m_type ) ;
	printf("length Log Out %d\n" , LogOutNew.m_length ) ;
	printf("type name %d\n" , LogOutNew.m_userName.m_type );
	printf("length name %d\n" , LogOutNew.m_userName.m_length );			
	printf("user name %s\n" , LogOutNew.m_userName.m_value );
		
	return 0 ;
}

