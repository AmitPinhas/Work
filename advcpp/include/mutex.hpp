#ifndef MUTEX_HPP
#define MUTEX_HPP

#include <pthread.h>
#include "mutex_exception.hpp"
#include "common.hpp"

namespace advcpp
{
class Mutex : private UnCopyable
{
public:

	Mutex() THROW1(MutexException);

	~Mutex() NOEXCEPT;

	void Lock() THROW1(MutexException);
	void UnLock() THROW1(MutexException);

	friend class ConditionalVariable;

private:
	pthread_mutex_t* MyMutex() NOEXCEPT;

private:
	pthread_mutex_t m_mutex;	
};

class Guard : private UnCopyable 
{
public:
	explicit Guard(Mutex& a_mutex) THROW1(MutexException);
	
	~Guard();

private:
	Mutex& m_mutex;
};
} // namespace advcpp

#include "inl/mutex.inl"

#endif // MUTEX_HPP
