#include "send_events.hpp"

namespace smarthome
{

SendEvents::SendEvents(SharedPointer<IEvent> a_event, 
                       size_t a_numEvents,
                       SharedPointer<IEventReceiver> a_ptrReceiver)
: m_event(a_event)
, m_numEvents(a_numEvents) 
, m_ptrReceiver(a_ptrReceiver)                    
{
}               

void SendEvents::Run() NOEXCEPTION
{
    while(m_numEvents-- >0)
    {
       m_ptrReceiver->Receive(m_event); 
    }
}

} // namespace smarthome