#ifndef _DEFAULT_SOURCE
#define _DEFAULT_SOURCE
#endif
#include <stdio.h> /* ptintf */
#include <stdlib.h> /* malloc, size_t */
#include <string.h> /* strcpy */ 
#include <signal.h> /* kill */ 
#include "../include/group.h" /* group typedef */
#include "../include/ui.h" /* ui functions */
#include "../../include/chatprotocol.h" /* JoinGroup */
#include "../../include/protocol.h"   /* pack, unpack */
#include "../../include/HashMap.h"  /* Groups container */
#include "../include/msgque.h"   /* msgque */

#define GET_GROUP_NAME_TXT      "Please enter name for the group"
#define NAME_ERROR              "Name is not legal, please try again"
#define SELECTION_TXT           "Enter the number of action:"


#define OPTION_SIZE             6
#define GROUP_NAME_SIZE         50
#define TRUE                    1
#define FAILED                  0
#define HASH_CAPACITY           100
#define IP_SIZE                 16
#define ADDRESS_SIZE            255

struct GroupManager {
    HashMap*        m_myGroups;
    int             m_groupMenu;
    int             m_msgqueId;
};                          

typedef struct GroupItem
{
    char            m_groupName[VALUE_LEN];
    char            m_groupIp[IP_SIZE];
    int             m_pidFirst;
    int             m_pidSecond; 
}GroupItem ;


static size_t HashGroup(const void* _groupName);
static int EqualGroup(const void* _groupName1, const void* _groupName2);
static GroupItem* GroupItemCreate(const char* _groupname);
static void GroupItemDestroy (void* _gItem);
static void GroupInit(GroupManager* _gManger, GroupItem* _gItem, char* _userName, const char* _ip);
static void OpenChatWindows (const char* _ip, const char* _userName, int _msgId);
static ErrDefs CreateMsgId(GroupManager* _gManger);
static ErrDefs GetPid(GroupManager* _gManger, pid_t* _pid);
static ErrDefs KillChatWindows(GroupItem* _gItem);
/******************************************************/
/************     Public      *************************/
/******************************************************/
GroupManager* GroupManagerCreate()
{
    GroupManager* newGroupManager = NULL;

    if (NULL == (newGroupManager = (GroupManager*) malloc (sizeof(GroupManager))))
    {
        return NULL;
    }

    if (NULL == (newGroupManager->m_myGroups = HashMapCreate(HASH_CAPACITY, HashGroup, EqualGroup)))
    {
        free(newGroupManager);
        return NULL;
    }

    CreateMsgId(newGroupManager);
    return newGroupManager;
}

void GroupManagerDestroy (GroupManager** _gManger)
{
    HashMap* map = NULL;
    if (NULL != _gManger && NULL != *_gManger)
    {
        map = (*_gManger)->m_myGroups;
        HashMapDestroy(&map, NULL, GroupItemDestroy);
        MsgQueDestroy((*_gManger)->m_msgqueId);
        free(*_gManger);
        *_gManger = NULL;
    }
    return;
}

int GroupManagerSelection(GroupManager* _gManger)
{
    char* options[OPTION_SIZE] = {"Create a group", "Get all exisiting groups", "Join group", "Leave group", "Logout", "Exit"};

    return UiSelectGroupAction(options, OPTION_SIZE, SELECTION_TXT);
}

ErrDefs GroupManagerGetName(char* _groupName, char* _nameLen)
{
    if (ERR_PARAM_ERROR == UiGetGroupName(_groupName, GET_GROUP_NAME_TXT, _nameLen))
    {
        return ERR_PARAM_ERROR;
    }
    return ERR_OK;
}

ErrDefs GroupManagerCreateGroup(GroupManager* _gManger,const char* _groupName, char* _userName, const char* _ip)
{
    GroupItem* newItem;

    if (NULL == (newItem = GroupItemCreate(_groupName)))
    {
        return ERR_ALLOCATION_FAILED;
    }

    if (MAP_SUCCESS != HashMapInsert(_gManger->m_myGroups, _groupName, (void*) newItem))
    {
        free(newItem);
        return ERR_GROUP_CREATE_FAILED;
    }
    GroupInit(_gManger, newItem, _userName, _ip);
    return ERR_OK;
}

