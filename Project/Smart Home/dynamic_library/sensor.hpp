#ifndef SENSOR_H
#define SENSOR_H

#include "i_sensor.hpp"
#include "i_event_receiver.hpp"
namespace smarthome
{

class Sensor : public ISensor
{
public:
    Sensor(const Topic & a_topic, const IEventReceiver & a_receiver);
    ~Sensor() = default;

    virtual void SendEvent() const;

private:
    Topic m_topic;
    const IEventReceiver & m_receiver;

};

} // namespace smarthome

#endif //  SENSOR_H