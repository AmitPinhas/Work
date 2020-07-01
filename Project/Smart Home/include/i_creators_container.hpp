#ifndef I_CREATORS_CONTAINER_H
#define I_CREATORS_CONTAINER_H

#include "i_device_info.hpp"
#include "i_device_creator.hpp"
#include <memory>

namespace smarthome
{

typedef std::string DeviceType;

class ICreatorsContainer
{
public:
    virtual ~ICreatorsContainer() = default;

    virtual std::shared_ptr<IDeviceCreator> Find(DeviceType a_deviceType) = 0;

protected:
    ICreatorsContainer() = default;
    ICreatorsContainer(const ICreatorsContainer & a_rhs) = default;
    ICreatorsContainer & operator = (const ICreatorsContainer & a_rhs) = default;
};

} // namespace smarthome

#endif // I_CREATORS_CONTAINER_H