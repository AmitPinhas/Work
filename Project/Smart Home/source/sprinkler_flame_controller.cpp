#include "sprinkler_flame_controller.hpp"

#include <iostream>
#include "fire_event.hpp"

namespace smarthome
{

SprinklerFlameController::SprinklerFlameController(Location a_location, AtomicValue<int> & a_atomic)
: m_location(a_location)
, m_atomic(a_atomic)
{
}

void SprinklerFlameController::SetSharedPointer(SharedPointer<ISubscriber> a_SharedPtrThis)
{
    m_SharedPtrThis = a_SharedPtrThis;
}

void SprinklerFlameController::Notify(SharedPointer<IEvent> a_event)
{
    (void)a_event;
    ++m_atomic;   
}

void SprinklerFlameController::Connect(SharedPointer<ISystemConnectApi> a_systemConnectAPI)
{
    auto sprinklerTopic = createTopic();

    a_systemConnectAPI->Subscribe(sprinklerTopic, m_SharedPtrThis);

}

Topic SprinklerFlameController::createTopic()
{
    Topic sprinklerTopic;
    sprinklerTopic.m_type.m_type = "fire sensor";
    sprinklerTopic.m_location = m_location;

    return sprinklerTopic;
}

} // namespace smarthome