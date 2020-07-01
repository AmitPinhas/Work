#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "i_controller.hpp"
#include "i_device.hpp"
#include "shared_pointer.hpp"

using namespace advcpp;

namespace smarthome
{

class Controller : public IController
{
public:
    Controller(const Location & a_location, SharedPointer<IDevice> a_device);
    ~Controller() = default;
    Controller(const Controller & a_controller) = default;
    Controller & operator = (const Controller & a_controller) = default;

    virtual void Run(SharedPointer<IEvent> a_ievent);

private:
    Location m_location;
    SharedPointer<IDevice> m_device;
};

} // namespace smarthome

#endif // CONTROLLER_H