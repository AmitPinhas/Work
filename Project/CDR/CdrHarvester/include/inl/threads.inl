#include <cassert>// assert
#include <pthread.h>
#include <errno.h>
#include <signal.h>

#include "common.hpp"


namespace advcpp
{

inline void* Thread::thunk(void* a_runAble)
{
    IRunAble* runFunc = static_cast<IRunAble*>(a_runAble);
    try
    {
        runFunc-> Run();
    }
    catch(...)
    {
        assert(false);
    }
    return 0;
}

inline void Thread::Join() THROW1(ThreadExeption)
{
    if (pthread_join(m_thread, NULL) != 0)
    {
        XTHROW(ThreadExeption, "join error");
    }   
}

inline void Thread::Detach() NO_EXEPTION
{
    pthread_detach(m_thread);
}    

inline void Thread::Cancel() NO_EXEPTION
{
    if (pthread_cancel(m_thread) != 0)
    {
        XTHROW(ThreadExeption, "cancel error");
    }
}

inline void Thread::Kill(size_t a_sig) THROW1(ThreadExeption)
{
    if(pthread_kill(m_thread, a_sig) != 0)
    {
        XTHROW(ThreadExeption, "kill error");
    }
}

inline void Thread::TryJoin(Nano a_time) THROW1(ThreadExeption)
{
    void* retVal;
    timespec timeToWeit = a_time;

    if( (pthread_timedjoin_np(m_thread, &retVal, &(timeToWeit) ) ) != 0)
    {
        XTHROW(ThreadExeption, "try join error");
    }
}


inline void Thread::Yield() THROW1(ThreadExeption)
{
    if(pthread_yield() != 0)
    {
        XTHROW(ThreadExeption, "yield error");
    }
    pthread_yield();
}
 
inline void Thread::Exit(void* a_return) NO_EXEPTION
{
    pthread_exit(a_return);
}

inline ThreadExeption::ThreadExeption(const char* a_msg, InfoExeption a_info) NO_EXEPTION
: MyExeption(a_msg, a_info)
{
}


inline IRunAble::~IRunAble()
{
}






}//advcpp namespace