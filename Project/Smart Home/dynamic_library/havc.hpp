#ifndef HAVC_H
#define HAVC_H

#include "i_device.hpp"
#include "test_events.hpp" // HavcLevel, HavcEvent

namespace smarthome
{

class HavcDevice : public IDevice
{
public:
    enum Switch{OFF, ON, END};

    HavcDevice();
    ~HavcDevice() = default;
    HavcDevice(const HavcDevice & a_havcDevice) = default;
    HavcDevice & operator = (const HavcDevice & a_havcDevice) = default;

    virtual void Work(const IEvent & a_ievent);

private:
    Switch      m_switch;
    HavcLevel   m_level;

};

} // namespace smarthome

#endif // HAVC_H