#include "pool_routine.hpp"
#include "thread.hpp"

namespace advcpp
{

const int ON = 1;
const int OFF = 0;

PoolRoutine::PoolRoutine(WaitableQueue<SharedPointer<ITask> > & a_tasks)
: m_tasks(a_tasks)
, m_flag(OFF)
{
}

void PoolRoutine::Run() NOEXCEPTION
{
    while ( m_flag.Value() == OFF )
    {
        SharedPointer<ITask> task;
        m_tasks.Dequeue(task);
        if(dynamic_cast<EndTask*>(&(*task)))
        {
            ShutDown();
            break; 
        }
        try
        {
            task -> Run();
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
        catch( ... )
        {

        }
    }
}

void PoolRoutine::ShutDown() 
{
    m_flag.Set(ON);
}

size_t PoolRoutine::GetStatus() const NOEXCEPTION
{
    return m_flag.Value();
}

} // namespace advcpp
