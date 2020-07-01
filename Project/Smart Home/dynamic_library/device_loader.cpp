#include "device_loader.hpp"
#include "fire_sensor_creator.hpp"
#include "sprinkler_controller_creator.hpp"

namespace smarthome
{

DeviceLoader::DeviceLoader(ICreatorsRegistrator& a_register)
:   m_register(a_register)
{
}

void DeviceLoader::Upload(std::string a_deviceType)
{
    
    
    if(!a_deviceType.compare("FireSensor"))
    {
        FireSensorCreator::Registration(m_register);
    }  
    else if(!a_deviceType.compare("SprinklerController"))
    {
        SprinklerControllerCreator::Registration(m_register);
    }
    else 
    {
        std::cout << "yotam gay" << std::endl;
    }
    
    
    
}


} // smarthome