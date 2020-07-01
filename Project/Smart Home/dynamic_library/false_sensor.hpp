#ifndef FALSE_SENSOR_H
#define FALSE_SENSOR_H

#include"i_agent.hpp"
#include "shared_pointer.hpp"
#include "i_system_api.hpp"
#include "event_structs.hpp"
#include "i_event_receiver.hpp"

using namespace advcpp;

namespace smarthome
{

class FalseSensor : public IAgent
{
public:
    FalseSensor(Location a_location, size_t a_numEvents);

    ~FalseSensor() noexcept = default;
    FalseSensor(const FalseSensor& a_rhs) = default;
    FalseSensor& operator =(const FalseSensor& a_rhs) = default;

    virtual void Connect(SharedPointer<ISystemConnectApi> a_systemConnectAPI);

private:
    SharedPointer<IEvent> createEvent();

private:
    Location m_location;        
    size_t m_numEvents;
    SharedPointer<IEventReceiver> m_ptrReceiver;

};

} // namespace smarthome

#endif // FIRE_SENSOR_H
