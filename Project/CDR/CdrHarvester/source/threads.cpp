#include "threads.hpp"
#include "common.hpp"


namespace advcpp
{


Thread::Thread(IRunAble* a_prun) THROW1(ThreadExeption)
: m_thread()
{

    int retVal = EAGAIN;
    unsigned int i = 0;
    do
    {
        if ( (retVal = pthread_create(&m_thread, 0, thunk, static_cast<void*>(a_prun) ) ) == 0)
        {
            return;
        }
        Nano timeToWeit(i * MiliSeconds);
        Sleep(timeToWeit);
        ++i;
    }
    while (retVal == EAGAIN && i < 3);
    XTHROW(ThreadExeption, "thread was not created");
}

Thread::~Thread()
{
    if(pthread_kill(m_thread, 0) == 0)
    {
        assert(false);
    }
}

}//end advcpp namespace