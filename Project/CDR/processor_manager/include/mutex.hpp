#ifndef MUTEX_H
#define MUTEX_H

#include <vector>
#include <pthread.h> //pthread_mutex_t
#include "exceptions_definitions.hpp" //EnrichedExeption
#include "commons.hpp" //UnCopyable
#include "condition_variable.hpp"

namespace advcpp
{

class MutexPermissionException;
class MutexBusyException;
class MutexMemoryException;
class MutexDeadLockException;

class MutexException: public EnrichedExeption
{
public:
    MutexException(int a_typeOfError, XtendedInformation const& a_info) THROW2(std::exception, std::ios_base::failure)
    : EnrichedExeption(ConvertErrorType(a_typeOfError), a_info)
    {
    }

    static std::string ConvertErrorType(int a_typeOfError) THROW(std::ios_base::failure);
};

class Mutex: private UnCopyable
{
public:
    friend class ConditionVariable;
    Mutex() THROW(MutexException);
    ~Mutex() NOEXCEPT;
    void Lock() THROW(MutexException);
    void TryLock(Nano const& a_time) THROW(MutexException);
    void Unlock() NOEXCEPT;
    pthread_mutex_t* mtx() NOEXCEPT;
   
private:
    typedef int (*MutexFunc)(pthread_mutex_t*);
    void errorResponse(int a_error, MutexFunc const& a_func, 
                                    XtendedInformation const& a_info) THROW(MutexException);
    int  notEnoughRecoursesFix(MutexFunc const& a_func) THROW(MutexException);
    

private:
    pthread_mutex_t m_mutex;

};

class Guard: private UnCopyable
{
public:
    Guard(Mutex& a_lock) THROW(MutexException);
    ~Guard() NOEXCEPT;

private:
    Mutex& m_lock;
};

class GuardAll: private UnCopyable
{
public:
    GuardAll(std::vector<Mutex*>& a_locks) THROW(MutexException);
    ~GuardAll() NOEXCEPT;

private:
    std::vector<Mutex*>& m_locks;
};

class MutexPermissionException: public MutexException
{
public:
    MutexPermissionException(int a_typeOfError, XtendedInformation const& a_info) THROW2(std::exception, std::ios_base::failure)
    : MutexException(a_typeOfError, a_info)
    {
    }
};

class MutexBusyException: public MutexException
{
public:
    MutexBusyException(int a_typeOfError, XtendedInformation const& a_info) THROW2(std::exception, std::ios_base::failure)
    : MutexException(a_typeOfError, a_info)
    {
    }
};

class MutexMemoryException: public MutexException
{
public:
    MutexMemoryException(int a_typeOfError, XtendedInformation const& a_info) THROW2(std::exception, std::ios_base::failure)
    : MutexException(a_typeOfError, a_info)
    {
    }
};

class MutexUnknownException: public MutexException
{
public:
    MutexUnknownException(int a_typeOfError, XtendedInformation const& a_info) THROW2(std::exception, std::ios_base::failure)
    : MutexException(a_typeOfError, a_info)
    {
    }
};

class MutexDeadLockException: public MutexException
{
public:
    MutexDeadLockException(int a_typeOfError, XtendedInformation const& a_info) THROW2(std::exception, std::ios_base::failure)
    : MutexException(a_typeOfError, a_info)
    {
    }
};

}//namespace advcpp

#endif //MUTEX_H
