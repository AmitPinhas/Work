#include "commons.hpp"
#include <unistd.h>

namespace advcpp
{

inline Nano::Nano(size_t a_time) NOEXCEPT
: value(a_time)
{
}  

inline Nano::operator size_t() const NOEXCEPT
{ 
    return value; 
} 

inline Minutes::Minutes(size_t a_time) NOEXCEPT
: value(a_time) 
{
}  

inline Minutes::operator size_t() const NOEXCEPT
{ 
    return value; 
} 

inline void Sleep(const Minutes& a_minutes) NOEXCEPT
{
    timespec req = a_minutes;
    nanosleep(&req, 0); 
}

inline void Sleep(const Nano& a_nanoseconds) NOEXCEPT
{
    timespec req = a_nanoseconds;
    nanosleep(&req, 0); 
}

}//namespace advcpp