#ifndef THREAD_POOL_INL
#define THREAD_POOL_INL


#include "thread_pool.hpp"

#include <iostream>
#include <cassert>

namespace advcpp
{

typedef std::tr1::shared_ptr<Thread> ThreadPtr;

template <typename TaskContainer>
ThreadPool<TaskContainer>::ThreadPool(size_t a_maxWaitingTasks, size_t a_numThreads)  
: m_shutdownFlag(OPEN_FOR_BUSINESS)       
, m_tasks(a_maxWaitingTasks)              
{
    CheckParams(a_maxWaitingTasks, a_numThreads);

    m_workers.Reserve(a_numThreads);

    createThreads(a_numThreads); 
}          

template <typename TaskContainer>
void ThreadPool<TaskContainer>::CheckParams(size_t a_maxWaitingTasks, size_t a_numThreads) const
{
    assert(a_maxWaitingTasks > 0);

    assert(a_numThreads <= DefaultMaxNumThreads());
}

template <typename TaskContainer>
ThreadPool<TaskContainer>::~ThreadPool() NOEXCEPT
{
    assert(shutdownOn() || m_workers.Size() == 0);
}

template <typename TaskContainer>
bool ThreadPool<TaskContainer>::Submit(ITaskPtr a_task)
{
    if(shutdownOff() && a_task)
    {
        m_tasks.Enqueue(a_task);
        return true;       
    }
    return false;
}

template <typename TaskContainer>
void ThreadPool<TaskContainer>::Shutdown()
{
    CloseTheGate();

    WaitForContainerToBeEmpty();

    WakeAndKillAllWorkers();
}

template <typename TaskContainer>
void ThreadPool<TaskContainer>::WakeAndKillAllWorkers()
{
    RemoveWorkers(m_workers.Size());
}

template <typename TaskContainer>
void ThreadPool<TaskContainer>::CloseTheGate()
{
    m_shutdownFlag.Set(CLOSE_FOR_BUSINESS);
}

template <typename TaskContainer>
void ThreadPool<TaskContainer>::WaitForContainerToBeEmpty()
{
    std::tr1::shared_ptr<ShutdownRun> runShutdown(new ShutdownRun(m_tasks));

    Thread threadShutdown(&*runShutdown);
    
    threadShutdown.Join();    
}

template <typename TaskContainer>
void ThreadPool<TaskContainer>::AddWorkers(size_t a_num)
{
    if(shutdownOff())
    {
        createThreads(a_num);
    }
}

template <typename TaskContainer>
void ThreadPool<TaskContainer>::RemoveWorkers(size_t a_num)
{
    size_t numThreadsRemove = std::min(a_num, m_workers.Size());

    WakeWorkers();

    RemoveThreads(numThreadsRemove);
}

template <typename TaskContainer>
void ThreadPool<TaskContainer>::RemoveThreads(size_t a_numThreadsRemove)
{
    while(a_numThreadsRemove-- > 0)
    {
        m_workers.Back().second->Shutdown();           
        m_workers.Back().first->Join();       
        m_workers.PopBack();
    }    
}

template <typename TaskContainer>
void ThreadPool<TaskContainer>::WakeWorkers()
{
    ITaskPtr end(new EndTask(m_tasks));
    m_tasks.Enqueue(end);   
}

template <typename TaskContainer>
void ThreadPool<TaskContainer>::createThreads(size_t a_numThreads)
{
    while(a_numThreads-- > 0)
    {
        std::pair<ThreadPtr, PerformerPtr> worker;
        PerformerPtr performerPtr(new Performer(m_tasks)); 
        ThreadPtr threadPtr(new Thread(&*performerPtr)); 
        worker.first = threadPtr;
        worker.second = performerPtr;
        m_workers.PushBack(worker);
    }
}

template <typename TaskContainer>
bool ThreadPool<TaskContainer>::shutdownOff() const
{
    return !m_shutdownFlag.Get();
}

template <typename TaskContainer>
bool ThreadPool<TaskContainer>::shutdownOn() const
{
    return m_shutdownFlag.Get();    
}

template <typename TaskContainer>
bool ThreadPool<TaskContainer>::tasksNotEmpty() const
{
    return m_tasks.Size();
}

template <typename TaskContainer>
ThreadPool<TaskContainer>::Performer::Performer(TaskContainer& a_tasks)
: m_tasks(a_tasks)
, m_threadShutdown(1)
{
}

template <typename TaskContainer>
void ThreadPool<TaskContainer>::Performer::Run() NOEXCEPT
{
    while(m_threadShutdown.Get()) 
    {
        ITaskPtr taskPtr;
        m_tasks.Dequeue(taskPtr);
        try
        {
            taskPtr->Execute();
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
        catch(...)
        {
        
        }
    }
}

template <typename TaskContainer>
void ThreadPool<TaskContainer>::Performer::Shutdown()
{
    m_threadShutdown.Set(0);
}

template <typename TaskContainer>
ThreadPool<TaskContainer>::ShutdownRun::ShutdownRun(TaskContainer& a_tasks)
: m_tasks(a_tasks)
{
}

template <typename TaskContainer>
void ThreadPool<TaskContainer>::ShutdownRun::Run() NOEXCEPT
{
    while(m_tasks.Size()) 
    {
    }
}

template <typename TaskContainer>
ThreadPool<TaskContainer>::EndTask::EndTask(TaskContainer& a_tasks)
: m_tasks(a_tasks)
{
}

template <typename TaskContainer>
void ThreadPool<TaskContainer>::EndTask::Execute()
{
    ITaskPtr endTask(new EndTask(m_tasks));
    m_sharedPtr = endTask;
    m_tasks.Enqueue(m_sharedPtr);
}

} // namespace advcpp

#endif // THREAD_POOL_INL