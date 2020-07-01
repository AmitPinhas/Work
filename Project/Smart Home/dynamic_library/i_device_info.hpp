#ifndef I_DEVICE_INFO_HPP
#define I_DEVICE_INFO_HPP

#include <string>
#include "event_structs.hpp"

namespace smarthome
{

class IDeviceInfo
{
public:
    virtual ~IDeviceInfo() = default;

    virtual const std::string & GetType() const = 0;
    virtual const Location & GetLocation() const = 0;
    virtual const std::string & GetConfig() const = 0;
    virtual const std::string& GetLog() const = 0;

protected:
    IDeviceInfo() = default;
    IDeviceInfo(const IDeviceInfo& a_rhs) = default;
    IDeviceInfo& operator = (const IDeviceInfo& a_rhs) = default;

};

} // namespace smarthome


#endif //  I_DEVICE_INFO_HPP.hpp