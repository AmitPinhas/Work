#ifndef EVENT_DISPATCHER_H
#define EVENT_DISPATCHER_H

#include "shared_pointer.hpp"
#include "i_event_dispatcher.hpp"
#include "thread_pool.hpp"
#include "event_dequeuer.hpp"
#include "i_event_storage_pop.hpp"
//#include "i_broadcast.hpp" 
#include "i_subscribers_list_notifier.hpp"

using namespace advcpp;

namespace smarthome
{

class EventDispatcher : public IEventDispatcher
{
public:
    EventDispatcher(IEventStoragePop& a_eventStorage, ISubscribersListNotifier& a_broadcast, size_t a_numOfThreads);

    ~EventDispatcher() noexcept = default;
    EventDispatcher(const EventDispatcher& a_rhs) = default;
    EventDispatcher& operator =(const EventDispatcher& a_rhs) = default;

    virtual void Pause();

    virtual void Resume();

    virtual void ShutDown();

private:
    void insertTasks(size_t a_numTasks);

private:
    std::vector<SharedPointer<Thread> > m_threads;
    // ThreadPool m_threadPool;
    SharedPointer<EventDequeuer> m_ptrEventDequeuer;
    size_t m_numThreads;
    IEventStoragePop& m_eventStorage;

};


class EventDispatcherShutDownRun : public IRunnable
{
public:
    explicit EventDispatcherShutDownRun(IEventStoragePop& a_eventStorage);

    ~EventDispatcherShutDownRun() = default;
    EventDispatcherShutDownRun(const EventDispatcherShutDownRun& a_rhs) =delete;
    EventDispatcherShutDownRun& operator =(const EventDispatcherShutDownRun& a_rhs) =delete;

    virtual void Run() NOEXCEPTION;

private:
    IEventStoragePop& m_eventStorage;

};

} // namespace smarthome

#endif // EVENT_DISPATCHER_H