ErrDefs GroupManagerLeaveGroup (GroupManager* _gManger,const char* _groupName)
{
    void* gItem = NULL;
    
    if( MAP_SUCCESS != HashMapRemove(_gManger->m_myGroups, _groupName, &gItem))
    {
        return ERR_GROUP_NOT_EXIST;
    }
    
    GroupItemDestroy(gItem);
    return ERR_OK;
}

ErrDefs GroupManagerLeaveAllGroups (GroupManager* _gManger)
{
    HashMapDestroy(&_gManger->m_myGroups, NULL, GroupItemDestroy);

    if (NULL == (_gManger->m_myGroups = HashMapCreate(HASH_CAPACITY, HashGroup, EqualGroup)))
    {
        MsgQueDestroy(_gManger->m_msgqueId);
        free(_gManger);
        return ERR_ALLOCATION_FAILED;
    }
    return ERR_OK;
}

/******************************************************/
/************     Locals      *************************/
/******************************************************/
static size_t HashGroup(const void* _groupName) 
{
	int sum=0, i ;
	char *groupName = (char*)_groupName ;
	
	for ( i = 0 ; groupName[i] != '\0' ; ++i )
	{
		sum += groupName[i] ;
	}
	return sum ;
}


static int EqualGroup(const void* _groupName1, const void* _groupName2) 
{

	if ( 0 ==  ( strcmp((char*)_groupName1, (char*)_groupName2) ) ) 
	{
		return TRUE ;
	}
	
	return FAILED ;
}

static GroupItem* GroupItemCreate(const char* _groupname)
{
    GroupItem* newItem = NULL;

    if (NULL == (newItem = (GroupItem*) calloc (1, sizeof(GroupItem))))
    {
        return NULL;
    }

    strcpy(newItem->m_groupName, _groupname);
    return newItem;
}

static void GroupItemDestroy (void* _gItem)
{
    if (NULL != _gItem)
    {
        KillChatWindows(_gItem);
        free(_gItem);
    }
    return;
}

static ErrDefs CreateMsgId(GroupManager* _gManger)
{
    char path[ADDRESS_SIZE] = "/home/student/work/makefile";

    if(ERR_OK != MsgQueCreate(path, &_gManger->m_msgqueId))
    {
        return ERR_SYS_ERROR;
    }
    return ERR_OK;
}

static void GroupInit(GroupManager* _gManger, GroupItem* _gItem, char* _userName, const char* _ip)
{
    strcpy(_gItem->m_groupIp, _ip);
    OpenChatWindows(_ip, _userName, _gManger->m_msgqueId);
    GetPid(_gManger, &_gItem->m_pidFirst);
    GetPid(_gManger, &_gItem->m_pidSecond);
    return;
}

static void OpenChatWindows (const char* _ip, const char* _userName, int _msgId)
{
    char command[ADDRESS_SIZE];
    
    sprintf(command,"gnome-terminal  --geometry=20x20+30+0 -- ./multiApp %d %s %d", MULT_PORT, _ip, _msgId);
    system(command);
    sprintf(command, "gnome-terminal --geometry=20x10+30+500 -- ./senderApp %d %s %s %d", MULT_PORT, _ip, _userName, _msgId);
    system(command);
    return;
}

static ErrDefs GetPid(GroupManager* _gManger, pid_t* _pid)
{
    MsgBuf _msg;
    
    if(ERR_OK != MsgQueRead(_gManger->m_msgqueId, &_msg))
    {
        return ERR_SYS_ERROR;
    
    }
    *_pid = _msg.m_pid;
    return ERR_OK;
}

static ErrDefs KillChatWindows(GroupItem* _gItem)
{
    kill(_gItem->m_pidFirst, SIGINT);
    kill(_gItem->m_pidSecond, SIGINT);
    return ERR_OK;
}
