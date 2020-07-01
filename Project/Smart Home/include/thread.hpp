#ifndef THREAD_H
#define THREAD_H

#include <cassert> // assert
#include <cerrno> // EAGAIN
#include <sched.h> // pthread_sche_kill
#include <signal.h> // pthread_kill
#include <vector> // vector -> thread manipulation
#include "Common.hpp" // UnCopyable
#include "EnrichedException.hpp" // EnrichedException inheretence
#include "mutex.hpp" // Mutex class

namespace advcpp
{

/////////////////////  class ThreadException  ///////////////////// 

class ThreadException : public EnrichedException
{
public: 
    ThreadException(int errNumber, const Info & a_info) NOEXCEPTION;
    //~ThreadException() NOEXCEPTION = default;
    // ThreadException(const ThreadException & a_te) = default;
    // ThreadException & operator= (const ThreadException & a_te) = default;
};

/////////////////////  class IRunnable  ///////////////////// 

class IRunnable : private UnCopyable
{
public: 
    virtual ~IRunnable() NOEXCEPTION = 0;

    virtual void Run() NOEXCEPTION = 0; // unknown exceptions Behavior
};

/////////////////////  class Thread  ///////////////////// 


class Thread : private UnCopyable 
{
public:
    enum Policy{ TERMINATE, JOIN };

    explicit Thread( IRunnable *prun , Policy a_policy = TERMINATE ); 
    
    ~Thread() NOEXCEPTION;

    void Detach() NOEXCEPTION;    
    void Join() THROW1(ThreadException);

    void TryJoin( const Second & a_sedonds, void ** retval = 0 ) THROW1(ThreadException);

    void Cancel() THROW1(ThreadException);
    void Kill( int a_sig = 0 ) THROW1(ThreadException);
    
    static void Yield() THROW1(ThreadException);
    static void Exit(void* a_retval = 0) NOEXCEPTION;

private:
    static void* thunk( void * v_prun ) NOEXCEPTION;
    
private:
    pthread_t m_thread;
    int m_joinable;
    Policy m_policy;
};

long NumOfCores();
size_t DefaultThreads();
size_t MaxThreads();


} // end namespace advcpp

#include "inl/thread.inl"
#endif // THREAD_H