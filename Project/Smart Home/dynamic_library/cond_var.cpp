#include "cond_var.hpp"
#include "time.hpp"
#include "mutex.hpp"


namespace advcpp
{

CondVar::CondVar() THROW1(CondVarException)
{
    size_t repeat = REPEATS;
    int errNumber = pthread_cond_init(&m_cond, 0);
    while(EAGAIN == errNumber && repeat-- > 0)
    {
        Nano sleepTime(SLEEP_TIME);
        advcpp::Sleep(sleepTime);
        errNumber = pthread_cond_init(&m_cond, 0);
        sleepTime.value *= JUMPS;
    }
    if(errNumber)
    {
        throw CondVarException(errno, Info(__FILE__, __func__, __LINE__));
    }

}

void CondVar::Notify() NOEXCEPTION
{
    size_t repeat = REPEATS;    
    int errNumber = pthread_cond_signal(&m_cond);
    while(EAGAIN == errNumber && repeat-- > 0)
    {
        Nano sleepTime(SLEEP_TIME);
        advcpp::Sleep(sleepTime);
        errNumber = pthread_cond_signal(&m_cond);
        sleepTime.value *= JUMPS;
    }
}

void CondVar::BroadcastNotify() NOEXCEPTION
{
    size_t repeat = REPEATS;  
    int errNumber = pthread_cond_broadcast(&m_cond);
    while(EAGAIN == errNumber && repeat-- > 0)
    {
        Nano sleepTime(SLEEP_TIME);
        advcpp::Sleep(sleepTime);
        errNumber = pthread_cond_broadcast(&m_cond);
        sleepTime.value *= JUMPS;
    }
}

void CondVar::Destroy() NOEXCEPTION
{

}




} // end of namespace advcpp