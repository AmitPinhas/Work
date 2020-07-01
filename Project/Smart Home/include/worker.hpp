#ifndef WORKER_H
#define WORKER_H

#include "shared_pointer.hpp"
#include "thread.hpp"
#include "pool_routine.hpp"

namespace advcpp
{

class Worker
{
public:
    Worker(WaitableQueue<SharedPointer<ITask> > & a_tasks);
    ~Worker();

    size_t GetStatus() const;
    void ShutDown();
    void Join();

private:
    IPoolRoutine * m_run;
    SharedPointer<Thread> m_thread;
    
};

} // namespace advcpp


#endif // WORKER_H