#ifndef DEVICE_INFO
#define DEVICE_INFO

#include "i_device_info.hpp"
#include "event_structs.hpp"


namespace smarthome
{

class DeviceInfo: public IDeviceInfo
{
public:
    DeviceInfo(Type a_type, Location a_loc, PayLoad a_pl);

    virtual const std::string & GetType() const;
    virtual const Location & GetLocation() const;
    virtual const std::string & GetConfig() const;
    virtual const std::string& GetLog() const;

private:
    Type m_type;
    Location m_location;
    PayLoad m_payload;

};

}

#endif //device_info.hpp