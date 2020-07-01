#include <stdio.h>
#include <string.h> 
#include <stdlib.h> /* size_t */
#include "../include/protocol.h"

/* --------------------------- define ------------------------------ */

#define TYPE_SIZE				1
#define LENGHT_SIZE				1


/* --------------------- statements locl func ---------------------- */
int ProtocolUnpackName(Name* _name, char* _msg, int* _loc) ;
int ProtocolPackName(Name* _name, char* _msg, int* _loc) ;
int ProtocolUnpackPassword (Password* _passowrd, char* _msg, int* _loc) ;
int ProtocolPackPassword (Password* _passowrd, char* _msg, int* _loc) ;
int ProtocolUnpackIpNumber (IpNumber* _ipNumber, char* _msg, int* _loc);
int ProtocolPackIpNumber (IpNumber* _ipNumber, char* _msg, int* _loc);

/* ============================== API ============================= */

/* ------------------------- Unpack Signup ------------------------ */
int ProtocolUnpackSignup(SignUp* _signup ,char* _msg)
{
    int loc = 0;

    memcpy((void*) &_signup->m_type, (void*) &_msg[loc], TYPE_SIZE);
    loc += TYPE_SIZE;
    memcpy((void*) &_signup->m_length, (void*) &_msg[loc], LENGHT_SIZE);
    loc += LENGHT_SIZE;
    memcpy((void*) &_signup->m_value, (void*) &_msg[loc], (int) _signup->m_length);
    loc += (int) _signup->m_length;
    ProtocolUnpackName(&_signup->m_userName, _msg, &loc);
    ProtocolUnpackPassword(&_signup->m_password, _msg, &loc);
    return loc;
}

/* ------------------------- Pack Signup --------------------------- */
int ProtocolPackSignup (SignUp* _signup, char* _msg)
{
	int loc = 0;

    memcpy((void*) &_msg[loc], &_signup->m_type, TYPE_SIZE);
	loc += TYPE_SIZE;
	memcpy((void*) &_msg[loc], &_signup->m_length, LENGHT_SIZE);
	loc += LENGHT_SIZE;
	memcpy((void*) &_msg[loc], &_signup->m_value, (int)(_signup->m_length));
	loc += (int) (_signup->m_length);
	ProtocolPackName(&_signup->m_userName, _msg, &loc);
	ProtocolPackPassword (&_signup->m_password, _msg, &loc);
	return loc;
}

/* ------------------------- Unpack LogIn ------------------------ */
int ProtocolUnpackLogIn(LogIn* _logIn ,char* _msg)
{
    int loc = 0;

    memcpy((void*) &_logIn->m_type, (void*) &_msg[loc], TYPE_SIZE);
    loc += TYPE_SIZE;
    memcpy((void*) &_logIn->m_length, (void*) &_msg[loc], LENGHT_SIZE);
    loc += LENGHT_SIZE;
    memcpy((void*) &_logIn->m_value, (void*) &_msg[loc], (int) _logIn->m_length);
    loc += (int) _logIn->m_length;
    ProtocolUnpackName(&_logIn->m_userName, _msg, &loc);
    ProtocolUnpackPassword(&_logIn->m_password, _msg, &loc);
    return loc;
}

/* ------------------------- Pack LogIn --------------------------- */
int ProtocolPackLogIn (LogIn* _logIn, char* _msg)
{
	int loc = 0;

    memcpy((void*) &_msg[loc], &_logIn->m_type, TYPE_SIZE);
	loc += TYPE_SIZE;
	memcpy((void*) &_msg[loc], &_logIn->m_length, LENGHT_SIZE);
	loc += LENGHT_SIZE;
	memcpy((void*) &_msg[loc], &_logIn->m_value, (int)(_logIn->m_length));
	_msg[loc] += (int) (_logIn->m_length);
	ProtocolPackName(&_logIn->m_userName, _msg, &loc) ;
	ProtocolPackPassword (&_logIn->m_password, _msg, &loc) ;
	return loc;
}

/* ------------------------- Pack Response --------------------------- */
int ProtocolPackResponse (Response* _response, char* _msg)
{
	int loc = 0;
    
	memcpy((void*) &_msg[loc], &_response->m_type, TYPE_SIZE);
	loc += TYPE_SIZE;
	memcpy((void*) &_msg[loc], &_response->m_length, LENGHT_SIZE);
	loc += LENGHT_SIZE;
	memcpy((void*) &_msg[loc], &_response->m_value, (int)(_response->m_length));
	loc += (int) (_response->m_length);
    return loc;
}

