#ifndef I_CREATORS_REGISTRATOR_H
#define I_CREATORS_REGISTRATOR_H

#include <string>
//#include "shared_pointer.hpp"
#include <memory>


namespace smarthome
{

typedef std::string DeviceType; // change to devicetype;
class IDeviceCreator;

class ICreatorsRegistrator
{
public:
    virtual ~ICreatorsRegistrator() = default;

    virtual void Registrate(DeviceType a_deviceType,
                            std::shared_ptr<IDeviceCreator> a_deviceCreator) = 0;

protected:
    ICreatorsRegistrator() = default;
    ICreatorsRegistrator(const ICreatorsRegistrator & a_rhs) = default;
    ICreatorsRegistrator & operator = (const ICreatorsRegistrator & a_rhs) = default;


};

} // namespace smarthome

#endif // I_CREATORS_REGISTRATOR_H