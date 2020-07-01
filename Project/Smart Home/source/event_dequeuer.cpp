#include "event_dequeuer.hpp"

#include "i_event.hpp"
#include "shared_pointer.hpp"

using namespace advcpp;

namespace smarthome
{

EventDequeuer::EventDequeuer(IEventStoragePop& a_events, ISubscribersListNotifier& a_broadcast)
: m_events(a_events)
, m_broadcast(a_broadcast)
, m_shutDownFlag(OPEN_FOR_BUSINESS)
{
}

void EventDequeuer::Pause()
{
    m_workFlag.Set(CLOSE_FOR_BUSINESS);
}

void EventDequeuer::Resume()
{
    m_workFlag.Set(OPEN_FOR_BUSINESS);
}

void EventDequeuer::ShutDown()
{
    m_shutDownFlag.Set(CLOSE_FOR_BUSINESS);
}

void EventDequeuer::Run() NOEXCEPTION
{
    while(m_shutDownFlag.Value() == OPEN_FOR_BUSINESS)
    {
        if(m_workFlag.Value() == OPEN_FOR_BUSINESS)
        {
            SharedPointer<IEvent> newEvent;

            if(m_events.Size())
            {
                m_events.Pop(newEvent);     
                m_broadcast.Notifi(newEvent);
            }
        }
    }
}

} // namespace smarthome