/* ------------------------- Unpack Response ------------------------ */
int ProtocolUnpackResponse(Response* _response ,char* _msg)
{
    int loc = 0;

    memcpy((void*) &_response->m_type, (void*) &_msg[loc], TYPE_SIZE);
    loc += TYPE_SIZE;
    memcpy((void*) &_response->m_length, (void*) &_msg[loc], LENGHT_SIZE);
    loc += LENGHT_SIZE;
    memcpy((void*) &_response->m_value, (void*) &_msg[loc], (int) _response->m_length);
    loc += (int) _response->m_length;
    return loc;
}

/* ------------------------- Pack CreateGroup --------------------------- */
int ProtocolPackCreateGroup (CreateGroup* _createGroup, char* _msg)
{
	int loc = 0;

    memcpy((void*) &_msg[loc], &_createGroup->m_type, TYPE_SIZE);
	loc += TYPE_SIZE;
	memcpy((void*) &_msg[loc], &_createGroup->m_length, LENGHT_SIZE);
	loc += LENGHT_SIZE;
	memcpy((void*) &_msg[loc], &_createGroup->m_value, (int)(_createGroup->m_length));
	_msg[loc] += (int) (_createGroup->m_length);
	ProtocolPackName(&_createGroup->m_groupName, _msg, &loc) ;
	return loc;
}

/* ------------------------- UnPack CreateGroup --------------------------- */
int ProtocolUnpackCreateGroup(CreateGroup* _createGroup ,char* _msg)
{
	int loc = 0;

    memcpy((void*) &_createGroup->m_type, (void*) &_msg[loc], TYPE_SIZE);
    loc += TYPE_SIZE;
    memcpy((void*) &_createGroup->m_length, (void*) &_msg[loc], LENGHT_SIZE);
    loc += LENGHT_SIZE;
    memcpy((void*) &_createGroup->m_value, (void*) &_msg[loc], (int) _createGroup->m_length);
    loc += (int) _createGroup->m_length;
    ProtocolUnpackName(&_createGroup->m_groupName, _msg, &loc);
    return loc;
}

/* ------------------------- Pack RespGroup --------------------------- */
int ProtocolPackRespGroup (RespGroup* _respGroup, char* _msg)
{
	int loc = 0;

    memcpy((void*) &_msg[loc], &_respGroup->m_type, TYPE_SIZE);
	loc += TYPE_SIZE;
	memcpy((void*) &_msg[loc], &_respGroup->m_length, LENGHT_SIZE);
	loc += LENGHT_SIZE;
	memcpy((void*) &_msg[loc], &_respGroup->m_value, (int)(_respGroup->m_length));
	_msg[loc] += (int) (_respGroup->m_length);
	loc += ProtocolPackResponse(&_respGroup->m_resp, &_msg[loc]);
    ProtocolPackIpNumber(&_respGroup->m_ip, _msg, &loc);
	return loc;
}

/* ------------------------- UnPack RespGroup --------------------------- */
int ProtocolUnpackRespGroup(RespGroup* _respGroup ,char* _msg)
{
	int loc = 0;

    memcpy((void*) &_respGroup->m_type, (void*) &_msg[loc], TYPE_SIZE);
    loc += TYPE_SIZE;
    memcpy((void*) &_respGroup->m_length, (void*) &_msg[loc], LENGHT_SIZE);
    loc += LENGHT_SIZE;
    memcpy((void*) &_respGroup->m_value, (void*) &_msg[loc], (int) _respGroup->m_length);
    loc += (int) _respGroup->m_length;
    loc += ProtocolUnpackResponse(&_respGroup->m_resp, &_msg[loc]);
    ProtocolUnpackIpNumber(&_respGroup->m_ip, _msg, &loc);
    return loc;
}

/* ------------------------- Pack JoinGroup --------------------------- */
int ProtocolPackJoinGroup (JoinGroup* _joinGroup, char* _msg)
{
	int loc = 0;

    memcpy((void*) &_msg[loc], &_joinGroup->m_type, TYPE_SIZE);
	loc += TYPE_SIZE;
	memcpy((void*) &_msg[loc], &_joinGroup->m_length, LENGHT_SIZE);
	loc += LENGHT_SIZE;
	memcpy((void*) &_msg[loc], &_joinGroup->m_value, (int)(_joinGroup->m_length));
	_msg[loc] += (int) (_joinGroup->m_length);
	ProtocolPackName(&_joinGroup->m_groupName, _msg, &loc) ;
	return loc;
}

