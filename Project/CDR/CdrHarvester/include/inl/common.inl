#include <time.h>
#include "exeption.hpp"


inline Nano::Nano(size_t a_value) NO_EXEPTION
: m_value(a_value)
{
}

inline Second::Second(size_t a_value) NO_EXEPTION
: m_value(a_value)
{
}

inline Minute::Minute(size_t a_value) NO_EXEPTION
: m_value(a_value)
{
}

inline Nano::operator timespec() const NO_EXEPTION
{
    timespec temp;
    temp.tv_sec = m_value / NanoToSec;
    temp.tv_nsec = m_value % NanoToSec;
    return temp;
}

inline Second::operator timespec() const NO_EXEPTION
{
    timespec temp;
    temp.tv_sec = m_value;
    temp.tv_nsec = 0;
    return temp;
}

inline Minute::operator timespec() const NO_EXEPTION
{
    timespec temp;
    temp.tv_sec = m_value * SecondToMinute;
    temp.tv_nsec = 0;
    return temp;
}

inline void Sleep(Nano a_nanos) NO_EXEPTION
{
    timespec ts = a_nanos;
    nanosleep(&ts, 0);
}

inline void Sleep(Second a_seconds) NO_EXEPTION
{
    timespec ts = a_seconds;
    nanosleep(&ts, 0);
}

inline void Sleep(Minute a_minutes) NO_EXEPTION
{
    timespec ts = a_minutes;
    nanosleep(&ts, 0);
}

inline UnCopyAble::UnCopyAble()
{
}

inline UnCopyAble::~UnCopyAble()
{
}