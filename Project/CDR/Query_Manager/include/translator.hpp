#ifndef TRANSLATOR_HPP
#define TRANSLATOR_HPP

#include "protocol_ui.hpp" //msg

namespace advcpp
{

struct Translator 
{
public:
    
    static void ClientDecode(ClientProtocol* a_client, char* a_buffer);
    
    static size_t ClientRequestEncode(RequestClient* a_client,char* a_buffer);

    static void ClientRequestDecode(ResponseQueryClients* a_response, char* a_buffer);

    static void OperatorRequestDecode(ResponseQueryOperators* a_response, char* a_buffer);

    static void OperatorDecode(OperatorProtocol* a_operator, char* a_buffer);

    static size_t RequestOperatorEncode(RequestOperator* a_operator, char* a_buffer);
};



}


#endif /*translator.hpp*/
