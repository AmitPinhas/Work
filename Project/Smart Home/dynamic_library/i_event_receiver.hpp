#ifndef I_EVENT_RECEIVER_H
#define I_EVENT_RECEIVER_H

#include "i_event.hpp"
#include "shared_pointer.hpp"

using namespace advcpp;

namespace smarthome
{

class IEventReceiver
{
public:
    typedef SharedPointer<IEvent> IEventPtr;

    virtual ~IEventReceiver() = 0;

    virtual void Receive(IEventPtr a_event) const = 0;

protected:
    IEventReceiver() = default;
    IEventReceiver(const IEventReceiver & a_rhs) = default;
    IEventReceiver & operator =(const IEventReceiver & a_rhs) = default;

};

} // namespace smarthome

#endif // I_EVENT_RECEIVER_H