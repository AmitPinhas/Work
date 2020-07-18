#ifndef _DEFAULT_SOURCE
#define _DEFAULT_SOURCE
#endif
#include <stdio.h> /* printf */
#include <signal.h> /* sigaction */
#include <stdlib.h> /* malloc */
#include <unistd.h> /* close */
#include <string.h> /* memset, strcpy */
#include "../../include/chatprotocol.h" /* types */
#include "../include/clientManager.h" /* server functions */
#include "../include/clientnet.h" /* client functions*/
#include "../include/entrance.h" /* entrance signup */
#include "../include/ui.h" /* ui fucntion */
#include "../include/ErrDefs.h" /* error typedef*/
#include "../../include/protocol.h" /* packing, unpacking*/
#include "../include/group.h"       /* group functions */


#define BUFF_SIZE 1024

#define MENU_ON                 1
#define MENU_OFF                0
#define LOGGED_IN               0
#define LOGGED_OFF              1
#define APP_RUNNING             1
#define APP_SHUTING_DOWN        0
#define ACTION_SUCCESS_TXT      "Action Succesful"
#define LOGGED_IN_TXT           "Logged in sucessful"
#define LOGGED_OUT_TXT          "Logged Out"
#define WRONG_SLECTION          "Wrong selection, please try again"

int g_run = APP_RUNNING;

struct ClientManager {
    Clientnet*                  m_clientnet;                      
    GroupManager*               m_group;
    char                        m_name[VALUE_LEN];
    int                         m_appRun;
    int                         m_logged;
};

static void ClientManagerInit(ClientManager* _clientManager);
static void SignUpUser(ClientManager* _ClientManager);
static void LoginUser(ClientManager* _clientManager);
static void CheckResponse(ClientManager* _clientManager, Response _response, char* _name);
static ErrDefs EntranceSelection(ClientManager* _clientManager);
static ErrDefs GetGroupSelection(ClientManager* _clientManager);
static void Transmiting (ClientManager* _clientManager,char* _buff, int _buffSize);
static ErrDefs AddNewGroup(ClientManager* _clientManager);
static ErrDefs JoinAGroup(ClientManager* _clientManager);
static ErrDefs GetGroupList(ClientManager* _clientManager);
static ErrDefs LeaveAGroup(ClientManager* _clientManager);
static ErrDefs SendLogOut(ClientManager* _clientManager);
static void LogoutClient(ClientManager* _clientManager);
static void GroupDetailsPacking(CreateGroup* _newGroup, char* _groupName);
static void JoinGroupDetailsPacking(JoinGroup* _group, char* _groupName);
static void LogoutDetailsPacking(LogOut* _user, char* _userName);
static void LeaveGroupDetailsPacking(LeaveGroup* _group, char* _groupName);
static void GroupListDetailsPacking(ReqGroupsList* _group);
static void ChangeSigAction (ClientManager* _clientManager);
static void CloseApp (int sig);
static void ShutDown(ClientManager* _clientManager);
/******************************************************/
/************     Public      *************************/
/******************************************************/
ClientManager* ClientManagerCreate(const char* _serverIp, size_t _serverPort)
{
    ClientManager* newClientManager = NULL;

    ChangeSigAction(newClientManager);
    if (NULL == (newClientManager = (ClientManager*) malloc (sizeof(ClientManager))))
    {
        return NULL;
    }

    if (NULL == (newClientManager->m_clientnet = ClientnetCreate(_serverIp, _serverPort)))
    {
        free(newClientManager);
        return NULL;
    }

    if (NULL == (newClientManager->m_group = GroupManagerCreate()))
    {
        ClientnetDestroy(&newClientManager->m_clientnet);
        free(newClientManager);
        return NULL;
    }

    ClientManagerInit(newClientManager);
    return newClientManager;
}

void ClientManagerDestroy (ClientManager** _clientManager)
{
    if (NULL != _clientManager && NULL != *_clientManager)
    {
        GroupManagerDestroy(&(*_clientManager)->m_group);
        ClientnetDestroy(&(*_clientManager)->m_clientnet);
        free(*_clientManager);
        *_clientManager = NULL;
    }
    return;
}

void ClientManagerRun (ClientManager* _clientManager)
{
    while (APP_RUNNING == g_run)
    {
        if (_clientManager->m_logged == LOGGED_OFF)
        {
            EntranceSelection(_clientManager);
        }
        else
        {
            GetGroupSelection(_clientManager);
        }
    }
    ShutDown(_clientManager);
    return;
}

/******************************************************/
/************     Locals      *************************/
/******************************************************/
static void ClientManagerInit(ClientManager* _clientManager)
{
    _clientManager->m_appRun = APP_RUNNING;
    _clientManager->m_logged = LOGGED_OFF;
    return;
}

