#include "thread_group.hpp"

namespace advcpp
{


const int ON = 1;
const int OFF = 0;

ThreadGroup::ThreadGroup(WaitableQueue<SharedPointer<ITask> > & a_tasks)
: m_tasks(a_tasks)
{
}

bool ThreadGroup::AddWorker(size_t a_numOfWorkers)
{
    size_t originalSize = m_workers.size();
    if(a_numOfWorkers + originalSize > MaxThreads())
    {
        return false;
    }
    
    for(size_t i = 0; i < a_numOfWorkers ; ++i)
    {
        Guard gauard(m_mutex);
        m_workers.emplace_back(new Worker(m_tasks));
    }    
return m_workers.size() == originalSize + a_numOfWorkers;
}

bool ThreadGroup::SubstractWorker(size_t a_numOfWorkers)
{
    size_t originalSize = m_workers.size();
    size_t subThreads = minThreads(a_numOfWorkers);
    {
        Guard gauard(m_mutex);
        throwPoisonApples(subThreads);
        joinCloseWorkers();
    }
    return originalSize - subThreads == m_workers.size();
}

void ThreadGroup::throwPoisonApples(size_t numOfApples) const
{
    for(size_t i = 0; i < numOfApples; ++i)
    {
        SharedPointer<EndTask> poison(new EndTask);
        m_tasks.Enqueue(poison);
    }
}

size_t ThreadGroup::joinCloseWorkers()
{
    size_t count = 0;
    
    std::vector<SharedPointer<Worker> >::iterator it = m_workers.begin();
    std::vector<SharedPointer<Worker> >::iterator end = m_workers.end();
    
    while(end != it)
    {
        if(ON == (*it) -> GetStatus())
        {
            (*it) -> Join();
            it = m_workers.erase( it );
            ++count;
            continue;
        }
        ++it;
    }
    
    return count;
}

bool ThreadGroup::ShutDown()
{
    throwPoisonApples(Size());
    while(Size() > 0)
    {
        m_workers.back() -> Join();
        m_workers.pop_back();
    }
    return true;
}

size_t ThreadGroup::Size() const
{
    size_t size;
    {
        Guard gauard(m_mutex);
        size = m_workers.size();
    }
    return size;
}

size_t ThreadGroup::minThreads(size_t givenNum)
{
    return givenNum <= m_workers.size() ? givenNum : m_workers.size();
}
    

} // namespace advcpp
