#ifndef PROTOCOL_UI_HPP
#define	PROTOCOL_UI_HPP

typedef unsigned int uint;
typedef unsigned char uchar;
typedef unsigned short ushort;

namespace advcpp
{

const size_t MSI_LENGTH = 16;
const size_t OPERATOR_NAME_LENGTH = 65;


const uint MAX_CLIENTS = 100;



enum ReqQuery
{
	ONE_CLIENT_REQ = 222,//one client
	ALL_CLIENTS_REQ,//all clients
	ONE_OPERATOR_REQ,//one operator
	ALL_OPERATORS_REQ,//all operators
	REQ_QUERY_ERR
};

enum Query
{
	ONE_CLIENT = 112,//one client
	ALL_CLIENTS,//all clients
	ONE_OPERATOR,//one operator
	ALL_OPERATORS,//all operators
	CLIENT_NOT_FOUND,
	OPERATOR_NOT_FOUND,
	QUERY_ERR,
	DEFAULT = 0
};


struct RequestClient
{
	uchar m_type; //Byte
	uchar m_length;
	uint m_imsi;
};

struct RequestClients
{
	uchar m_type;
};

struct RequestOperator
{
	uchar m_type;
	uchar m_length;
	uchar m_value[OPERATOR_NAME_LENGTH];
};

struct RequestOperators
{
	uchar m_type;
};

struct ClientProtocol
{
	uchar m_length;
	char m_imsi[MSI_LENGTH];
	uint m_totalMinutesIn;
	uint m_totalMinutesOut;
	uint m_totalMinutesInOutside;
	uint m_totalMinutesOutOutside;
	uint m_totalSmsIn;
	uint m_totalSmsOut;
	uint m_totalSmsInOutside;
	uint m_totalSmsOutOutside;
	uint m_download;
	uint m_upload;
};

struct OperatorProtocol
{
	uint m_MccAndMnc;
	uchar m_length;
	char m_name[OPERATOR_NAME_LENGTH];
	uint m_totalMinutesIn;
	uint m_totalMinutesOut;
	uint m_totalSmsIn;
	uint m_totalSmsOut;
};


struct ResponseQueryClients
{
	uchar m_type;
	uchar m_numOfClients;
	ClientProtocol m_clients[MAX_CLIENTS];
};

struct ResponseQueryOperators
{
	uchar m_type;
	uint m_numOfOperators;
	OperatorProtocol m_operators[MAX_CLIENTS];
};

struct ResponseQueryOperatorNotFound
{
	uchar m_type;
};

struct ResponseQueryClientNotFound
{
	uchar m_type;
};

////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////

}//namespace advcpp

#endif	//PROTOCOL_HPP























