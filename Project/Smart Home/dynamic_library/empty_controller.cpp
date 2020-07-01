#include "empty_controller.hpp"

#include <iostream>
#include "fire_event.hpp"

namespace smarthome
{

EmptyController::EmptyController(Location a_location)
: m_location(a_location)
{
}

void EmptyController::SetSharedPointer(SharedPointer<ISubscriber> a_SharedPtrThis)
{
    m_SharedPtrThis = a_SharedPtrThis;
}

void EmptyController::Notify(SharedPointer<IEvent> a_event)
{
    FireEvent* fireEvent = dynamic_cast<FireEvent*>(&*a_event);
    std::cout << "event type: "<< a_event->GetTopic().m_type.m_type << " empty controller listen to sprinkler controller \n";
    std::cout << "height -->: "<< fireEvent->GetFlames().m_height <<
              "\n" << "exist -->: " << fireEvent->GetFlames().m_exist << std::endl ;    
}

void EmptyController::Connect(SharedPointer<ISystemConnectApi> a_systemConnectAPI)
{
    auto sprinklerTopic = createTopic();

    a_systemConnectAPI->Subscribe(sprinklerTopic, m_SharedPtrThis);

}

Topic EmptyController::createTopic()
{
    Topic empty;
    empty.m_type.m_type = "fire sensor";
    empty.m_location = m_location;

    return empty;
}

} // namespace smarthome