
namespace smarthome
{

inline bool operator == (const Type & a_first, const Type & a_second)
{
    return !a_first.m_type.compare(a_second.m_type);
} 

inline bool operator == (const Location & a_first, const Location & a_second)
{
    return (a_first.m_floor == a_second.m_floor && a_first.m_room == a_second.m_room);
}

inline bool operator == (const Topic & a_first, const Topic & a_second)
{
    return (a_first.m_type == a_second.m_type && a_first.m_location == a_second.m_location);
}

inline bool operator <= (const Topic & a_first, const Topic & a_second)
{
    return (a_first.m_location.m_room <= a_second.m_location.m_room);
}

inline bool operator >= (const Topic & a_first, const Topic & a_second)
{
    return (a_first.m_location.m_room >= a_second.m_location.m_room);
}

inline bool operator > (const Topic & a_first, const Topic & a_second)
{
    return (a_first.m_location.m_room > a_second.m_location.m_room);
}

inline bool operator < (const Topic & a_first, const Topic & a_second)
{
    return (a_first.m_location.m_room < a_second.m_location.m_room);
}

} // namespace smart_home
