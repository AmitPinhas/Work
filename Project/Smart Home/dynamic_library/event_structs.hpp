#ifndef EVENT_STRUCTS_H
#define EVENT_STRUCTS_H

#include <ctime>
#include <iostream>
#include <cstdlib>
#include <iostream>

namespace smarthome
{

struct TimeStamp
{
    time_t m_time;
};

struct Type
{
    Type() = default;
    Type(const std::string & a_type);
    std::string m_type;
};

struct Location
{
    Location() = default;
    Location(short a_floor, u_int a_room);
    short m_floor;
    u_int m_room;
};

struct PayLoad
{
    std::string m_payload;
};

struct Topic
{
    Topic() = default;
    Topic(const Type & a_type, const Location & a_location);
    Type        m_type;
    Location    m_location;
};

bool operator == (const Location & first, const Location & second);
bool operator != (const Location & first, const Location & second);
bool operator > (const Location & first, const Location & second);
bool operator < (const Location & first, const Location & second);


bool operator == (const Type & first, const Type & second);
bool operator != (const Type & first, const Type & second);
bool operator > (const Type & first, const Type & second);
bool operator < (const Type & first, const Type & second);

bool operator == (const Topic & first, const Topic & second);
bool operator != (const Topic & first, const Topic & second);
bool operator > (const Topic & first, const Topic & second);
bool operator < (const Topic & first, const Topic & second);

std::ostream & operator << (std::ostream & os, const Topic & a_topic);

} // namespace smarthome

#endif // EVENT_STRUCTS_H