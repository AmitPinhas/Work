#include "mutex.hpp"

namespace advcpp
{

inline Guard::Guard(Mutex & a_mutex)
: m_mutex(a_mutex)
{
    m_mutex.Lock();
}

inline Guard::~Guard() NOEXCEPTION
{
    m_mutex.UnLock();
}


} // end namespace advcpp
