#include <pthread.h>
#include <cstdio>
#include <errno.h>


namespace advcpp
{

static const int MiliSeconds = 1000000;

inline Mutex::Mutex() THROW1(MutexExeption)
: m_mutex()
{
    int retVal = EAGAIN;
    unsigned int i = 0;
    do
    {
        if ( (retVal = pthread_mutex_init(&m_mutex, NULL) ) == 0)
        {
            return;
        }
        Nano timeToWeit(i * MiliSeconds);
        Sleep(timeToWeit);
        ++i;
    }
    while (retVal == EAGAIN && i < 3);
    XTHROW(MutexExeption, "mutex was not created");

}

inline void Mutex::Lock() THROW1(MutexExeption)
{
    if (pthread_mutex_lock(&m_mutex) != 0)
    {
        XTHROW(MutexExeption, "mutex error lock");
    }
}

inline void Mutex::UnLock() THROW1(MutexExeption)
{
    if (pthread_mutex_unlock(&m_mutex) != 0)
    {
        XTHROW(MutexExeption, "mutex error unlock");
    }
}

inline void Mutex::TryLock(Nano a_time) NO_EXEPTION
{
    if (pthread_mutex_trylock(&m_mutex) != 0)
    {
        Sleep(a_time);
        pthread_mutex_trylock(&m_mutex);
    }
}

inline MutexExeption::MutexExeption(const char* a_msg, InfoExeption a_info) NO_EXEPTION
: MyExeption(a_msg, a_info)
{
}

inline pthread_mutex_t* Mutex::GetMutexP() NO_EXEPTION
{
    return &m_mutex;
}

inline Guard::Guard(Mutex& a_lock)
: m_lock(a_lock)
{
    m_lock.Lock();
}

inline Guard::~Guard()
{
    try
    {
        m_lock.UnLock();
    }
    catch(...)
    {
    }
}

}//namespace advcpp