#ifndef I_DEVICE_CREATOR_H
#define I_DEVICE_CREATOR_H

#include "shared_pointer.hpp"
#include "i_agent.hpp"
#include "i_device_info.hpp"

namespace smarthome
{

class IDeviceCreator
{
public:
    virtual ~IDeviceCreator() = default;

    virtual advcpp::SharedPointer<IAgent> Create(advcpp::SharedPointer<IDeviceInfo> a_deviceInfo) = 0;  

protected:
    IDeviceCreator() = default;
    IDeviceCreator(const IDeviceCreator & a_rhs) = default;
    IDeviceCreator & operator = (const IDeviceCreator & a_rhs) = default;
};


} // namespace smarthome

#endif // I_DEVICE_CREATOR_H