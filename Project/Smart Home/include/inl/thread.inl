#include <unistd.h> // sysconf

namespace advcpp
{

const size_t REASNABLE_MAX = 25;

inline void* Thread::thunk( void * v_prun ) NOEXCEPTION
{
    try
    {
        IRunnable * runObject = static_cast<IRunnable *> (v_prun);
        runObject -> Run();
    }
    catch( ... )
    {
        assert( 0 );
    }
    return 0;
}

inline IRunnable::~IRunnable() NOEXCEPTION
{
}

inline Thread::Thread( IRunnable *prun , Policy a_policy )
: m_joinable(1)
, m_policy(a_policy)
{
    size_t repeat = REPEATS;
    int errNumber = pthread_create(&m_thread, 0, thunk, prun);
    while(EAGAIN == errNumber && repeat-- > 0)
    {
        Nano sleepTime(SLEEP_TIME);
        advcpp::Sleep(sleepTime);
        errNumber = pthread_create(&m_thread, 0, thunk, prun);
        sleepTime.value *= JUMPS;
    }
    if(errNumber)
    {
        throw ThreadException(errNumber, Info(__FILE__, __func__, __LINE__));
    }
}


inline Thread::~Thread() NOEXCEPTION
{
    if(!m_joinable)
    {
        return;
    }
    if(TERMINATE == m_policy)
    {
        std::terminate();
        return;
    }
    Join();
}

inline void Thread::Detach() NOEXCEPTION
{
    assert(m_joinable);
    pthread_detach(m_thread);
    m_joinable = 0;
}

inline void Thread::Join() THROW1(ThreadException)
{
    int errNumber = pthread_join(m_thread, 0);
    if(errNumber)
    {
        throw ThreadException(errNumber, Info(__FILE__, __func__, __LINE__));
    }
    m_joinable = 0;
}
       
inline void Thread::TryJoin( const Second & a_sedonds, void ** retval ) THROW1(ThreadException)
{
    timespec t_spec(a_sedonds);
    int errNumber =  pthread_timedjoin_np(m_thread, retval, &t_spec);
    {
        throw ThreadException(errNumber, Info(__FILE__, __func__, __LINE__));
    }
    m_joinable = 0;
}
   
inline void Thread::Cancel() THROW1(ThreadException)
{
    int errNumber =  pthread_cancel(m_thread);
    {
        throw ThreadException(errNumber, Info(__FILE__, __func__, __LINE__));
    }
}

inline void Thread::Kill( int a_sig ) THROW1(ThreadException)
{
    int errNumber =  pthread_kill(m_thread, a_sig);
    {
        throw ThreadException(errNumber, Info(__FILE__, __func__, __LINE__));
    }
}

inline void Thread::Yield() THROW1(ThreadException)
{
    int errNumber = sched_yield();
    {
        throw ThreadException(errNumber, Info(__FILE__, __func__, __LINE__));
    }
}    

inline void Thread::Exit(void* a_retval) NOEXCEPTION
{
    pthread_exit(a_retval);
}

//////////////////// thread exception functions ////////////////////


inline ThreadException::ThreadException(int errNumber, const Info & a_info) NOEXCEPTION
: EnrichedException(a_info, NumberToString(errNumber).c_str())
{
}

//////////////////// thread manipulation ////////////////////

inline void ThreadManipulation(std::vector<IRunnable *> runContainer)
{
    std::vector<Thread *> Threads;

    for(size_t i = 0; i < runContainer.size(); ++i)
    {
        try{
             advcpp::Thread *newThread = new advcpp::Thread(runContainer[i]);
             Threads.push_back(newThread);
        }
        catch(advcpp::ThreadException a_except)
        {
            std::cout << a_except.what();
        }        
    }

    for(size_t i = 0; i < Threads.size(); ++i)
    {
        Threads[i] -> Join();
        delete runContainer[i];
    }
}

inline long NumOfCores()
{
    return sysconf(_SC_NPROCESSORS_ONLN);
}

inline size_t DefaultThreads()
{
    size_t deafultThreads = sysconf(_SC_NPROCESSORS_ONLN);
    if(1 == deafultThreads)
    {
        return 1;
    }
    return deafultThreads - 1;
}

inline size_t MaxThreads()
{
    return NumOfCores() * REASNABLE_MAX;
}


} // namespace advcpp
