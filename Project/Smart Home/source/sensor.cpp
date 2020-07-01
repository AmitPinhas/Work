#include "sensor.hpp"

#include "i_event.hpp"
#include "fire_event.hpp"
#include "shared_pointer.hpp"

using namespace advcpp;

namespace smarthome
{

typedef SharedPointer<IEvent> IEventPtr;

Sensor::Sensor(const Topic & a_topic, const IEventReceiver & a_receiver)
: m_topic(a_topic)
, m_receiver(a_receiver)
{
}

void Sensor::SendEvent() const
{
    TimeStamp time;
    asctime(gmtime(&(time.m_time)));
    Flames flame;
    flame.m_exist = true;
    flame.m_height = 100;
    IEventPtr event(new FireEvent(m_topic, time, flame));   // TODO !!!!
    m_receiver.Receive(event);
}

} // namespace smarthome
