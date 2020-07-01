#include "event_controllers_publisher.hpp"

namespace smarthome
{

EventControllersPublisher::EventControllersPublisher(ControllersContainer & a_container, const IEvent & a_ievent)
: m_container(a_container)
, m_ievent(a_ievent)
{
}

void EventControllersPublisher::Run()
{
    
}


} // namespace smarthome
