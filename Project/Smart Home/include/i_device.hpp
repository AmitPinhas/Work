#ifndef I_DEVICE_H
#define I_DEVICE_H

#include "i_event.hpp"
#include "shared_pointer.hpp"

using namespace advcpp;

namespace smarthome
{

class IDevice
{
public:
    virtual ~IDevice() = 0;
    virtual void Work(SharedPointer<IEvent> a_ievent) = 0;

protected:
    IDevice() = default;
    IDevice(const IDevice & a_device)= default;
    IDevice & operator = (const IDevice & a_device)= default;


};

} // namespace smarthome

#endif // I_DEVICE_H