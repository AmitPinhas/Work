#include "event_base.hpp"

namespace smarthome
{

EventBase:: ~EventBase()
{
}

TimeStamp EventBase::GetTimeStamp() const
{
    return m_timeStamp;
}


Topic EventBase::GetTopic() const
{
    return m_topic;
}

EventBase::EventBase(const Topic & a_topic, const TimeStamp & a_timestamp)
: m_topic(a_topic)
, m_timeStamp(a_timestamp)
{    
}

} // namespace smarthome