/* ------------------------- UnPack JoinGroup --------------------------- */
int ProtocolUnpackJoinGroup(JoinGroup* _joinGroup ,char* _msg)
{
	int loc = 0;

    memcpy((void*) &_joinGroup->m_type, (void*) &_msg[loc], TYPE_SIZE);
    loc += TYPE_SIZE;
    memcpy((void*) &_joinGroup->m_length, (void*) &_msg[loc], LENGHT_SIZE);
    loc += LENGHT_SIZE;
    memcpy((void*) &_joinGroup->m_value, (void*) &_msg[loc], (int) _joinGroup->m_length);
    loc += (int) _joinGroup->m_length;
    ProtocolUnpackName(&_joinGroup->m_groupName, _msg, &loc);
    return loc;
}

/* ------------------------- Pack LeaveGroup --------------------------- */
int ProtocolPackLeaveGroup (LeaveGroup* _leaveGroup, char* _msg)
{
	int loc = 0;

    memcpy((void*) &_msg[loc], &_leaveGroup->m_type, TYPE_SIZE);
	loc += TYPE_SIZE;
	memcpy((void*) &_msg[loc], &_leaveGroup->m_length, LENGHT_SIZE);
	loc += LENGHT_SIZE;
	memcpy((void*) &_msg[loc], &_leaveGroup->m_value, (int)(_leaveGroup->m_length));
	_msg[loc] += (int) (_leaveGroup->m_length);
	ProtocolPackName(&_leaveGroup->m_groupName, _msg, &loc) ;
	return loc;
}

/* ------------------------- UnPack LeaveGroup --------------------------- */
int ProtocolUnpackLeaveGroup(LeaveGroup* _leaveGroup ,char* _msg)
{
	int loc = 0;

    memcpy((void*) &_leaveGroup->m_type, (void*) &_msg[loc], TYPE_SIZE);
    loc += TYPE_SIZE;
    memcpy((void*) &_leaveGroup->m_length, (void*) &_msg[loc], LENGHT_SIZE);
    loc += LENGHT_SIZE;
    memcpy((void*) &_leaveGroup->m_value, (void*) &_msg[loc], (int) _leaveGroup->m_length);
    loc += (int) _leaveGroup->m_length;
    ProtocolUnpackName(&_leaveGroup->m_groupName, _msg, &loc);
    return loc;
}


/* ------------------- Protocol Pack Resp Groups List ------------------ */
int ProtocolPackRespGroupsList(RespGroupsList *_respGroupList, char* _msg) 
{
	int loc = 0 , i;

    memcpy((void*) &_msg[loc], &_respGroupList->m_type, TYPE_SIZE);
	loc += TYPE_SIZE;
	memcpy((void*) &_msg[loc], &_respGroupList->m_length, LENGHT_SIZE);
	loc += LENGHT_SIZE;
	memcpy((void*) &_msg[loc], &_respGroupList->m_value, (int)(_respGroupList->m_length));
	loc += (int) (_respGroupList->m_length);
	for ( i = 0 ; i < _respGroupList->m_value ; ++i )
	{
		ProtocolPackName(&(_respGroupList->m_groups[i]), _msg, &loc) ;
	}
	return loc ;
}

/* ---------------- Protocol Unpack Resp Groups List ------------------- */
int ProtocolUnpackRespGroupsList(RespGroupsList *_respGroupList, char* _msg) 
{
	int loc = 0, i;

    memcpy((void*) &_respGroupList->m_type, (void*) &_msg[loc], TYPE_SIZE);
    loc += TYPE_SIZE;
    memcpy((void*) &_respGroupList->m_length, (void*) &_msg[loc], LENGHT_SIZE);
    loc += LENGHT_SIZE;
    memcpy((void*) &_respGroupList->m_value, (void*) &_msg[loc], (int) _respGroupList->m_length);
    loc += (int) _respGroupList->m_length;
    for ( i = 0 ; i < _respGroupList->m_value ; ++i )
    {
		ProtocolUnpackName(&(_respGroupList->m_groups[i]), _msg, &loc);
	}	
    return loc;
}

/* --------------- Protocol Pack Log Out ---------------- */
int ProtocolPackLogOut (LogOut* _logOut, char* _msg)
{
	int loc = 0;

    memcpy((void*) &_msg[loc], &_logOut->m_type, TYPE_SIZE);
	loc += TYPE_SIZE;
	memcpy((void*) &_msg[loc], &_logOut->m_length, LENGHT_SIZE);
	loc += LENGHT_SIZE;
	memcpy((void*) &_msg[loc], &_logOut->m_value, (int)(_logOut->m_length));
	_msg[loc] += (int) (_logOut->m_length);
	ProtocolPackName(&_logOut->m_userName, _msg, &loc) ;
	return loc;
}

