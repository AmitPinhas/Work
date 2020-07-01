#include "creators_container.hpp"

namespace smarthome 
{

std::shared_ptr<IDeviceCreator> CreatorsContainer::Find(DeviceType a_deviceType)
{
    auto it = m_deviceContainer.find(a_deviceType);
    if(it == m_deviceContainer.end())
    {
        return 0;
    }
    return it->second;
}

void CreatorsContainer::Registrate(DeviceType a_deviceType,
                            std::shared_ptr<IDeviceCreator> a_deviceCreator)
{
    m_deviceContainer[a_deviceType] = a_deviceCreator;
}

} // namespace smarthome 
