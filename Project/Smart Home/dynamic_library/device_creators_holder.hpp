#ifndef DEVICE_CREATORS_HOLDER_H
#define DEVICE_CREATORS_HOLDER_H

#include <map>
#include <string>
#include "i_agent_creator.hpp"
#include "i_device_loader.hpp"
#include "i_creators_registrator.hpp"

namespace smarthome
{

typedef std::string DeviceType; // change to devicetype;
class IDeviceCreator;

class DeviceCreatorsHolder : public IAgentCreator, public ICreatorsRegistrator
{
public:
    explicit DeviceCreatorsHolder(IDeviceLoader & a_iDeviceLoader);

    virtual SharedPointer<IAgent> GetAgent(SharedPointer<IDeviceInfo> a_deviceInfo) const;
    virtual void Registrate(DeviceType a_deviceType,
                            std::shared_ptr<IDeviceCreator> a_deviceCreator);



private:
    void LoadNewDevice(SharedPointer<IDeviceInfo> a_deviceInfo);

private:
    std::map<DeviceType, std::shared_ptr<IDeviceCreator> > m_deviceCreatorContainer;
    IDeviceLoader& m_iDeviceLoader;

};




} // namespace smarthome

#endif //  DEVICE_CREATORS_HOLDER_H