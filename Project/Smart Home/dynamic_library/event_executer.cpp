#include "event_executer.hpp"

namespace smarthome
{

EventExecuter::EventExecuter(SharedPointer<IEvent> a_event, SharedPointer<ISubscribersList> a_cContainer)
: m_ievent(a_event)
, m_sContainer(a_cContainer)
{
}

void EventExecuter::Run()
{
    m_sContainer->Dispatch(m_ievent);
}

} // namespace smarthome
