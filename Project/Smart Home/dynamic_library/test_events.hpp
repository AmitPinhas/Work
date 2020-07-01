#ifndef TEST_EVENTS_H
#define TEST_EVENTS_H

#include "event_base.hpp"

namespace smarthome
{

class FireEvent : public EventBase
{
public:
    FireEvent(const Topic & a_topic, const TimeStamp & a_timestamp);
    ~FireEvent() = default;
    FireEvent(const FireEvent & fireEvent) = default;
    FireEvent & operator = (const FireEvent & fireEvent) = default;

};

struct HavcLevel
{
    size_t m_temp;
    size_t m_fanPower;
};

class HavcEvent : public EventBase
{
public:
    HavcEvent(const Topic & a_topic, const TimeStamp & a_timestamp, const HavcLevel & a_havclevel);
    ~HavcEvent() = default;
    HavcEvent(const HavcEvent & a_havc) = default;
    HavcEvent & operator = (const HavcEvent & a_havc) = default;

    HavcLevel GetLevel() const;

private:
    HavcLevel m_havclevel;

};


} // namespace smarthome

#endif //  TEST_EVENTS_H