#include "thread_pool.hpp"
#include "utils.hpp"
#include "task.hpp"

namespace advcpp
{

static const double GOLDEN_RATIO = 1.618; // NOT RELEVANT
static const size_t ON = 1;
static const size_t OFF = 0;
static const size_t MAX_THREADS = NumOfCores() * 25;

ThreadPool::ThreadPool(size_t a_maxTasks, size_t a_numOfThreads)
: m_tasks(a_maxTasks)
, m_threadGroup(m_tasks)
, m_shutdownFlag(OFF)
{
    m_threadGroup.AddWorker(a_numOfThreads);
}

ThreadPool::~ThreadPool() NOEXCEPTION
{
    assert(isShutdown());
}

void ThreadPool::AddThreads(size_t a_numOfThreads)
{
    if(!isShutdown())
    {
        m_threadGroup.AddWorker(a_numOfThreads);
    }   
}
    
void ThreadPool::RemoveThreads(size_t a_numOfThreads)
{   
    m_threadGroup.SubstractWorker(a_numOfThreads);
}

void ThreadPool::ShutDown()
{
    turnShut();
    bool checkSut = m_threadGroup.ShutDown(); 
    std::cout << "was shut down successfull?: " << checkSut <<  '\n';
}

void ThreadPool::DispatchTask(SharedPointer<ITask> a_task)
{
    if(false != a_task && !isShutdown())
    {
        m_tasks.Enqueue(a_task);
    }
}

bool ThreadPool::isShutdown()
{
    return m_shutdownFlag.Value();
}

void ThreadPool::turnShut()
{
    m_shutdownFlag.Set(ON);
}

size_t ThreadPool::maxNumOfThreads(size_t numOfthreads)
{
    return std::min(numOfthreads , MAX_THREADS);
}

} // namespace advcpp
