#include "worker.hpp"

namespace advcpp
{

Worker::Worker(WaitableQueue<SharedPointer<ITask> > & a_tasks)
{
    try
    {
        m_run = new PoolRoutine(a_tasks);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        throw;
    }
    try
    {
        SharedPointer<Thread> newThread(new Thread (m_run));
        m_thread = newThread;

    }
    catch( ... )
    {
        delete m_run;
        throw;
    }
}

Worker::~Worker()
{
    assert(m_run);
    delete m_run; 
}

size_t Worker::GetStatus() const
{
    return m_run -> GetStatus();
}

void Worker::ShutDown()
{
    m_run -> ShutDown();
}

void Worker::Join()
{
    m_thread -> Join();
}

} // namespace advcpp
