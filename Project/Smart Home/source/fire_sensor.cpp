#include "fire_sensor.hpp"

#include "i_event.hpp"
#include "fire_event.hpp"
#include "send_events.hpp"
#include <iostream> // cout , remove

using namespace advcpp;

namespace smarthome
{

FireSensor::FireSensor(Location a_location, size_t a_numEvents)
: m_location(a_location)
, m_numEvents(a_numEvents)
{
}

void FireSensor::Connect(SharedPointer<ISystemConnectApi> a_systemConnectAPI)
{
    m_ptrReceiver = a_systemConnectAPI->GetReciver();

    SharedPointer<IEvent> fireEvent = createEvent();

    SendEvents sendEventRun(fireEvent, m_numEvents, m_ptrReceiver);

    Thread threadSendEvents(&sendEventRun);

    threadSendEvents.Join();    
}

SharedPointer<IEvent> FireSensor::createEvent()
{
    Topic fireTopic;
    fireTopic.m_type.m_type = "fire sensor";
    fireTopic.m_location = m_location;

    TimeStamp timeEvent;
    asctime(gmtime(&(timeEvent.m_time)));

    Flames flame;
    flame.m_exist = true;
    flame.m_height = 100;

    SharedPointer<IEvent> fireEvent(new FireEvent(fireTopic, timeEvent, flame)); 

    return fireEvent;
}

size_t FireSensor::Test()
{
    return 5;
}


} // namespace smarthome