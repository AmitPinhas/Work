#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#include <vector> // vector
#include "i_thread_pool.hpp" // interface?
#include "pool_routine.hpp" // runnable routine
#include "i_task.hpp" // task
#include "mutex.hpp" // mutex guard
#include "waitable_queue.hpp" // queue for tasks
#include "Common.hpp" // NOEXCEPT
#include "thread_group.hpp"

namespace advcpp
{

const size_t DEAFAULT_THREAD_NUM = NumOfCores() - 1;

class ThreadPool : public UnCopyable
{
public:
    explicit ThreadPool(size_t a_maxTasks, size_t a_numOfThreads = DEAFAULT_THREAD_NUM); // : change name to MAX_TASKS
    ~ThreadPool() NOEXCEPTION;

    void DispatchTask(SharedPointer<ITask> a_task);
    
    void AddThreads(size_t numOfThreads);
    void RemoveThreads(size_t numOfThreads);
    
    void ShutDown();

private:
    void runThreads(size_t a_numOfThreads);
    void subThreads(size_t a_numOfThreads);
    
    void joinThreads();
    
    bool isShutdown(); 
    void turnShut();
    void freeTasks();
    
    void shutRoutines();

    size_t maxNumOfThreads(size_t numOfthreads);

private:
    WaitableQueue<SharedPointer<ITask> > m_tasks;
    ThreadGroup m_threadGroup;
    AtomicValue<int> m_shutdownFlag; 
    Mutex m_mutex;

};

} // namespace advcpp



#endif // THREAD_POOL_H