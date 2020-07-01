#include "event_structs.hpp"

namespace smarthome
{

Location::Location(short a_floor, u_int a_room)
: m_floor(a_floor)
, m_room(a_room)
{
}

Type::Type(const std::string & a_type)
: m_type(a_type)
{
}

Topic::Topic(const Type & a_type, const Location & a_location)
: m_type(a_type)
, m_location(a_location)
{
}

bool operator == (const Location & first, const Location & second)
{
    return (first.m_floor == second.m_floor && first.m_room == second.m_room);
}

bool operator != (const Location & first, const Location & second)
{
    return (first.m_floor != second.m_floor || first.m_room != second.m_room);
}

bool operator < (const Location & first, const Location & second)
{
    return ((first.m_floor < second.m_floor) || 
            (first.m_floor == second.m_floor && first.m_room < second.m_room));
}

bool operator > (const Location & first, const Location & second)
{
    return ((first.m_floor > second.m_floor) || 
            (first.m_floor == second.m_floor && first.m_room > second.m_room));
}

bool operator == (const Type & first, const Type & second)
{
    return (first.m_type.compare(second.m_type) == 0);
}

bool operator != (const Type & first, const Type & second)
{
    return (first.m_type.compare(second.m_type) != 0);
}

bool operator > (const Type & first, const Type & second)
{
    return (first.m_type.compare(second.m_type) > 0);
}

bool operator < (const Type & first, const Type & second)
{
    return (first.m_type.compare(second.m_type) < 0);
}


bool operator == (const Topic & first, const Topic & second)
{
    return (first.m_type == second.m_type && first.m_location == second.m_location);
}

bool operator != (const Topic & first, const Topic & second)
{
    return (first.m_type != second.m_type && first.m_location != second.m_location);
}

bool operator > (const Topic & first, const Topic & second)
{
    return (first.m_type > second.m_type  || 
            (first.m_type == second.m_type && first.m_location > second.m_location));
}

bool operator < (const Topic & first, const Topic & second)
{
    return (first.m_type < second.m_type || 
            (first.m_type == second.m_type && first.m_location < second.m_location));
}

std::ostream & operator << (std::ostream & os, const Topic & a_topic)
{
    os << "type: " << a_topic.m_type.m_type << " room: " << a_topic.m_location.m_room << " floor: " << a_topic.m_location.m_floor << std::endl;
    return os;
}

} // namespace smarthome