static void SignUpUser(ClientManager* _clientManager)
{
    SignUp signup;
    Response response = {0};
    char buff[BUFF_SIZE] = {0};
    int size = 0;
    signup.m_type = SIGNUP;
    signup.m_length = 0;

    if (ERR_PARAM_ERROR == EntranceSignup(&signup))
    {
        return;
    }
    size = ProtocolPackSignup(&signup, buff);
    Transmiting(_clientManager, buff, size);
    ProtocolUnpackResponse(&response, buff);  

    CheckResponse(_clientManager, response, signup.m_userName.m_value);
    return;
}

static void LoginUser(ClientManager* _clientManager)
{
    LogIn login;
    Response response = {0};
    char buff[BUFF_SIZE] = {0};
    int size = 0;
    login.m_type = LOGIN;
    login.m_length = 0;

    if (ERR_PARAM_ERROR == EntranceLogIn(&login))
    {
        return;
    }
    size = ProtocolPackLogIn(&login, buff);
    Transmiting(_clientManager, buff, size);
    ProtocolUnpackResponse(&response, buff);  

    CheckResponse(_clientManager, response, login.m_userName.m_value);
    return;
}

static void CheckResponse(ClientManager* _clientManager, Response _response, char* _name)
{
    if (_response.m_type == RESPONSE && (int) _response.m_value == SUCCESS)
    {
        _clientManager->m_logged = LOGGED_IN;
        strcpy(_clientManager->m_name, _name);
        UiPrintMsg(LOGGED_IN_TXT);
    }
    else
    {
        UiErrorHandling(_response.m_value);
    }
    return;
}

static ErrDefs EntranceSelection(ClientManager* _clientManager)
{
    int selection = EntranceMenu();
    switch (selection)
    {
        case ENTRANCE_SIGNUP:
            SignUpUser(_clientManager);    
            break;
        case ENTRACE_LOGIN:
            LoginUser(_clientManager);
            break;
        case ENTRANCE_EXIT_APP:
            g_run = APP_SHUTING_DOWN;
            break;
        default:
            UiPrintMsg(WRONG_SLECTION);
            break;
    }
    return ERR_OK;
}

static ErrDefs GetGroupSelection(ClientManager* _clientManager)
{
    int selcetion = GroupManagerSelection(_clientManager->m_group);
    switch (selcetion)
    {
        case CREATE_NEW_GROUP:
            AddNewGroup(_clientManager);        
            break;
        case GET_ALL_GROUPS:
            GetGroupList(_clientManager);
            break;
        case JOIN_A_GROUP:
            JoinAGroup(_clientManager);
            break;
        case LEAVE_A_GROUP:
            LeaveAGroup(_clientManager);
            break;
        case LOG_OUT:
            SendLogOut(_clientManager);
            break;
        case EXIT_APP:
            g_run = APP_SHUTING_DOWN;
            SendLogOut(_clientManager);
            break;
        default:
            UiPrintMsg(WRONG_SLECTION);
            break;
    }
    return ERR_OK;
}

static void Transmiting (ClientManager* _clientManager,char* _buff, int _buffSize)
{
    ClientnetSendMsg(_clientManager->m_clientnet, _buff, _buffSize);
    ClientnetRecieveMsg(_clientManager->m_clientnet, _buff, BUFF_SIZE);
    return;
}

static ErrDefs AddNewGroup(ClientManager* _clientManager)
{
    CreateGroup newGroup;
    RespGroup resGroup = {0};
    RespType  resType;
    char groupName[VALUE_LEN];
    char buff[BUFF_SIZE] = {0};
    int size = 0;

    if(ERR_PARAM_ERROR == GroupManagerGetName(groupName, &newGroup.m_groupName.m_length))
    {
        return ERR_PARAM_ERROR;
    }
    
    GroupDetailsPacking(&newGroup, groupName);
    size = ProtocolPackCreateGroup(&newGroup ,buff);
    Transmiting(_clientManager, buff, size);
    ProtocolUnpackRespGroup(&resGroup, buff);  

    resType = resGroup.m_resp.m_value;
    if (resType != SUCCESS)
    {
        UiErrorHandling(resType);
    }
    else
    {
        UiPrintMsg(ACTION_SUCCESS_TXT);
        GroupManagerCreateGroup(_clientManager->m_group, groupName, _clientManager->m_name, resGroup.m_ip.m_value);
    }
    return ERR_OK;
}

static ErrDefs JoinAGroup(ClientManager* _clientManager)
{
    JoinGroup joinGroup;
    RespGroup response = {0};
    RespType  resType;
    char groupName[VALUE_LEN];
    char buff[BUFF_SIZE] = {0};
    int size = 0;

    if(ERR_PARAM_ERROR == GroupManagerGetName(groupName, &joinGroup.m_groupName.m_length))
    {
        return ERR_PARAM_ERROR;
    }
    JoinGroupDetailsPacking(&joinGroup, groupName);
    size = ProtocolPackJoinGroup(&joinGroup ,buff);
    
    Transmiting(_clientManager, buff, size);
    
    ProtocolUnpackRespGroup(&response, buff);   
    
    resType = response.m_resp.m_value;
    if (resType != SUCCESS)
    {
        UiErrorHandling(resType);
    }
    else
    {
        UiPrintMsg(ACTION_SUCCESS_TXT);
        GroupManagerCreateGroup(_clientManager->m_group, groupName, _clientManager->m_name, response.m_ip.m_value);
    }
    return ERR_OK;
}

