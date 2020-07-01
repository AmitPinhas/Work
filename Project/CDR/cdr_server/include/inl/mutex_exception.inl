#include "mutex_exception.hpp"
#include "thread_utils.hpp"

namespace advcpp
{

inline MutexException::MutexException(int a_errorNum, 
	                                  const ExtendedExceptionInfo& a_info)        
	                                  NOEXCEPT
: EnrichedException(a_info, NumToStr(a_errorNum).c_str())	                                   
{
}

inline MutexException::~MutexException() NOEXCEPT
{
}

inline const char* MutexException::what() const NOEXCEPT
{	
	return this->what();
}

} // namespace advcpp
