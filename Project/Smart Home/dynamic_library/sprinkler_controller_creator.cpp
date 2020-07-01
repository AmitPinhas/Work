#include "sprinkler_controller_creator.hpp"

namespace smarthome
{


advcpp::SharedPointer<IAgent> SprinklerControllerCreator::Create(advcpp::SharedPointer<IDeviceInfo> a_deviceInfo)
{
    advcpp::SharedPointer<SprinklerController> temp(new SprinklerController(a_deviceInfo->GetLocation()));
    temp->SetSharedPointer(temp);
    return temp;
}


extern "C" void SprinklerControllerCreator::Registration(ICreatorsRegistrator & a_creatorRegistrator)
{
    std::shared_ptr<IDeviceCreator> self(new SprinklerControllerCreator);
    a_creatorRegistrator.Registrate("SprinklerController", self);

}

}