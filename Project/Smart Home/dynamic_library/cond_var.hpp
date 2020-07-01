#ifndef COND_VAR_H
#define COND_VAR_H

#include <cerrno>
#include "EnrichedException.hpp"
#include "Common.hpp"
#include "mutex.hpp"

namespace advcpp
{



class CondVarException : public EnrichedException
{
public:
    CondVarException(int errNumber, const Info & a_info) NOEXCEPTION;
};

class CondVar : private UnCopyable
{
public:
    CondVar() THROW1(CondVarException);
    ~CondVar() NOEXCEPTION;

    template <typename Pred>
    void Wait(Mutex & a_mutex, const Pred & a_pred) THROW1(CondVarException);
    void Notify() NOEXCEPTION;
    void BroadcastNotify() NOEXCEPTION;

    void Destroy() NOEXCEPTION;

private:
    pthread_cond_t m_cond;

};

inline CondVar::~CondVar() NOEXCEPTION
{
}

inline CondVarException::CondVarException(int errNumber, const Info & a_info) NOEXCEPTION
: EnrichedException(a_info, NumberToString(errNumber).c_str())
{
}

template <typename Pred>
void CondVar::Wait(Mutex & a_mutex, const Pred & a_pred) THROW1(CondVarException)
{ 
    while(a_pred()) 
    {
        pthread_cond_wait(&m_cond, a_mutex.GetMutex()); 
    }   
}

} // end namespace advcpp

#endif // COND_VAR_H