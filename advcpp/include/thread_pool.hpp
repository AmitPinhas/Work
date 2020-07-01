#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#include <tr1/memory> // std::tr1::shared_ptr
#include <utility>    // pair
#include "common.hpp" // NOEXCEPT , class UnCopyable
#include "thread.hpp"
#include "i_task.hpp"
#include "atomic_value.hpp"
#include "waitable_queue.hpp"
#include "safe_vector.hpp"

namespace advcpp
{

typedef std::tr1::shared_ptr<ITask> ITaskPtr;

template <typename TaskContainer =  WaitableQueue<ITaskPtr> >
// TaskContainer(size_t a_capacity)
// void Enqueue(const ITaskPtr& a_value)
// void Dequeue(ITaskPtr& a_value)
// size_t Size() const
class ThreadPool : private UnCopyable
{
private:
    class Performer;
    class ShutdownRun;
    class EndTask;

public:
    typedef std::tr1::shared_ptr<IRunnable> IRunnablePtr;
    typedef std::tr1::shared_ptr<Thread> ThreadPtr;
    typedef std::tr1::shared_ptr<Performer> PerformerPtr;

    explicit ThreadPool( size_t a_maxWaitingTasks = DEFAULT_MAX_NUM_TASKS,
                         size_t a_numThreads = DefaultNumThreads()); 

    ~ThreadPool() NOEXCEPT;

    bool Submit(ITaskPtr a_task);

    void Shutdown();

    void AddWorkers(size_t a_num);

    void RemoveWorkers(size_t a_num);

    friend class Worker;

private:
    static const size_t DEFAULT_MAX_NUM_TASKS = 42; 
    static const size_t CLOSE_FOR_BUSINESS = 1;
    static const size_t OPEN_FOR_BUSINESS = 0;
    void createThreads(size_t a_numThreads);
    bool shutdownOff() const;
    bool shutdownOn() const;
    bool tasksNotEmpty() const;
    void CloseTheGate();
    void WaitForContainerToBeEmpty();
    void WakeAndKillAllWorkers();
    void CheckParams(size_t a_maxWaitingTasks, size_t a_numThreads) const;
    void WakeWorkers();
    void RemoveThreads(size_t a_numThreadsRemove);

    typedef std::pair<ThreadPtr, PerformerPtr> Worker; 

private:
    AtomicValue<int> m_shutdownFlag; 
    TaskContainer m_tasks;
    SafeVector<Worker> m_workers;

};

template <typename TaskContainer>
class ThreadPool<TaskContainer>::EndTask : public ITask 
{
public:
    EndTask(TaskContainer& a_tasks);

    EndTask(const EndTask& a_rhs) = default;

    EndTask& operator =(const EndTask& a_rhs) = default;
    
    ~EndTask() = default;
    
    virtual void Execute();

private:
    TaskContainer& m_tasks; 
    ITaskPtr m_sharedPtr;   

};

template <typename TaskContainer>
class ThreadPool<TaskContainer>::Performer : public IRunnable
{
public:
    Performer(TaskContainer& a_tasks);

    Performer(const Performer& a_rhs) = default;

    Performer& operator =(const Performer& a_rhs) = default;
    
    ~Performer() = default;

    virtual void Run() NOEXCEPT; 

    void Shutdown();

private:
    TaskContainer& m_tasks;
    AtomicValue<> m_threadShutdown;

};

template <typename TaskContainer>
class ThreadPool<TaskContainer>::ShutdownRun : public IRunnable
{
public:
    ShutdownRun(TaskContainer& a_tasks);

    ShutdownRun(const ShutdownRun& a_rhs) = default;

    ShutdownRun& operator =(const ShutdownRun& a_rhs) = default;
    
    ~ShutdownRun() = default;

    virtual void Run() NOEXCEPT; 

private:
    TaskContainer& m_tasks;

};

} // namespace advcpp

#include "inl/thread_pool.inl"

#endif // THREAD_POOL_H