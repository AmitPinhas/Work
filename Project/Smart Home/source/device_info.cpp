#include "device_info.hpp"

namespace smarthome
{


DeviceInfo::DeviceInfo(Type a_type, Location a_loc, PayLoad a_pl)
:  m_type(a_type)
,  m_location(a_loc)
,  m_payload(a_pl)
{
}

const std::string & DeviceInfo::GetType() const 
{
    return m_type.m_type;
}

const Location & DeviceInfo::GetLocation() const 
{
    return m_location;
}

const std::string & DeviceInfo::GetConfig() const 
{
    return m_payload.m_payload;
}

const std::string& DeviceInfo::GetLog() const
{
    std::string str("log ---> change");
    return str;
}

} // namespace smarthome