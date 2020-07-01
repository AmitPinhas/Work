
#include "protocol_ui.hpp" //msg
#include <cstddef> //size_t
#include <algorithm>
#include <stdlib.h>
#include <cstring>
#include "translator.hpp"

namespace advcpp
{

void Translator::ClientDecode(ClientProtocol* a_client, char* a_buffer) // exception NULL
{
	if(!a_client || !a_buffer)
	{
		throw "pointer NULL\n";
	}
    size_t len=0;
	
    /*===length of imsi===*/
    a_client->m_length = a_buffer[0]; 
    a_buffer += 1;
    len+=1;
    
	/*===IMSI===*/	    
    memcpy(&a_client->m_imsi, a_buffer, a_client->m_length);
    a_client->m_imsi[ static_cast<int>(a_client->m_length) ] = '\0';
    len = a_client->m_length; 
    a_buffer += len;
    
    /*===Minutes In===*/
    len = sizeof(a_client->m_totalMinutesIn);
    memcpy(&(a_client->m_totalMinutesIn), a_buffer, len);
    a_buffer += len;
    
    /*===Minutes Out===*/
    len = sizeof(a_client->m_totalMinutesOut);
    memcpy(&(a_client->m_totalMinutesOut), a_buffer, len);
    a_buffer += len;

    /*===Minutes In Outside===*/
    len = sizeof(a_client->m_totalMinutesInOutside);
    memcpy(&(a_client->m_totalMinutesInOutside), a_buffer, len);
    a_buffer += len;
    
    /*===Minutes Out Outside===*/
    len = sizeof(a_client->m_totalMinutesOutOutside);
    memcpy(&(a_client->m_totalMinutesOutOutside), a_buffer, len);
    a_buffer += len;

    /*===Sms In===*/
    len = sizeof(a_client->m_totalSmsIn);
    memcpy(&(a_client->m_totalSmsIn), a_buffer, len);
    a_buffer += len;

    /*===Sms Out===*/
    len = sizeof(a_client->m_totalSmsOut);
    memcpy(&(a_client->m_totalSmsOut), a_buffer, len);
    a_buffer += len;

    /*===Sms In===*/
    len = sizeof(a_client->m_totalSmsInOutside);
    memcpy(&(a_client->m_totalSmsInOutside), a_buffer, len);
    a_buffer += len;

    /*===Sms Out===*/
    len = sizeof(a_client->m_totalSmsOutOutside);
    memcpy(&(a_client->m_totalSmsOutOutside), a_buffer, len);
    a_buffer += len;

    /*===Download===*/
    len = sizeof(a_client->m_download);
    memcpy(&(a_client->m_download), a_buffer, len);
    a_buffer += len;

    /*===Upload===*/
    len = sizeof(a_client->m_upload);
    memcpy(&(a_client->m_upload), a_buffer, len);
    a_buffer += len;

}

void Translator::ClientRequestDecode(ResponseQueryClients* a_response, char* a_buffer)  // exception NULL
{
    if(!a_response || !a_buffer)
	{
		throw "pointer NULL\n";
	}

    size_t len=0;

    a_response->m_type = a_buffer[0]; 
    a_buffer += 1;
    len+=1;

    len = sizeof(a_response->m_numOfClients);
    memcpy(&(a_response->m_numOfClients), a_buffer, len);
    a_buffer += len;

    for(uint i = 0; i < a_response->m_numOfClients; ++i)
    {
        ClientDecode(&(a_response->m_clients[i]), a_buffer );
    }
}

size_t Translator::ClientRequestEncode(RequestClient* a_client, char* a_buffer) // exception NULL
{
    if(!a_client || !a_buffer)
	{
		throw "pointer NULL\n";
	}

    int index=0;
	size_t bytes;
	
	/* type request client */
	bytes = sizeof(a_client->m_type);
	memcpy(a_buffer, &a_client->m_type, bytes);
	index += bytes;

	/* length */
	bytes = sizeof(a_client->m_length);
	memcpy(a_buffer + index, &a_client->m_length, bytes);
	index += bytes;
	
    /* imsi */
	bytes = static_cast<int>(a_client->m_length);
	memcpy(a_buffer + index, &a_client->m_imsi, bytes);
	index += bytes;
		
	return index;   
}

size_t Translator::RequestOperatorEncode(RequestOperator* a_operator, char* a_buffer) // exception NULL
{
    if(!a_operator || !a_buffer)
	{
		throw "pointer NULL\n";
	}

    int index=0;
	size_t bytes;
	
	/* type request client */
	bytes = sizeof(a_operator->m_type);
	memcpy(a_buffer, &a_operator->m_type, bytes);
	index += bytes;

	/* length */
	bytes = sizeof(a_operator->m_length);
	memcpy(a_buffer + index, &a_operator->m_length, bytes);
	index += bytes;
	
    /* imsi */
	bytes = static_cast<int>(a_operator->m_length);
	memcpy(a_buffer + index, &a_operator->m_value, bytes);
	index += bytes;
		
	return index;   
}

void Translator::OperatorDecode(OperatorProtocol* a_operator, char* a_buffer) // exception NULL
{
    if(!a_operator || !a_buffer)
	{
		throw "pointer NULL\n";
	}

    size_t len = 0;
	//size_t offset = 2; //hard coded must be transver from out
    /*===MccAndMnc===*/
    len = sizeof(a_operator->m_MccAndMnc);
    memcpy(&a_operator->m_MccAndMnc, a_buffer, len);
    a_buffer += len;
    //offset+= len;


	/*===length===*/
    len = sizeof(a_operator -> m_length);
    memcpy(&a_operator -> m_length, a_buffer, len );
    //a_operator -> m_length =  a_buffer[6];
    a_buffer += len;

    /*===name===*/
    memcpy(&a_operator->m_name, a_buffer, a_operator->m_length);
    a_operator->m_name[ a_operator->m_length  ] = '\0';
    len = a_operator->m_length; 
    a_buffer += len;
    
    /*===total Minutes In===*/
    len = sizeof(a_operator->m_totalMinutesIn);
    memcpy(&(a_operator->m_totalMinutesIn), a_buffer, len);
    a_buffer += len;
    
    /*===total Minutes Out===*/
    len = sizeof(a_operator->m_totalMinutesOut);
    memcpy(&(a_operator->m_totalMinutesOut), a_buffer, len);
    a_buffer += len;

    /*===total Sms In===*/
    len = sizeof(a_operator->m_totalSmsIn);
    memcpy(&(a_operator->m_totalSmsIn), a_buffer, len);
    a_buffer += len;

    /*===total Sms Out===*/
    len = sizeof(a_operator->m_totalSmsOut);
    memcpy(&(a_operator->m_totalSmsOut), a_buffer, len);
    a_buffer += len;

}

void Translator::OperatorRequestDecode(ResponseQueryOperators* a_response, char* a_buffer) // exception NULL
{
    if(!a_response || !a_buffer)
	{
		throw "pointer NULL\n";
	}

    a_response->m_type = a_buffer[0]; 
    ++a_buffer;

    size_t len=0;
    len = sizeof(a_response->m_numOfOperators);
    memcpy(&(a_response->m_numOfOperators), a_buffer, len);
    a_buffer += len;

    for(uint i = 0; i < a_response->m_numOfOperators; ++i)
    {
        OperatorDecode(&(a_response->m_operators[i]), a_buffer );
    }
}

}
