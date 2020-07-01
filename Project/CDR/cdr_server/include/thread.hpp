#ifndef THREAD_H
#define THREAD_H

#include <pthread.h>
#include "commons.hpp" // UnCopyable
#include "enriched_exception.hpp"


namespace advcpp
{

class ThreadException : public EnrichedException
{
public: 
	ThreadException(int a_errorNum, 
	               const ExtendedExceptionInfo& a_info)        
	               NOEXCEPT;
	               
	virtual ~ThreadException() NOEXCEPT;
	
	virtual const char* what() const NOEXCEPT;
};

class IRunnable : private UnCopyable
{
public:
    virtual ~IRunnable() NOEXCEPT = 0;

    virtual void Run() NOEXCEPT = 0; 
};


class Thread : private UnCopyable
{
public: 
	enum Policy
	{
		TERMINATE,
		JOIN
	};

    explicit Thread(IRunnable* a_pRun, Policy a_policy = TERMINATE) THROW1(ThreadException); 

    ~Thread() NOEXCEPT;

    void Detach();    

    void Join();

    // void TryJoin(timeOut);

    void Cancel();
    void Kill(int a_sig = 0);

    static void Yield();
    static void Exit(void* a_retVal = 0) NOEXCEPT;

private:
    static void* thunk(void* a_pCtx) NOEXCEPT;

private:
    pthread_t m_thread;
    bool m_notJoinable;
    Policy m_policy;
};

} // namespace advcpp

#include "inl/thread.inl"

#endif // THREAD_H
