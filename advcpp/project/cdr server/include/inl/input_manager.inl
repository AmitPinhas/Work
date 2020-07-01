#include <string.h> // strcpy
#include <algorithm> // std::for_each

#include "protocol_reader.hpp"

namespace advcpp
{
template <typename Type>      
InputManager<Type>::InputManager(size_t a_sizeQueueCdrs)
: m_cdrs(a_sizeQueueCdrs)
{
}

template <typename Type> 
InputManager<Type>::~InputManager()
{
    typename std::vector<DequeueCdr<Type>* >::iterator begin = m_dequeueCdrs.begin();
    typename std::vector<DequeueCdr<Type>* >::iterator end = m_dequeueCdrs.end();

    std::for_each(begin, end, DeleteDequeue);

    std::vector<Thread*>::iterator beginThreads = m_threads.begin();
    std::vector<Thread*>::iterator endThreads = m_threads.end();  

    std::for_each(beginThreads, endThreads, DeleteThreads);      
}

template <typename Type> 
void InputManager<Type>::DeleteDequeue(DequeueCdr<Type>* a_dequeue)
{
    delete a_dequeue;
}

template <typename Type> 
void InputManager<Type>::DeleteThreads(Thread* a_thread)
{
    delete a_thread;    
}

template <typename Type>  
void InputManager<Type>::Run(size_t a_numThreads,  int a_portNum, int a_sizeListenQueue, int a_maxClients)
{
    RunServer<EnqueueCdr<Type> > runServer(a_portNum, a_sizeListenQueue, a_maxClients, EnqueueCdr<Type>(m_cdrs));
    Thread threadrunServer(&runServer);

    DequeueThreads(a_numThreads);  

    threadrunServer.Join();
}

template <typename Type>  
void InputManager<Type>::DequeueThreads(size_t a_numThreads)
{
    for(size_t index = 0; index < a_numThreads; ++index)
    {
        DequeueCdr<Type> *dequeue = new DequeueCdr<Type>(m_cdrs);
        m_dequeueCdrs.push_back(dequeue);
    }

    for(size_t index = 0; index < a_numThreads; ++index)
    {
        Thread *threadDequeue = new Thread(m_dequeueCdrs[index]); 
        m_threads.push_back(threadDequeue);
    }    

    for(size_t index = 0; index < a_numThreads; ++index)
    {
        m_threads[index]->Join();
    }
}

template <typename Type>
DequeueCdr<Type>::DequeueCdr(WaitableQueue<Type>& a_cdrs)
: m_cdrs(a_cdrs)
{
}

template <typename Type>
void DequeueCdr<Type>::Run() NOEXCEPT
{
    while(true)
    {
        Cdr *cdr;
        m_cdrs.Dequeue(cdr);

        std::cout << *cdr << '\n';
    }
}

template <typename NewMessage>
RunServer<NewMessage>::RunServer(int a_portNum, int a_sizeListenQueue, int a_maxClients, NewMessage a_newMessage)
: m_tcpServer(a_portNum, a_sizeListenQueue, a_maxClients, a_newMessage)
{
}

template <typename NewMessage>
void RunServer<NewMessage>::Run() NOEXCEPT
{
   m_tcpServer.Run(); 
}

template <typename Type>
EnqueueCdr<Type>::EnqueueCdr(WaitableQueue<Type>& a_cdrs)
: m_cdrs(a_cdrs)
{
}

template <typename Type>
void EnqueueCdr<Type>::operator()(advcpp::Socket* a_socket,const char* a_buffer, size_t )
{
    Cdr *cdr = new Cdr;

    CdrCreator(cdr, a_buffer);
    
	if(a_buffer[0] > 0)
	{
    	m_cdrs.Enqueue(cdr);
    }	

    char msgSend[] = "thank you";

    advcpp::TCPServer<EnqueueCdr<Type> >::SendMessage(a_socket, msgSend, sizeof(msgSend));    
}

void CdrCreator(Cdr* a_cdr, const char* a_buffer)
{
    Types type = static_cast<Types>(a_buffer[0]);

    switch(type)
    {
        case CALL:  ProtocolReader::ProtocolUnpackCall(a_cdr, a_buffer);
                    break;

        case SMS:   ProtocolReader::ProtocolUnpackSms(a_cdr, a_buffer);
                    break;

        case GPRS:  ProtocolReader::ProtocolUnpackData(a_cdr, a_buffer);
                    break;    

        default:
                    break;
    }
}
} // namespace advcpp
