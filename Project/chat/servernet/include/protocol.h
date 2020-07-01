#ifndef __PROTOCOL_H__
#define __PROTOCOL_H__
#include "chatprotocol.h" /* protocolStruct */

int ProtocolUnpackSignup(SignUp* _signup ,char* _msg);

int ProtocolPackSignup (SignUp* _signup, char* _msg);

int ProtocolPackResponse (Response* _response, char* _msg);

int ProtocolUnpackResponse(Response* _response ,char* _msg);

int ProtocolPackLogIn (LogIn* _logIn, char* _msg);

int ProtocolUnpackLogIn(LogIn* _logIn ,char* _msg);

int ProtocolPackCreateGroup (CreateGroup* _createGroup, char* _msg);

int ProtocolUnpackCreateGroup(CreateGroup* _createGroup ,char* _msg);

int ProtocolPackRespGroup (RespGroup* _RespGroup, char* _msg);

int ProtocolUnpackRespGroup(RespGroup* _RespGroup ,char* _msg);

int ProtocolPackJoinGroup (JoinGroup* _joinGroup, char* _msg);

int ProtocolUnpackJoinGroup(JoinGroup* _joinGroup ,char* _msg);

int ProtocolPackRespGroupsList(RespGroupsList *_respGroupList, char* _msg) ; 	

int ProtocolUnpackRespGroupsList(RespGroupsList *_respGroupList, char* _msg) ; 

int ProtocolPackLeaveGroup (LeaveGroup* _leaveGroup, char* _msg) ;

int ProtocolUnpackLeaveGroup(LeaveGroup* _leaveGroup ,char* _msg) ;

int ProtocolPackLogOut (LogOut* _logOut, char* _msg);

int ProtocolUnpackLogOut(LogOut* _logOut ,char* _msg);

#endif /* __PROTOCOL_H__ */
