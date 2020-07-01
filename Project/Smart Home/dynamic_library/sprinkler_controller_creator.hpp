#ifndef SPRINKLER_CONTROLLER_CREATOR
#define SPRINKLER_CONTROLLER_CREATOR

#include <memory>
#include "i_device_creator.hpp"
#include "i_creators_registrator.hpp"
#include "device_creators_holder.hpp"
#include "sprinkler_controller.hpp"
#include "i_device_info.hpp"

namespace smarthome
{

class SprinklerControllerCreator : public IDeviceCreator
{
public:
    
    SprinklerControllerCreator() = default;

    ~SprinklerControllerCreator() = default;
    
    virtual advcpp::SharedPointer<IAgent> Create(advcpp::SharedPointer<IDeviceInfo> a_deviceInfo);

    SprinklerControllerCreator(SprinklerControllerCreator const& a_copy) = default;

    SprinklerControllerCreator& operator = (SprinklerControllerCreator const& a_copy) = default;

    static void Registration(ICreatorsRegistrator & a_creatorRegistrator);

};

}

#endif //sprinkler_controller_creator.hpp