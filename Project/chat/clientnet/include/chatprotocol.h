#ifndef __CHAT_PROTOCOL_H__
#define __CHAT_PROTOCOL_H__

#define VALUE_LEN 255
#define RESP_SIZE 1
#define MAX_GROUP 100
#define MULT_PORT 1500

typedef enum RespType
{
    SUCCESS = 0,
    INVALID_USERNAME,
    INVALID_PASSWORD,
    EXISTING_USERNAME,
    INVALID_GROUP_ID,
    USER_ALREADY_IN_USE,
    SERVER_ERROR,
    MULTI_ADDRESS_DEPLETED
}RespType;


typedef enum Types
{

    SIGNUP = 1,
    NAME,
    PASSWORD,
    RESPONSE,
    CREATE_GROUP,
    LOGIN,
    LOGOUT,
    REQ_GROUP_LIST,
    RESP_GROUPS_LIST,
    IP_NUMBER,
    JOIN_GROUP,
    LEAVE_GROUP,
    RESP_GROUP,
    MSG_DATA,
    MSG

}Types;



typedef struct Name
{

    char    m_type;    
    char    m_length;
    char    m_value[ VALUE_LEN ];

} Name;

/*----------------------------------------------------------*/

typedef struct Password
{

    char    m_type;    
    char    m_length;
    char    m_value[ VALUE_LEN ];

} Password;


/*----------------------------------------------------------*/

typedef struct SignUp
{
    char   	 m_type;
    char   	 m_length;
    char   	 m_value;
    Name   	 m_userName;
    Password    m_password;

} SignUp;

/*----------------------------------------------------------*/


typedef struct Response
{
    char   		 m_type;
    char   		 m_length;
    char   		 m_value;

} Response;


/*----------------------------------------------------------*/


typedef struct LogIn
{
    char   	 m_type;
    char   	 m_length;
    char   	 m_value;
    Name   	 m_userName;
    Password    m_password;

} LogIn;


/*----------------------------------------------------------*/

typedef struct LogOut
{
    char   	 m_type;
    char   	 m_length;
    char   	 m_value;
    Name   	 m_userName;

} LogOut;


/*----------------------------------------------------------*/


typedef struct ReqGroupsList
{
    char   	 m_type;
    char   	 m_length;
    char   	 m_value;

} ReqGroupsList;



/*----------------------------------------------------------*/

typedef struct RespGroupsList
{
    char   	 m_type;
    char   	 m_length;
    char   	 m_value;
    Name   	 m_groups[ MAX_GROUP ];

} RespGroupsList;


/*----------------------------------------------------------*/

typedef struct IpNumber
{
    char   	 m_type;
    char   	 m_length;
    char   	 m_value[ VALUE_LEN ];

} IpNumber;

/*----------------------------------------------------------*/

typedef struct JoinGroup
{
    char   	 m_type;
    char   	 m_length;
    char   	 m_value;
    Name   	 m_groupName;

} JoinGroup;

/*----------------------------------------------------------*/

typedef struct LeaveGroup
{
    char   	 m_type;
    char   	 m_length;
    char   	 m_value;
    Name   	 m_groupName;    

} LeaveGroup;

/*----------------------------------------------------------*/

typedef struct RespGroup
{
    char   	 m_type;
    char   	 m_length;
    char   	 m_value;
    Response     m_resp;
    IpNumber    m_ip;

} RespGroup;

/*----------------------------------------------------------*/

typedef struct CreateGroup
{
    char   	 m_type;
    char   	 m_length;
    char   	 m_value;
    Name   	 m_groupName;

} CreateGroup;

/*----------------------------------------------------------*/

typedef struct Msg
{
    char   	 m_type;
    char   	 m_length;
    char   	 m_value[ VALUE_LEN ];

} Msg;

typedef struct MsgData
{
    char   	 m_type;
    char   	 m_length;
    char   	 m_value;
    Name   	 m_userName;
    Msg   	 m_message;

} MsgData;

/*----------------------------------------------------------*/



#endif    /*__PROTOCOL_H__*/
























