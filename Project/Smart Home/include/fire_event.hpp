#ifndef FIRE_EVENT_H
#define FIRE_EVENT_H

#include "event_base.hpp"

namespace smarthome
{

struct Flames
{

bool m_exist;
size_t m_height;

};

class FireEvent : public EventBase
{
public:
    FireEvent(const Topic & a_topic, const TimeStamp & a_timestamp,  const Flames & a_flames);
    ~FireEvent() noexcept = default;
    FireEvent(const FireEvent & a_fireevent) = default;
    FireEvent & operator = (const FireEvent & a_fireevent) = default;

    Flames GetFlames() const;

private:
    Flames m_flames;

};


} // namespace smarthome

#endif // FIRE_EVENT_H
