#ifndef I_EVENT_H
#define I_EVENT_H

#include "event_structs.hpp"

namespace smarthome
{

class IEvent 
{
public:
    virtual ~IEvent() noexcept = 0;
    
    virtual TimeStamp GetTimeStamp() const = 0;
    virtual Topic GetTopic() const = 0;

protected:
    IEvent() = default;
    IEvent(const IEvent & a_ievent) = default;
    IEvent & operator = (const IEvent & a_ievent) = default;
    
};

} // namespace smarthome

#endif // I_EVENT_H