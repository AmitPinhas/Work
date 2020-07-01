#include "tasks.hpp"

namespace advcpp
{

WaitableQueueTasks::WaitableQueueTasks(size_t a_capacity)
: m_tasks(a_capacity)
{
}

WaitableQueueTasks::~WaitableQueueTasks() NOEXCEPT
{
}

void WaitableQueueTasks::Submit(ITaskPtr a_task)
{
    m_tasks.Enqueue(a_task);
}

void WaitableQueueTasks::Get(ITaskPtr& a_task)
{
   m_tasks.Dequeue(a_task); 
}

size_t WaitableQueueTasks::Size() const
{
    return m_tasks.Size();
}

} // namespace advcpp