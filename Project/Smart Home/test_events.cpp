#include "test_events.hpp"

namespace smarthome
{

FireEvent::FireEvent(const Topic & a_topic, const TimeStamp & a_timestamp)
: EventBase(a_topic, a_timestamp)
{
}

HavcEvent::HavcEvent(const Topic & a_topic, const TimeStamp & a_timestamp, const HavcLevel & a_havclevel)
: EventBase(a_topic, a_timestamp)
, m_havclevel(a_havclevel)
{
}

HavcLevel HavcEvent::GetLevel() const
{
    return m_havclevel;
}

} // namespace smarthome
