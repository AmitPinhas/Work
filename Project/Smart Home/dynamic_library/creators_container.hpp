#ifndef CREATORS_CONTAINER_H
#define CREATORS_CONTAINER_H

#include <map> 
#include <memory>

#include "i_creators_container.hpp"
#include "i_creators_registrator.hpp"
#include "i_device_creator.hpp"

namespace smarthome
{

typedef std::string DeviceType;

class CreatorsContainer : public ICreatorsContainer, public ICreatorsRegistrator
{
public:
    CreatorsContainer() = default;
    ~CreatorsContainer() = default;
    CreatorsContainer(const CreatorsContainer & a_rhs) = delete;
    CreatorsContainer & operator = (const CreatorsContainer & a_rhs) = delete;

    virtual std::shared_ptr<IDeviceCreator> Find(DeviceType a_deviceType);

    virtual void Registrate(DeviceType a_deviceType,
                            std::shared_ptr<IDeviceCreator> a_deviceCreator);

private:
    std::map<DeviceType, std::shared_ptr<IDeviceCreator> > m_deviceContainer;

};



} // namespace smarthome



#endif // CREATORS_CONTAINER_H