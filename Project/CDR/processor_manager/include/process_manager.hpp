#ifndef PROCESS_MANAGER_HPP
#define PROCESS_MANAGER_HPP


#include "tcp_server.hpp"
#include "Query_handler.hpp"
#include "data_storage.hpp"
#include "input_manager.hpp"
#include "cdr.hpp"


namespace advcpp
{


class ProcessManager
{
public:
    ProcessManager(int a_portNum, int a_sizeListenQueue, int a_maxClients);
    void Run();
private:
    DataStorage m_ds;
    QueryInsideManager m_handlerUI;
    InputManager<Cdr*> m_cdrManager;

};

ProcessManager::ProcessManager(int a_portNum, int a_sizeListenQueue, int a_maxClients)
:   m_handlerUI(a_portNum, a_sizeListenQueue, a_maxClients, m_ds)
{
    m_cdrManager.Run(m_ds);
}

void ProcessManager::Run()
{
    while(1);
}

}



#endif /*process_manager.hpp*/
