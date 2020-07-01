#ifndef CONDITION_VARIABLE_H
#define CONDITION_VARIABLE_H


#include <pthread.h> // pthread_cond_t
#include "commons.hpp" // UnCopyable, Sleep
namespace advcpp
{

class Mutex;

class CVBusyException;
class CVMemoryException;
class CVUnknownException;
class CVPermissionException;
class CVDupMutexException;

class ConditionVariableException: public EnrichedExeption
{
public:
    ConditionVariableException(int a_typeOfError, 
                               XtendedInformation const& a_info) THROW2(std::exception, std::ios_base::failure)
    : EnrichedExeption(ConvertErrorType(a_typeOfError), a_info)
    {
    }

    static std::string ConvertErrorType(int a_typeOfError) THROW(std::ios_base::failure);
};

class ConditionVariable: private UnCopyable
{
public:
    ConditionVariable() THROW(ConditionVariableException);
    ~ConditionVariable() NOEXCEPT;

    template<typename Predicate>
    void Wait(Mutex& a_mutex, Predicate const & a_pred) THROW(ConditionVariableException);

    void Notify() NOEXCEPT;
    void NotifyAll() NOEXCEPT;

private:
    typedef int (*CVFunc)(pthread_cond_t*);
    void errorResponse(int a_error, CVFunc a_func, 
                              XtendedInformation const& a_info) THROW(ConditionVariableException);
    void wait(Mutex& a_mutex) THROW(ConditionVariableException);
    void errorResponseWait(int a_error, XtendedInformation const& a_info) THROW(ConditionVariableException);
    int reTry(CVFunc const& a_func) NOEXCEPT;

private:
    pthread_cond_t m_cv;

};

class CVBusyException: public ConditionVariableException
{
public:
    CVBusyException(int a_typeOfError, XtendedInformation const& a_info) THROW2(std::exception, std::ios_base::failure)
    : ConditionVariableException(a_typeOfError, a_info)
    {
    }
};

class CVMemoryException: public ConditionVariableException
{
public:
    CVMemoryException(int a_typeOfError, XtendedInformation const& a_info) THROW2(std::exception, std::ios_base::failure)
    : ConditionVariableException(a_typeOfError, a_info)
    {
    }
};

class CVUnknownException: public ConditionVariableException
{
public:
    CVUnknownException(int a_typeOfError, XtendedInformation const& a_info) THROW2(std::exception, std::ios_base::failure)
    : ConditionVariableException(a_typeOfError, a_info)
    {
    }
};

class CVPermissionException: public ConditionVariableException
{
public:
    CVPermissionException(int a_typeOfError, XtendedInformation const& a_info) THROW2(std::exception, std::ios_base::failure)
    : ConditionVariableException(a_typeOfError, a_info)
    {
    }
};

class CVDupMutexException: public ConditionVariableException
{
public:
    CVDupMutexException(int a_typeOfError, XtendedInformation const& a_info) THROW2(std::exception, std::ios_base::failure)
    : ConditionVariableException(a_typeOfError, a_info)
    {
    }
};


} //namespace advcpp

#include "condition_variable.inl"

#endif //CONDITION_VARIABLE_H