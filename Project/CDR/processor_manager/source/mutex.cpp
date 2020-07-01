#include <errno.h> // errno enums
#include <cmath> // pow
#include <cassert> // assert
#include <algorithm> //for_each

#include "mutex.hpp"
namespace advcpp
{

const static size_t TIMES_TO_TRY = 3;
const static size_t FIRST_SLEEP_TIME = 3000;
const static size_t DELTA = 3;

static inline int MutexInit(pthread_mutex_t* m_mutex) NOEXCEPT;

Mutex::Mutex() THROW(MutexException)
{
    int r = pthread_mutex_init(&m_mutex, 0);
    if(r != 0)
    {
        errorResponse(r, MutexInit, XINFO);
    }
}

static inline int MutexInit(pthread_mutex_t* m_mutex) NOEXCEPT
{
    assert(0 != m_mutex); 
    return pthread_mutex_init(m_mutex, 0);
}

inline pthread_mutex_t* Mutex::mtx() NOEXCEPT
{
    return &m_mutex;
}


void Mutex::errorResponse(int a_error, MutexFunc const& a_func, XtendedInformation const& a_info) THROW(MutexException)
{
    switch(a_error)
    {//case EINVAL->attr is invalid error, currently doesn't use attrributes
        case EPERM:
            throw MutexPermissionException(a_error, a_info);
            break;
        case ENOMEM:
        case EBUSY:
        case EAGAIN:
            a_error = notEnoughRecoursesFix(a_func);
            if(EBUSY == a_error || EAGAIN == a_error)
            {
                throw MutexBusyException(a_error, a_info);
            }
            else if(ENOMEM == a_error)
            {
                throw MutexMemoryException(a_error, a_info);
            }
            break;
        case EDEADLK:
            throw MutexDeadLockException(a_error, a_info);
            break;
        default:
            throw MutexUnknownException(a_error, a_info);
            break;      
    }
}

int Mutex::notEnoughRecoursesFix(MutexFunc const& a_func) THROW(MutexException)
{
    size_t tries = TIMES_TO_TRY;
    size_t timeToWait = FIRST_SLEEP_TIME;
    int r;
    do
    {
        r = a_func(mtx());
        Sleep(Nano(timeToWait));
        timeToWait *= pow(timeToWait, DELTA);
    }while(r != 0 && tries --> 0);

    return r;
}

Mutex::~Mutex() NOEXCEPT
{
    int r = pthread_mutex_destroy(mtx());
    assert(0 == r);
}

void Mutex::Lock() THROW(MutexException)
{
    int r = pthread_mutex_lock(mtx());
    if(r != 0)
    {
        errorResponse(r, pthread_mutex_lock, XINFO);
    }  
}

void Mutex::TryLock(Nano const& a_time) THROW(MutexException)
{
    Sleep(a_time);
    int r = pthread_mutex_trylock(mtx());
    if(r)
    {
        errorResponse(r, pthread_mutex_trylock, XINFO);
    }  
}

void Mutex::Unlock() NOEXCEPT
{
    int r = pthread_mutex_unlock(mtx());
    if(r)
    {
        std::terminate();
    } 
}


Guard::Guard(Mutex& a_lock) THROW(MutexException)
: m_lock(a_lock)
{
    m_lock.Lock();
}

Guard::~Guard() NOEXCEPT
{
    m_lock.Unlock();
}

struct LockAll
{
    void operator()(Mutex* a_mutex)
    {
        a_mutex->Lock();
    }
};

GuardAll::GuardAll(std::vector<Mutex*>& a_locks) THROW(MutexException)
: m_locks(a_locks)
{
    for_each(m_locks.begin(), m_locks.end(), LockAll());
}

struct UnlockAll
{
    void operator()(Mutex* a_mutex)
    {
        a_mutex->Unlock();
    }
};

GuardAll::~GuardAll() NOEXCEPT
{
    for_each(m_locks.begin(), m_locks.end(), UnlockAll());
}

std::string MutexException::ConvertErrorType(int a_typeOfError) THROW(std::ios_base::failure)
{
    assert(0 != a_typeOfError); 
    switch(a_typeOfError)
    {//case EINVAL->attr is invalid error, currently doesn't use attrributes
        case EPERM:
            return std::string("EPERM");
        case ENOMEM:
            return std::string("ENOMEM");
        case EBUSY:
            return std::string("EBUSY");
        case EAGAIN:
            return std::string("EAGAIN");
        case EDEADLK:
            return std::string("EDEADLK");
        default:
        {
            std::ostringstream sstr;
            sstr<<a_typeOfError;
            return std::string("Unknown Error: ") + sstr.str();   
        }
    }

}





} //namespace advcpp