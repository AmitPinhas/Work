#ifndef QUERY_HANDLER_HPP
#define QUERY_HANDLER_HPP

#include "tcp_server.hpp"
#include "stddef.h"
#include "protocol_handler_ui.hpp"
#include "commons.hpp"
#include "data_storage.hpp"
#include "thread.hpp"

namespace advcpp
{

class HandlerRequest
{
public:
    HandlerRequest(DataStorage& a_ds);
    int operator()(advcpp::Socket* a_sock, char* a_buffer, size_t a_size);

private:
   DataStorage& m_refDS;
};




class RunServerQuery: public IRunnable
{
public:
    RunServerQuery(int a_portNum, int a_sizeListenQueue, int a_maxClients, HandlerRequest a_app);
    void Run() NOEXCEPT;

private:
    TCPServer<HandlerRequest> m_serverUI;
};


class QueryInsideManager
{
public:
    QueryInsideManager(int a_portNum, int a_sizeListenQueue, int a_maxClients, DataStorage& a_refDS);

private:
    HandlerRequest m_handlerRequest;
    RunServerQuery m_serverRun;
};

}




#endif /*Query_handler.hpp*/
