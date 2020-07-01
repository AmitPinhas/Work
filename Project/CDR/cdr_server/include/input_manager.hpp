#ifndef INPUT_MANAGER_HPP
#define INPUT_MANAGER_HPP

#include <vector>
#include "commons.hpp" // UnCopyable
#include "waitable_queue.hpp"
#include "tcp_server.hpp"
#include "cdr.hpp"
#include "data_storage.hpp"


namespace advcpp
{
template <typename Type>
class DequeueCdr;

template <typename Type>    
class InputManager : private UnCopyable
{
public:
    explicit InputManager(size_t a_sizeQueueCdrs = 1024);

    ~InputManager();

    void Run(DataStorage& m_refDS, size_t a_numThreads = 10, int a_portNum = 5050, int a_sizeListenQueue = 1024, int a_maxClients = 1024);

private:
    void DequeueThreads(DataStorage& m_refDS, size_t a_numThreads);
    static void DeleteDequeue(DequeueCdr<Type>* a_dequeue);
    static void DeleteThreads(Thread* a_thread);

private:
    WaitableQueue<Type> m_cdrs;
    std::vector<DequeueCdr<Type>* > m_dequeueCdrs;
    std::vector<Thread*> m_threads; 

};

template <typename NewMessage>
class RunServer : public IRunnable
{
public:
    RunServer(int a_portNum, int a_sizeListenQueue, int a_maxClients, NewMessage a_newMessage);

    virtual void Run() NOEXCEPT;

private:
    TCPServer<NewMessage> m_tcpServer;
};

template <typename Type>
class EnqueueCdr
{
public:
    explicit EnqueueCdr(WaitableQueue<Type>& a_cdrs);

    void operator()(advcpp::Socket* a_socket,const char* a_buffer, size_t);

private:
    WaitableQueue<Type>& m_cdrs;

};

template <typename Type>
class DequeueCdr : public IRunnable
{
public:
    explicit DequeueCdr(WaitableQueue<Type>& a_cdrs, DataStorage& a_refDS);

    virtual void Run() NOEXCEPT;

private:
    WaitableQueue<Type>& m_cdrs;
    DataStorage& m_refDS;
};

void CdrCreator(Cdr* a_cdr, const char* a_buffer);
} // namespace advcpp

#endif // INPUT_MANAGER_HPP
