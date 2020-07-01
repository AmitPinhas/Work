#ifndef TASKS_H
#define TASKS_H

#include <tr1/memory> // std::tr1::shared_ptr
#include "i_task.hpp"
#include "waitable_queue.hpp"

namespace advcpp
{

class WaitableQueueTasks : public ITasksSubmit, public ITasksGet
{
public:
    typedef std::tr1::shared_ptr<ITask> ITaskPtr;

    explicit WaitableQueueTasks(size_t a_capacity); 

    ~WaitableQueueTasks() NOEXCEPT;

    virtual void Submit(ITaskPtr a_task);

    virtual void Get(ITaskPtr& a_task);

    virtual size_t Size() const;

private:
    WaitableQueue<ITaskPtr> m_tasks;

};

} // namespace advcpp

#endif // TASKS_H