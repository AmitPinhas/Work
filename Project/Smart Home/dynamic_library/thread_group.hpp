#ifndef THREAD_GROUP_H
#define THREAD_GROUP_H

#include <vector>
#include <mutex>
#include "worker.hpp"


namespace advcpp
{

class ThreadGroup
{
public:
    explicit ThreadGroup(WaitableQueue<SharedPointer<ITask> > & a_tasks);
    bool AddWorker(size_t a_numOfWorkers = 1);
    bool SubstractWorker(size_t a_numOfWorkers = 1);
    bool ShutDown();

    size_t Size() const;

private:
    void throwPoisonApples(size_t numOfApples) const;
    size_t joinCloseWorkers();
    size_t minThreads(size_t givenNum);

private:
    std::vector<SharedPointer<Worker> > m_workers;
    WaitableQueue<SharedPointer<ITask> > & m_tasks;
    mutable Mutex m_mutex;

};

} // namespace advcpp


#endif // THREAD_GROUP_H