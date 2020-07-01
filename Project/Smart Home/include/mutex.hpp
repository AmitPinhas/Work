#ifndef MUTEX_H
#define MUTEX_H
#include <cerrno> // errno
#include <pthread.h>
#include "Common.hpp"
#include "utils.hpp"
#include "Info.hpp"
#include "EnrichedException.hpp"
//#include "cond_var.hpp"

namespace advcpp
{

const size_t SLEEP_TIME = 500000000;
const size_t REPEATS = 3;
const size_t JUMPS = 3;

class MutexException : public EnrichedException
{
public: 
	MutexException(int a_n, const Info & a_info) NOEXCEPTION;
	~MutexException() NOEXCEPTION;	
};

class Mutex
{
public: 
	Mutex() THROW1(MutexException);
	~Mutex() NOEXCEPTION;

	void Lock() THROW1(MutexException);
	void TryLock() THROW1(MutexException);
	void UnLock() THROW1(MutexException);

	void Destroy() NOEXCEPTION;
	
	// template <typename Pred>
	//friend void CondVar::Wait(Mutex & a_mutex, const Pred & a_pred);
	friend class CondVar;

private:
	Mutex(const Mutex & a_mutex);
	Mutex & operator= (const Mutex & a_mutex);

	pthread_mutex_t * GetMutex();
	
private:
	pthread_mutex_t m_mutex;
	
};

class Guard : private UnCopyable
{
public:
	Guard(Mutex & a_mutex);
	~Guard() NOEXCEPTION;

private:
	Mutex & m_mutex;

};

} // namespace advcpp

#include "inl/mutex.inl"
#endif // MUTEX_H
