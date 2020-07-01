#ifndef COMMON_HPP
#define COMMON_HPP

#include <time.h>
#include "exeption.hpp"



static const size_t NanoToSec = 1000000000;
static const size_t SecondToMinute = 60;

class UnCopyAble
{
protected:
    virtual ~UnCopyAble();
    UnCopyAble();
    
private:
    UnCopyAble(UnCopyAble const& a_lhs);
    UnCopyAble& operator=(UnCopyAble const& a_lhs);
};


struct Nano
{
    Nano(size_t a_value) NO_EXEPTION;
    // Nano(const Nano & a_nano) = default;
    // ~Nano() = default 
    // Nano& a_nano operator=(const Nano & a_nano) = default;

    operator timespec() const NO_EXEPTION; 
    
public:
    size_t m_value;
};

struct Second
{
    Second(size_t a_value) NO_EXEPTION;
    // Second(const Second & a_second) = default;
    // ~Second() = default 
    // Second& a_second operator=(const Second & a_second) = default;

    operator timespec() const NO_EXEPTION;

public:
    size_t m_value;
};

struct Minute
{
    Minute(size_t a_value) NO_EXEPTION;
    // Minute(const Minute & a_minute) = default;
    // ~Minute() = default 
    // Minute& a_Minute operator=(const Minute & a_minute) = default;

    operator timespec() const NO_EXEPTION;

public:
    size_t m_value;
};

void Sleep(Nano a_nanos) NO_EXEPTION;

void Sleep(Minute a_minutes) NO_EXEPTION;

void Sleep(Second a_seconds) NO_EXEPTION;

#include "inl/common.inl"
#endif //COMMON_HPP