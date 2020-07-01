#include "fire_event.hpp"

namespace smarthome
{

FireEvent::FireEvent(const Topic & a_topic, const TimeStamp & a_timestamp,  const Flames & a_flames)
: EventBase(a_topic, a_timestamp)
, m_flames(a_flames)
{
}

Flames FireEvent::GetFlames() const
{
    return m_flames;
}

} // namespace smarthome
