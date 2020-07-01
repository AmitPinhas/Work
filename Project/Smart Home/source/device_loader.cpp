#include "device_loader.hpp"
#include "fire_sensor_creator.hpp"
#include "sprinkler_controller_creator.hpp"
#include <dlfcn.h>

namespace smarthome
{

DeviceLoader::DeviceLoader(ICreatorsRegistrator& a_register)
:   m_register(a_register)
{
}

void DeviceLoader::Upload(std::string a_deviceType)
{      
    std::string path = "../../source/";
    path+=a_deviceType;
    path+="Creator.so";
    
    void* handle = dlopen(path.c_str(), RTLD_NOW);
    if(!handle)
    {
        std::cout<<dlerror()<<std::endl; //exception && log
    }

    void (*pf)(ICreatorsRegistrator & );

    path.clear();

    path+=a_deviceType;
    path+="CreatorRegistration";

    pf = (void (*)(ICreatorsRegistrator & ))dlsym(handle,path.c_str());
    if(!pf)
    {
        std::cout<<dlerror()<<std::endl; //exception && log
    }
    
    pf(m_register);     
    
}


} // smarthome