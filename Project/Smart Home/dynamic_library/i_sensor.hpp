#ifndef I_SENSOR_H
#define I_SENSOR_H

#include "i_agent.hpp"

namespace smarthome
{

class ISensor : public IAgent
{
public:
    virtual ~ISensor() noexcept = 0 ;
    virtual void SendEvent() const = 0;

protected:
    ISensor() = default;
    ISensor(const ISensor & a_sensor) = default;
    ISensor & operator = (const ISensor & a_sensor) = default;

};

} // namespace smart_home

#endif // I_SENSOR_H