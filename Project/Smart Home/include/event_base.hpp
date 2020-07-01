#ifndef EVENT_BASE_H
#define EVENT_BASE_H

#include <string>
#include <chrono>

#include "i_event.hpp"

namespace smarthome
{

class EventBase : public IEvent
{
public:
    virtual ~EventBase() = 0;

    virtual TimeStamp GetTimeStamp() const;
    virtual Topic GetTopic() const;

protected:
    EventBase(const Topic & a_topic, const TimeStamp & a_timestamp);
    EventBase(const EventBase & a_eventbase) = default;
    EventBase & operator = (const EventBase & a_eventbase) = default;

private:
    Topic m_topic;
    TimeStamp m_timeStamp;
    
};

} // namespace smart_home

#endif //  EVENT_BASE_H