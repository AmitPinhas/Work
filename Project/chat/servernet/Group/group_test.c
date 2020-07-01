#include <stdio.h>
#include <string.h>
#include "protocol.h"
#include "chatprotocol.h"
#include "Group.h" 

int main()
{
	CreateGroup createGroupVar, createGroupNew ;
	JoinGroup joinGroupVar, joinGroupNew ;	
	LeaveGroup leaveGroupVar, leaveGroupNew ;		
	RespGroupsList respGroupsListVar, respGroupsListNew ;
	char msg[VALUE_LEN], msg2[VALUE_LEN], msg3[VALUE_LEN] ;
	
	
	printf("Create Group Positive\n");
	
	createGroupVar.m_type	= CREATE_GROUP ;
	createGroupVar.m_length	= 0 ;
	createGroupVar.m_groupName.m_type = NAME ;
	createGroupVar.m_groupName.m_length = 5 ;			
	strcpy(createGroupVar.m_groupName.m_value , "Group" ) ;
	
	
	ProtocolPackCreateGroup (&createGroupVar, msg) ;
	
	ProtocolUnpackCreateGroup(&createGroupNew, msg) ;

	printf("type Create Group %d\n" , createGroupNew.m_type ) ;
	printf("length Create Group %d\n" , createGroupNew.m_length ) ;
	printf("type name %d\n" , createGroupNew.m_groupName.m_type );
	printf("length name %d\n" , createGroupNew.m_groupName.m_length );			
	printf("group name %s\n" , createGroupNew.m_groupName.m_value );
	
	printf("\nJoin Group Positive\n");	
	
	joinGroupVar.m_type	= JOIN_GROUP ;
	joinGroupVar.m_length	= 0 ;
	joinGroupVar.m_groupName.m_type = NAME ;
	joinGroupVar.m_groupName.m_length = 5 ;			
	strcpy(joinGroupVar.m_groupName.m_value , "Group" ) ;
	
	ProtocolPackJoinGroup (&joinGroupVar, msg2) ;
	
	ProtocolUnpackJoinGroup(&joinGroupNew, msg2) ;

	printf("type Join Group %d\n" , joinGroupNew.m_type ) ;
	printf("length Join Group %d\n" , joinGroupNew.m_length ) ;
	printf("type name %d\n" , joinGroupNew.m_groupName.m_type );
	printf("length name %d\n" , joinGroupNew.m_groupName.m_length );			
	printf("group name %s\n" , joinGroupNew.m_groupName.m_value );

	printf("\nLeave Group Positive\n");	
	
	leaveGroupVar.m_type	= LEAVE_GROUP ;
	leaveGroupVar.m_length	= 0 ;
	leaveGroupVar.m_groupName.m_type = NAME ;
	leaveGroupVar.m_groupName.m_length = 5 ;			
	strcpy(leaveGroupVar.m_groupName.m_value , "Group" ) ;
	
	
	ProtocolPackLeaveGroup (&leaveGroupVar, msg2) ;
	
	ProtocolUnpackLeaveGroup(&leaveGroupNew, msg2) ;

	printf("type Leave Group %d\n" , leaveGroupNew.m_type ) ;
	printf("length Leave Group %d\n" , leaveGroupNew.m_length ) ;
	printf("type name %d\n" , leaveGroupNew.m_groupName.m_type );
	printf("length name %d\n" , leaveGroupNew.m_groupName.m_length );			
	printf("group name %s\n" , leaveGroupNew.m_groupName.m_value );
	
	
	printf("\nResp Groups List Positive\n");		
	
	respGroupsListVar.m_type = RESP_GROUPS_LIST ;
	respGroupsListVar.m_length = 1 ;
	respGroupsListVar.m_value = 1 ;	
	respGroupsListVar.m_groups[0].m_type =  NAME ;
	respGroupsListVar.m_groups[0].m_length = 5 ;
	strcpy( respGroupsListVar.m_groups[0].m_value , "Group" ) ;
	
	ProtocolPackRespGroupsList(&respGroupsListVar, msg3) ; 		
	ProtocolUnpackRespGroupsList(&respGroupsListNew, msg3) ;
	
	printf("Resp Groups Group %d\n" , respGroupsListNew.m_type ) ;
	printf("length Groups Group %d\n" , respGroupsListNew.m_length ) ;
	printf("value Groups Group %d\n" , respGroupsListNew.m_value ) ;	
	printf("type name %d\n" , respGroupsListNew.m_groups[0].m_type );
	printf("length name %d\n" , respGroupsListNew.m_groups[0].m_length );			
	printf("group name %s\n" , respGroupsListNew.m_groups[0].m_value );	 	
			
	return 0 ;
}
