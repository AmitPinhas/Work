#ifndef I_DEVICE_LOADER_H
#define I_DEVICE_LOADER_H

#include <string> // remove when adding idevice info
#include "shared_pointer.hpp"
#include "i_device_info.hpp"



namespace smarthome
{

class IDeviceLoader
{
public:
    ~IDeviceLoader() = default;
    virtual void Upload(std::string a_deviceType) = 0;

protected:
    IDeviceLoader() = default;
    IDeviceLoader(const IDeviceLoader& a_rhs) = default;
    IDeviceLoader& operator =(const IDeviceLoader& a_rhs) = default;
};

} // namespace smarthome

#endif // I_DEVICE_LOADER_H