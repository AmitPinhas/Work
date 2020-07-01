#include "mutex.hpp"

namespace advcpp
{

Mutex::Mutex() THROW1(MutexException)
{
	size_t repeat = REPEATS;
	int errNumber = pthread_mutex_init(&m_mutex, 0);
	while(EAGAIN == errNumber && repeat-- > 0)
    {
        Nano sleepTime(SLEEP_TIME);
        advcpp::Sleep(sleepTime);
        errNumber = pthread_mutex_init(&m_mutex, 0);
        sleepTime.value *= JUMPS;
    }
	if(errNumber)
	{
		throw MutexException(errNumber, Info(__func__, __FILE__, __LINE__));
	}
}

Mutex::~Mutex() NOEXCEPTION
{
	pthread_mutex_destroy(&m_mutex);
}

void Mutex::Lock() THROW1(MutexException)
{
	size_t repeat = REPEATS;
	int errNumber = pthread_mutex_lock(&m_mutex);
	while(EAGAIN == errNumber && repeat-- > 0)
    {
        Nano sleepTime(SLEEP_TIME);
        advcpp::Sleep(sleepTime);
        errNumber = pthread_mutex_init(&m_mutex, 0);
        sleepTime.value *= JUMPS;
    }
	if(errNumber)
	{
		throw MutexException(errNumber, Info(__func__, __FILE__, __LINE__));
	}
}

void Mutex::TryLock() THROW1(MutexException)
{
	pthread_mutex_trylock(&m_mutex);
}
	

void Mutex::UnLock() THROW1(MutexException)
{
	int errNumber = pthread_mutex_unlock(&m_mutex);
	if(errNumber)
	{
		throw MutexException(errNumber, Info(__func__, __FILE__, __LINE__));
	}
}

void Mutex::Destroy() NOEXCEPTION
{
	pthread_mutex_unlock(&m_mutex);
	pthread_mutex_destroy(&m_mutex);
}

pthread_mutex_t * Mutex::GetMutex()
{
	return &m_mutex;
}

MutexException::MutexException(int a_n, const Info & a_info) NOEXCEPTION
: EnrichedException(a_info, NumberToString(a_n).c_str())
{
}

MutexException::~MutexException() NOEXCEPTION
{	
}

} // end namespace advcpp
