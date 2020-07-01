#include "fire_sensor_creator.hpp"

namespace smarthome
{


advcpp::SharedPointer<IAgent> FireSensorCreator::Create(advcpp::SharedPointer<IDeviceInfo> a_deviceInfo)
{
    advcpp::SharedPointer<IAgent> temp(new FireSensor(a_deviceInfo->GetLocation(), 1 ));
    return temp;
}


extern "C" void FireSensorCreator::Registration(ICreatorsRegistrator & a_creatorRegistrator)
{
    std::shared_ptr<IDeviceCreator> self(new FireSensorCreator);

    a_creatorRegistrator.Registrate("FireSensor", self);
}

}