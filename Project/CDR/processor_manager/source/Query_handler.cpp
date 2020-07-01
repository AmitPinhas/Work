#include "Query_handler.hpp"
#include <cstdlib> // atoi()

namespace advcpp
{


HandlerRequest::HandlerRequest(DataStorage& a_ds)
:   m_refDS(a_ds)
{ 
}


int HandlerRequest::operator()(advcpp::Socket* a_sock, char* a_buffer, size_t)
{
    ProtocolHandlerUI requestAnswer(a_buffer);
    requestAnswer.DecodeQuery();
    switch ( requestAnswer.Request() )
    {
    case ONE_CLIENT:
        {
            std::vector<Client> vec;
            if(!(m_refDS.Find<Client, std::string>(m_refDS, vec ,  &requestAnswer.Name())))
            {
                    IMSI numPelephone ("0000000000");
                    uint data[10] = {999, 999, 999, 999, 999, 999, 999, 999, 999, 999};
                    Client myClient(numPelephone, data[0], data[1], data[2], data[3], data[4], data[5], data[6], data[7], data[8], data[9]);
                    std::vector<Client> vectorClients;
                    vectorClients.push_back(myClient);
                    requestAnswer.EncodeQuery(vectorClients, a_buffer);
                    advcpp::TCPServer<HandlerRequest>::SendMessage(a_sock, a_buffer, 200);   
                }
                else
                {
                    requestAnswer.EncodeQuery(vec, a_buffer);
                    advcpp::TCPServer<HandlerRequest>::SendMessage(a_sock, a_buffer, requestAnswer.EncodedMsgLen());
                }    
        }
    break;

    case ONE_OPERATOR:
    {
        std::vector<Operator> vec;
        uint key = atoi(requestAnswer.Name().c_str());
        if(!(m_refDS.Find<Operator, uint>(m_refDS, vec ,  &key  )))
        {

            requestAnswer.EncodeQuery(vec, a_buffer);
            advcpp::TCPServer<HandlerRequest>::SendMessage(a_sock, a_buffer, requestAnswer.EncodedMsgLen());

        }
        else
        {
            requestAnswer.EncodeQuery(vec, a_buffer);
            advcpp::TCPServer<HandlerRequest>::SendMessage(a_sock, a_buffer, requestAnswer.EncodedMsgLen());
        }
    }
    break;

    default:
    {
        try
        {
            throw "no option exist\n";
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
        
    }
        break;
    }  
    return 1;
}


RunServerQuery::RunServerQuery(int a_portNum, int a_sizeListenQueue, int a_maxClients, HandlerRequest a_app)
:   m_serverUI(a_portNum, a_sizeListenQueue, a_maxClients, a_app)
{    
}

QueryInsideManager::QueryInsideManager(int a_portNum, int a_sizeListenQueue, int a_maxClients, DataStorage& a_refDS)
:  m_handlerRequest(a_refDS)
,   m_serverRun(a_portNum, a_sizeListenQueue, a_maxClients, m_handlerRequest) 
{
    Thread ptr(&m_serverRun);
    ptr.Detach();
}

void RunServerQuery::Run() NOEXCEPT
{
    m_serverUI.Run();
}



}
