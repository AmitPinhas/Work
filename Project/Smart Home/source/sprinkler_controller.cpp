#include "sprinkler_controller.hpp"

#include <iostream>
#include "fire_event.hpp"

namespace smarthome
{

SprinklerController::SprinklerController(Location a_location)
: m_location(a_location)
{
}

void SprinklerController::SetSharedPointer(SharedPointer<ISubscriber> a_SharedPtrThis)
{
    m_SharedPtrThis = a_SharedPtrThis;
}

void SprinklerController::Notify(SharedPointer<IEvent> a_event)
{
    FireEvent* fireEvent = dynamic_cast<FireEvent*>(&*a_event);
    std::cout << "event type: "<< a_event->GetTopic().m_type.m_type << " sprinklers on \n";
    std::cout << "height -->: "<< fireEvent->GetFlames().m_height <<
              "\n" << "exist -->: " << fireEvent->GetFlames().m_exist << std::endl ;    
}

void SprinklerController::Connect(SharedPointer<ISystemConnectApi> a_systemConnectAPI)
{
    auto sprinklerTopic = createTopic();

    a_systemConnectAPI->Subscribe(sprinklerTopic, m_SharedPtrThis);

}

Topic SprinklerController::createTopic()
{
    Topic sprinklerTopic;
    sprinklerTopic.m_type.m_type = "fire sensor";
    sprinklerTopic.m_location = m_location;

    return sprinklerTopic;
}

} // namespace smarthome