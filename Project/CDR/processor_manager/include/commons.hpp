#ifndef COMMONS_H
#define COMMONS_H

#include <ctime>
#include <time.h>
#include "exceptions_definitions.hpp"

namespace advcpp
{

class UnCopyable
{

protected:
    UnCopyable(){}

private:
    UnCopyable(UnCopyable const&);// =delete
    UnCopyable& operator=(UnCopyable const&);// =delete

};

struct Nano 
{
    size_t value;
    Nano(size_t a_time) NOEXCEPT;    
    operator size_t() const NOEXCEPT;      
    operator timespec() const NOEXCEPT;
};

struct Minutes 
{
    size_t value;
    Minutes(size_t a_time) NOEXCEPT;    
    operator size_t() const NOEXCEPT;  
    operator timespec() const NOEXCEPT;
};

void Sleep(const Nano& a_nanoseconds) NOEXCEPT;
void Sleep(const Minutes& a_minutes) NOEXCEPT;

}//namespace advcpp


#include "commons.inl"

#endif //COMMONS_H