#include "event_2_list_runner.hpp"

namespace smarthome
{

Event2ListRunner::Event2ListRunner(SharedPointer<IEvent> a_event, SharedPointer<ISubscribersList> a_cContainer)
: m_ievent(a_event)
, m_sContainer(a_cContainer)
{
}

void Event2ListRunner::Run()
{
    m_sContainer->Dispatch(m_ievent);
}

} // namespace smarthome
