#ifndef THREAD_INL
#define THREAD_INL

#include <sstream> // std::ostringstream

namespace advcpp
{

template <typename T>
std::string NumToStrr( T a_num )
{
     std::ostringstream a_oStringStream;
     a_oStringStream << a_num;
     return a_oStringStream.str();
}

inline ThreadException::ThreadException(int a_errorNum, 
	                                  const ExtendedExceptionInfo& a_info)        
	                                   NOEXCEPT
: EnrichedException(a_info, NumToStrr(a_errorNum).c_str())	                                   
{
}

inline ThreadException::~ThreadException() NOEXCEPT
{
}

inline const char* ThreadException::what() const NOEXCEPT
{	
	return this->what();
}

inline void* Thread::thunk(void* a_pCtx) NOEXCEPT
{
	IRunnable* runnable = static_cast<IRunnable*>(a_pCtx);
	runnable->Run();
	return 0;
}

inline size_t NumberOfCores()
{
    return sysconf(_SC_NPROCESSORS_ONLN);
}

inline size_t DefaultNumThreads()
{
	return NumberOfCores() - 1;
}

inline size_t DefaultMaxNumThreads()
{
	return NumberOfCores() * 25;
}

} // namespace advcpp

#endif // THREAD_INL