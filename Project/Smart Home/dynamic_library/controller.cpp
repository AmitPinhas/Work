#include "controller.hpp"

namespace smarthome
{

Controller::Controller(const Location & a_location, SharedPointer<IDevice> a_device)
: m_location(a_location)
, m_device(a_device)
{
}


void Controller::Run(SharedPointer<IEvent> a_ievent)
{
    m_device -> Work(a_ievent);
}

} // namespace smarthome
