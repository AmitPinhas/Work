#ifndef FIRE_SENSOR_CREATOR_H
#define FIRE_SENSOR_CREATOR_H

#include <memory>
#include "i_device_creator.hpp"
#include "i_creators_registrator.hpp"
#include "device_creators_holder.hpp"
#include "fire_sensor.hpp"
#include "i_device_info.hpp"


namespace smarthome
{

class FireSensorCreator : public IDeviceCreator
{
public:
    
    FireSensorCreator() = default;

    ~FireSensorCreator() = default;
    
    virtual advcpp::SharedPointer<IAgent> Create(advcpp::SharedPointer<IDeviceInfo> a_deviceInfo);

    FireSensorCreator(FireSensorCreator const& a_copy) = default;

    FireSensorCreator& operator = (FireSensorCreator const& a_copy) = default;

    static void Registration(ICreatorsRegistrator & a_creatorRegistrator);

};




} // namespace smarthome

#endif // FIRE_SENSOR_CREATOR_H