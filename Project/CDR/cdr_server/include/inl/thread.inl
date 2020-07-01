
//#include "utils.hpp"
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

} // namespace advcpp
