#include "thread.hpp"

#include <signal.h> // pthread_kill
#include <cassert>

namespace advcpp
{

IRunnable::~IRunnable() NOEXCEPT
{
}

Thread::Thread(IRunnable* a_pRun, Policy a_policy) THROW1(ThreadException)
: m_notJoinable(false)
, m_policy(a_policy)
{
	int errnoThread;
	errnoThread = pthread_create(&m_thread, 0, thunk, a_pRun);
	if(errnoThread)
	{
		throw ThreadException(errnoThread, XINFO);
	}
}

Thread::~Thread() NOEXCEPT
{
	if(m_notJoinable)
	{
		return;
	}
	if(m_policy == JOIN)
	{
		Join();
		return;
	}
	std::terminate();
}

void Thread::Detach()
{
	pthread_detach(m_thread);
	m_notJoinable = true;
}

void Thread::Join()
{
	pthread_join(m_thread, 0);
	m_notJoinable = true;
}

void Thread::Cancel()
{
	pthread_cancel(m_thread);
}

void Thread::Kill(int a_sig)
{
	pthread_kill(m_thread, a_sig);
}

void Thread::Yield()
{
	pthread_yield();
}

void Thread::Exit(void* a_retVal) NOEXCEPT
{
	pthread_exit(a_retVal);
}

} // namespace advcpp
