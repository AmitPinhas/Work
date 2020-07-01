namespace advcpp
{

inline Guard::Guard(Mutex& a_mutex) THROW1(MutexException)
: m_mutex(a_mutex)
{
	m_mutex.Lock();
}

inline Guard::~Guard()
{
	m_mutex.UnLock();
}	

inline Mutex::Mutex() THROW1(MutexException)	                                   
{
	int errnoMutex;
	errnoMutex = pthread_mutex_init(&m_mutex, 0);
	if(errnoMutex)
	{
		throw MutexException(errnoMutex, XINFO);
	}
}

inline void Mutex::UnLock() THROW1(MutexException)
{
	int errnoMutex;
	errnoMutex = pthread_mutex_unlock(&m_mutex);
	if(errnoMutex)
	{
		throw MutexException(errnoMutex, XINFO);
	}
}

inline Mutex::~Mutex() NOEXCEPT
{
	pthread_mutex_destroy(&m_mutex);
}

inline void Mutex::Lock() THROW1(MutexException)
{
	int errnoMutex;
	errnoMutex = pthread_mutex_lock(&m_mutex);
	if(errnoMutex)
	{
		throw MutexException(errnoMutex, XINFO);
	}
}

inline pthread_mutex_t* Mutex::MyMutex() NOEXCEPT
{
	return &m_mutex;
}

} // namespace advcpp
