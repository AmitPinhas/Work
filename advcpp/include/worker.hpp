#ifndef WORKER_H
#define WORKER_H

#include "thread_pool.hpp" // class Performer
#include "common.hpp" // NOEXCEPT , class UnCopyable
#include "thread.hpp"

namespace advcpp
{   
/*
template <typename TaskContainer>
class Worker : private UnCopyable
{
public:
    typedef std::tr1::shared_ptr<ThreadPool<TaskContainer>::Performer> PerformerPtr; 

    explicit Worker(PerformerPtr a_performer);

    ~Worker() = default;

    void Close();

private:
    PerformerPtr m_performer;
    Thread m_thread;

};
*/
} // namespace advcpp

#include "inl/worker.inl"

#endif // WORKER_H