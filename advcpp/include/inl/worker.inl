#ifndef WORKER_INL
#define WORKER_INL

#include "worker.hpp"

namespace advcpp
{
/*
template <typename TaskContainer>
Worker<TaskContainer>::Worker(PerformerPtr a_performer)
: m_performer(a_performer)
, m_thread(&*m_performer)
{
}

template <typename TaskContainer>
void Worker<TaskContainer>::Close()
{
    m_performer->Shutdown();
    m_thread.Join();
}
*/
} // namespace advcpp

#endif // WORKER_INL