/* -------------- Protocol Un pack Log Out -------------- */
int ProtocolUnpackLogOut(LogOut* _logOut ,char* _msg)
{
	int loc = 0;

    memcpy((void*) &_logOut->m_type, (void*) &_msg[loc], TYPE_SIZE);
    loc += TYPE_SIZE;
    memcpy((void*) &_logOut->m_length, (void*) &_msg[loc], LENGHT_SIZE);
    loc += LENGHT_SIZE;
    memcpy((void*) &_logOut->m_value, (void*) &_msg[loc], (int) _logOut->m_length);
    loc += (int) _logOut->m_length;
    ProtocolUnpackName(&_logOut->m_userName, _msg, &loc);
    return loc;
}

/* ========================= local func ============================= */

/* ------------------------- Unpack Name --------------------------- */
int ProtocolUnpackName(Name* _name, char* _msg, int* _loc)
{
    memcpy((void*) &_name->m_type, (void*) &_msg[*_loc], TYPE_SIZE);
    *_loc += TYPE_SIZE;
    memcpy((void*) &_name->m_length, (void*) &_msg[*_loc], LENGHT_SIZE);
    *_loc += LENGHT_SIZE;
    memcpy((void*) &_name->m_value, (void*) &_msg[*_loc], (int) _name->m_length);
    *_loc += (int) _name->m_length;
    _name->m_value[(int) _name->m_length] = '\0';
    return *_loc;
}

/* ------------------------- Pack Name --------------------------- */
int ProtocolPackName(Name* _name, char* _msg, int* _loc)
{
    memcpy((void*) &_msg[*_loc], &_name->m_type, TYPE_SIZE);
    *_loc += TYPE_SIZE;
    memcpy((void*) &_msg[*_loc], &_name->m_length, LENGHT_SIZE);
    *_loc += LENGHT_SIZE;
    memcpy((void*) &_msg[*_loc], &_name->m_value, (int) _name->m_length);
    *_loc += (int) _name->m_length;
    return *_loc;
}

/* ------------------------- Unpack Password --------------------------- */
int ProtocolUnpackPassword (Password* _passowrd, char* _msg, int* _loc)
{
    memcpy((void*) &_passowrd->m_type, (void*) &_msg[*_loc], TYPE_SIZE);
    *_loc += TYPE_SIZE;
    memcpy((void*) &_passowrd->m_length, (void*) &_msg[*_loc], LENGHT_SIZE);
    *_loc += LENGHT_SIZE;
    memcpy((void*) &_passowrd->m_value, (void*) &_msg[*_loc], (int) _passowrd->m_length);
    *_loc += (int) _passowrd->m_length;
    _passowrd->m_value[(int) _passowrd->m_length] = '\0';
    return *_loc;
}

/* ------------------------- Pack Password --------------------------- */
int ProtocolPackPassword (Password* _passowrd, char* _msg, int* _loc)
{
    memcpy((void*) &_msg[*_loc] , &_passowrd->m_type, TYPE_SIZE);
    *_loc += TYPE_SIZE;
    memcpy((void*) &_msg[*_loc], &_passowrd->m_length, LENGHT_SIZE);
    *_loc += LENGHT_SIZE;
    memcpy((void*) &_msg[*_loc], &_passowrd->m_value, (int) _passowrd->m_length);
    *_loc += (int) _passowrd->m_length;
    return *_loc;
}

/* ------------------------- Unpack IpNumber --------------------------- */
int ProtocolUnpackIpNumber (IpNumber* _ipNumber, char* _msg, int* _loc)
{
    memcpy((void*) &_ipNumber->m_type, (void*) &_msg[*_loc], TYPE_SIZE);
    *_loc += TYPE_SIZE;
    memcpy((void*) &_ipNumber->m_length, (void*) &_msg[*_loc], LENGHT_SIZE);
    *_loc += LENGHT_SIZE;
    memcpy((void*) &_ipNumber->m_value, (void*) &_msg[*_loc], (int) _ipNumber->m_length);
    *_loc += (int) _ipNumber->m_length;
    _ipNumber->m_value[(int) _ipNumber->m_length] = '\0';
    return *_loc;
}

/* ------------------------- Pack IpNumber --------------------------- */
int ProtocolPackIpNumber (IpNumber* _ipNumber, char* _msg, int* _loc)
{
    memcpy((void*) &_msg[*_loc] , &_ipNumber->m_type, TYPE_SIZE);
    *_loc += TYPE_SIZE;
    memcpy((void*) &_msg[*_loc], &_ipNumber->m_length, LENGHT_SIZE);
    *_loc += LENGHT_SIZE;
    memcpy((void*) &_msg[*_loc], &_ipNumber->m_value, (int) _ipNumber->m_length);
    *_loc += (int) _ipNumber->m_length;
    return *_loc;
}
