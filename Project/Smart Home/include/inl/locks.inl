#include <cassert> //assert

#include "locks.hpp"



namespace advcpp 
{

inline Guard::Guard(Mutex& a_mutex)
: m_mutex(a_mutex)
{
    m_mutex.Lock();
}

inline Guard::~Guard()
{
    m_mutex.UnLock();
}

inline Mutex::~Mutex() NOEXCEPT
{
    int res = pthread_mutex_destroy(&getLock());
    assert(res == 0);
}

inline void Mutex::Lock() THROW1(MutexLockingException)
{
    if(pthread_mutex_lock(&getLock()) != 0)
    {
        THROWX(MutexLockingException);
    }
}

inline void Mutex::UnLock() THROW1(MutexLockingException)
{
    if(pthread_mutex_unlock(&getLock()) != 0)
    {
        THROWX(MutexLockingException);
    }
}

inline pthread_mutex_t& Mutex::getLock() 
{
    return m_lock;
}



} //namespace advcpp 