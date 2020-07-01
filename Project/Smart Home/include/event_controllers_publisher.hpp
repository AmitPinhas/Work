#ifndef EVENT_CONTROLLERS_PUBLISHER_H
#define EVENT_CONTROLLERS_PUBLISHER_H

#include "i_task.hpp"
#include "i_event.hpp"

class ControllersContainer;

using namespace advcpp;

namespace smarthome
{

class EventControllersPublisher : public ITask
{
public:
    EventControllersPublisher(ControllersContainer & a_container, const IEvent & a_ievent);
    ~EventControllersPublisher() = default;
    EventControllersPublisher(const EventControllersPublisher & a_eventControllersPublisher) = default;
    EventControllersPublisher & operator = (const EventControllersPublisher & a_eventControllersPublisher) = default;

    virtual void Run();

private:
    ControllersContainer & m_container; 
    const IEvent & m_ievent;

};

} // namespace smarthome

#endif // EVENT_CONTROLLERS_PUBLISHER_H