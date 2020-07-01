#ifndef I_THREAD_POOL_H
#define I_THREAD_POOL_H

#include "shared_pointer.hpp"
#include "thread.hpp"
#include "i_task.hpp"

namespace advcpp
{

class IThreadPool
{
public:
    virtual ~IThreadPool() = 0;
    virtual void DispatchTask(SharedPointer<ITask> a_task) = 0;
    
    virtual void AddThreads(size_t numOfThreads) = 0;
    virtual void RemoveThreads(size_t numOfThreads) = 0;
    
    virtual void ShutDown() = 0;
};

inline IThreadPool::~IThreadPool()
{
}

} // namespace advcpp

#endif // I_THREAD_POOL_H