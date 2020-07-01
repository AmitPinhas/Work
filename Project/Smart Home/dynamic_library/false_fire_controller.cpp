#include "false_fire_controller.hpp"

#include <iostream>
#include "fire_event.hpp"

namespace smarthome
{

FalseFireControlller::FalseFireControlller(Location a_location)
: m_location(a_location)
{
}

int FalseFireControlller::GetValue() const
{
    return m_numEvents.Value();
}

void FalseFireControlller::SetSharedPointer(SharedPointer<ISubscriber> a_SharedPtrThis)
{
    m_SharedPtrThis = a_SharedPtrThis;
}

void FalseFireControlller::Notify(SharedPointer<IEvent> a_event)
{
    FireEvent* fireEvent = dynamic_cast<FireEvent*>(&*a_event);
    std::cout << "event type: "<< a_event->GetTopic().m_type.m_type << " sprinklers on \n";
    std::cout << "height -->: "<< fireEvent->GetFlames().m_height <<
              "\n" << "exist -->: " << fireEvent->GetFlames().m_exist << std::endl ;    
    ++m_numEvents;
}

void FalseFireControlller::Connect(SharedPointer<ISystemConnectApi> a_systemConnectAPI)
{
    auto sprinklerTopic = createTopic();

    a_systemConnectAPI->Subscribe(sprinklerTopic, m_SharedPtrThis);

    Topic falseTopic;
    falseTopic.m_type.m_type = "false sensor";
    falseTopic.m_location = m_location;

    a_systemConnectAPI->Subscribe(falseTopic, m_SharedPtrThis);

}

Topic FalseFireControlller::createTopic()
{
    Topic sprinklerTopic;
    sprinklerTopic.m_type.m_type = "fire sensor";
    sprinklerTopic.m_location = m_location;

    return sprinklerTopic;
}

} // namespace smarthome