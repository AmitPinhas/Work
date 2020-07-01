#ifndef FIRE_SENSOR_H
#define FIRE_SENSOR_H

#include"i_agent.hpp"
#include "shared_pointer.hpp"
#include "i_system_api.hpp"
#include "event_structs.hpp"
#include "i_event_receiver.hpp"

using namespace advcpp;

namespace smarthome
{

class FireSensor : public IAgent
{
public:
    FireSensor(Location a_location, size_t a_numEvents);

    ~FireSensor() noexcept = default;
    FireSensor(const FireSensor& a_rhs) = default;
    FireSensor& operator =(const FireSensor& a_rhs) = default;

    virtual void Connect(SharedPointer<ISystemConnectApi> a_systemConnectAPI);

    size_t Test();

private:
    SharedPointer<IEvent> createEvent();

private:
    Location m_location;        
    size_t m_numEvents;
    SharedPointer<IEventReceiver> m_ptrReceiver;

};

} // namespace smarthome

#endif // FIRE_SENSOR_H
