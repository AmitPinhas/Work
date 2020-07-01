#ifndef EVENT_DEQUEUER_H
#define EVENT_DEQUEUER_H

#include "i_task.hpp"
#include "i_event_storage_pop.hpp"
//#include "i_broadcast.hpp" 
#include "thread.hpp"
#include "i_subscribers_list_notifier.hpp"

namespace smarthome
{

class EventDequeuer : public IRunnable //public advcpp::ITask
{
public:
    EventDequeuer(IEventStoragePop& a_events, ISubscribersListNotifier& a_broadcast);

    ~EventDequeuer() = default;
    EventDequeuer(const EventDequeuer& a_rhs) = default;
    EventDequeuer& operator =(const EventDequeuer& a_events) = default;

    virtual void Run() NOEXCEPTION;

    void Pause();
    
    void Resume();

    void ShutDown();

private:
    static const size_t OPEN_FOR_BUSINESS = 1;
    static const size_t CLOSE_FOR_BUSINESS = 0;

private:
    IEventStoragePop& m_events;
    ISubscribersListNotifier& m_broadcast;
    AtomicValue<int> m_workFlag;
    AtomicValue<int> m_shutDownFlag;    

};

} // namespace smarthome

#endif // EVENT_DEQUEUER_H