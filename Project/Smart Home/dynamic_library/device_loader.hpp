#ifndef DEVICE_LOADER
#define DEVICE_LOADER

#include "i_device_loader.hpp"
#include "i_creators_registrator.hpp"


namespace smarthome
{
class DeviceLoader: public IDeviceLoader
{
public:
    DeviceLoader(ICreatorsRegistrator& a_register);
    virtual void Upload(std::string a_deviceType);

private:
    ICreatorsRegistrator& m_register;
};


}

#endif //device_loader.hpp
