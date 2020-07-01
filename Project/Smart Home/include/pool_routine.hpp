#ifndef POOL_ROUTINE_H
#define POOL_ROUTINE_H

#include "i_pool_routine.hpp"
#include "task.hpp"

namespace advcpp
{

class PoolRoutine : public IPoolRoutine
{
public:

    explicit PoolRoutine(WaitableQueue<SharedPointer<ITask> > & a_tasks);
    ~PoolRoutine() NOEXCEPTION;

    virtual void Run() NOEXCEPTION;
    
    virtual void ShutDown();
    virtual size_t GetStatus() const NOEXCEPTION;

private:
    WaitableQueue<SharedPointer<ITask> > & m_tasks;
    AtomicValue<int> m_flag;
    
};

inline PoolRoutine::~PoolRoutine()NOEXCEPTION
{
}

} // namespace advcpp

#endif // POOL_ROUTINE_H