static ErrDefs GetGroupList(ClientManager* _clientManager)
{
    ReqGroupsList groupList;
    RespGroupsList response = {0};
    char buff[BUFF_SIZE] = {0};
    int size = 0;

    GroupListDetailsPacking(&groupList);
    size = ProtocolPackReqGroupsList(&groupList ,buff);
    
    Transmiting(_clientManager, buff, size);
    
    ProtocolUnpackRespGroupsList(&response, buff);  

    UiPrintMsg(ACTION_SUCCESS_TXT);
    UiPrintGroups(response.m_groups, (int) response.m_value);
    return ERR_OK;
}

static ErrDefs LeaveAGroup(ClientManager* _clientManager)
{
    LeaveGroup leaveGroup;
    Response response = {0};
    RespType  resType;
    char groupName[VALUE_LEN];
    char buff[BUFF_SIZE] = {0};
    int size = 0;

    GroupManagerGetName(groupName, &leaveGroup.m_groupName.m_length);
    LeaveGroupDetailsPacking(&leaveGroup, groupName);
    size = ProtocolPackLeaveGroup(&leaveGroup ,buff);
    Transmiting(_clientManager, buff, size);
    ProtocolUnpackResponse(&response, buff);  

    resType = response.m_value;
    if (resType != SUCCESS)
    {
        UiErrorHandling(resType);
    }
    else
    {
        UiPrintMsg(ACTION_SUCCESS_TXT);
        GroupManagerLeaveGroup(_clientManager->m_group, groupName);
    }
    return ERR_OK;
}

static ErrDefs SendLogOut(ClientManager* _clientManager)
{
    LogOut logout;
    Response response = {0};
    RespType  resType;
    char buff[BUFF_SIZE] = {0};
    int size = 0;

    LogoutDetailsPacking(&logout, _clientManager->m_name);
    size = ProtocolPackLogOut(&logout ,buff);
    Transmiting(_clientManager, buff, size);
    ProtocolUnpackResponse(&response, buff);  

    resType = response.m_value;
    if (resType != SUCCESS)
    {
        UiErrorHandling(resType);
    }
    else
    {
        LogoutClient(_clientManager);
    }
    return ERR_OK;
}

static void LogoutClient(ClientManager* _clientManager)
{
    GroupManagerLeaveAllGroups(_clientManager->m_group);
    UiPrintMsg(ACTION_SUCCESS_TXT);
    UiPrintMsg(LOGGED_OUT_TXT);
    _clientManager->m_logged = LOGGED_OFF;
    return;
}

static void JoinGroupDetailsPacking(JoinGroup* _group, char* _groupName)
{
    _group->m_type = JOIN_GROUP;
    _group->m_length = 0;
    _group->m_groupName.m_type = NAME;
    _group->m_groupName.m_length = strlen(_groupName);
    strcpy(_group->m_groupName.m_value, _groupName);
    _group->m_groupName.m_value[_group->m_groupName.m_length - 1] = '\0';
    return;
}

static void LogoutDetailsPacking(LogOut* _user, char* _userName)
{
    _user->m_type = LOGOUT;
    _user->m_length = 0;
    _user->m_userName.m_length = strlen(_userName);
    _user->m_userName.m_type = NAME;
    strcpy(_user->m_userName.m_value, _userName);
    return;
}

static void GroupDetailsPacking(CreateGroup* _newGroup, char* _groupName)
{
    _newGroup->m_type = CREATE_GROUP;
    _newGroup->m_length = 0;
    _newGroup->m_groupName.m_type = NAME;
    strcpy(_newGroup->m_groupName.m_value, _groupName);
    _newGroup->m_groupName.m_value[_newGroup->m_groupName.m_length - 1] = '\0';
    return;
}

static void LeaveGroupDetailsPacking(LeaveGroup* _group, char* _groupName)
{
    _group->m_type = LEAVE_GROUP;
    _group->m_length = 0;
    _group->m_groupName.m_type = NAME;
    strcpy(_group->m_groupName.m_value, _groupName);
    _group->m_groupName.m_value[_group->m_groupName.m_length - 1] = '\0';
    return;
}

static void GroupListDetailsPacking(ReqGroupsList* _group)
{
    _group->m_type = REQ_GROUP_LIST;
    _group->m_length = 0;
    return;
}

static void ChangeSigAction (ClientManager* _clientManager)
{
    struct sigaction sa;

    sa.sa_handler = CloseApp;
    sa.sa_flags = 0; 
    sigemptyset(&sa.sa_mask);

    if (sigaction(SIGINT, &sa, (void*) _clientManager) == -1) 
	{
        perror("sigaction");
	}
	return;
}

static void CloseApp (int sig)
{
    g_run = APP_SHUTING_DOWN;
	return;
}

static void ShutDown(ClientManager* _clientManager)
{
    
    ClientManagerDestroy(& _clientManager);
    printf("\nBye bye\n");
    return;
}