#ifndef TIME_H
#define TIME_H
#include <time.h> //timespec
#include "Common.hpp"// throw exceptions


namespace advcpp
{

const size_t NANO = 1000000000;
const size_t SECONDS_IN_MINUTE = 60;

struct Nano
{
    size_t value;
    
    Nano(size_t a_value) NOEXCEPTION;
    // Nano(const Nano & a_nano) = default;
    // ~Nano() = default 
    // Nano & a_nano operator=(const Nano & a_nano) = default;

    operator size_t() const NOEXCEPTION; 
    operator timespec() const NOEXCEPTION; 
};

struct Second
{
    size_t value;

    Second(size_t a_value) NOEXCEPTION;
    // Second(const Second & a_second) = default;
    // ~Second() = default 
    // Second & a_second operator=(const Second & a_second) = default;

    operator size_t() const NOEXCEPTION;
    operator timespec() const NOEXCEPTION;
};

struct Minute
{
    size_t value;

    Minute(size_t a_value) NOEXCEPTION;
    // Minute(const Minute & a_minute) = default;
    // ~Minute() = default 
    // Minute & a_Minute operator=(const Minute & a_minute) = default;

    operator size_t() const NOEXCEPTION;
    operator timespec() const NOEXCEPTION;
};

inline Nano::Nano(size_t a_value) NOEXCEPTION
: value(a_value)
{    
}

} // namespace advcpp

#include "inl/time.inl"
#endif // TIME_H
